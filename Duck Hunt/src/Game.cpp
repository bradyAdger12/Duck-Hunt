#include "Game.h"
#include "ofApp.h"
#include "Duck.h"  
bool ofApp::gameLoop;
bool ofApp::gameOverMusic;  
int choice = 0;
int lengthSelector = 0;
int characterSelector = 0;
string c = "";
void Game::setup() {
	

	//setup crosshair and duck
	crosshairColor.set(255, 0, 0);
	d = new Duck(); 
	d->setup();
	adjustHitZone = d->size/5;  //adjusts the hit zone to make up for invisible box around duck. the lower the number the easier it is to hit

	//add characters 
	characters.push_back("images/duck.png");
	characters.push_back("images/duck2.png"); 

	//default bird
	character.load("images/duck.png");

	//set up difficulty map
	selection = "Easy";
	difficulty["Easy"] = 7;
	difficulty["Medium"] = 9;
	difficulty["Hard"] = 11;
	difficulty["Extreme"] = 14;
    diffVector.push_back("Easy");
	diffVector.push_back("Medium");
	diffVector.push_back("Hard");
	diffVector.push_back("Extreme");
	

	//set attributes 
	hit = 0;
	miss = 0;
	shot = 0;
	quitGame = false;
	gameLength = 15;
	for (int i = 15; i <= 90; i += 15) {
		gameLengthList.push_back(i);
	}  

	//number of bullets depend on length of the game
	bullets = gameLength / 2.5 + 1;
	magazine = bullets;

	fireRate = .008;
	gravity = .55;   //how fast bird falls when shot per frame

	//sounds
	duckLands.load("sounds/duck lands.mp3");
	shotSound.load("sounds/gun.mp3");
	dryfire.load("sounds/dryfire.mp3");

	//set initial flash color to white
	flashColor.set(255, 255, 255, 0);
	

}
void Game::update() {

	if (ofApp::gameLoop) {
		//keep track of time passed since last shot to implement fire rate
		currentTime = ofGetElapsedTimef();
		delta = currentTime - time;

		//countdown to end of game
		timer = gameLength - currentTime;

		//if timer = 0 and bird is not on screen
		if (timer < 1 || quitGame) {
			timer = 0; 
			if (d->y > ofGetHeight() || d->y + d->size < 5 || quitGame) {
				restartGame();
			}

		}

		//update duck. see if flew away
		d->update();
		if (d->flewAway) {
			miss++;
		}

		//handle dead duck
		deadDuck();
	}
}
void Game::draw() {
	d->draw();  
}

void Game::_mouseMoved(int x, int y) { 
		mouseX = x;
		mouseY = y;
}

void Game::drawCrosshairs() { 
		//color crosshairs 
		ofSetColor(crosshairColor);
		ofSetLineWidth(3);
		ofDrawLine(mouseX, mouseY - 5, mouseX, mouseY - 20);
		ofDrawLine(mouseX + 5, mouseY, mouseX + 20, mouseY);
		ofDrawLine(mouseX, mouseY + 5, mouseX, mouseY + 20);
		ofDrawLine(mouseX - 5, mouseY, mouseX - 20, mouseY);

		//flashColor changes when gun is shot
		ofSetColor(flashColor);
		ofDrawCircle(mouseX, mouseY, 5);
		ofSetColor(255, 255, 255);
	
}

void Game::_keyPressed(int key) { 

	cout << key << endl;

	if(ofApp::gameLoop) {
		//shoot key
		if (key == 32) {
			if (isEmpty()) {
				dryfire.play();
			}
			else {
				shotSound.play();
				magazine -= 1;
				flashColor.set(255, 238, 0);  //flash if space is hit
				shot++;
				detectDuck(mouseX, mouseY);
			}
		}

		//change to random color
		if (key == 99) {
			int red = ofRandom(0, 255);
			int green = ofRandom(0, 255);
			int blue = ofRandom(0, 255);
			crosshairColor.set(red, blue, green);
		}

		// quit/new game
		if (key == 113) {
			quitGame = true;
		}

}
	else {

		if (key == 57358) {
			c = characters[characterSelector % characters.size()];
			characterSelector++;
			character.load(c);
		}

		//restart game
		if (key == 13) {
			ofResetElapsedTimeCounter();
			d->resetDuck();
			d->time = 0;
			d->delta = 0;
			ofApp::gameLoop = true;
			ofApp::gameOverMusic = false;
		}

		//change difficulties 
		if (key == 57345) {
			choice++;
			selection = diffVector[choice % diffVector.size()];
			d->minVel = difficulty[selection] - 2;
			d->maxVel = difficulty[selection];
			
		}

		//change length of game
		if (key == 116) {
			lengthSelector++;
			gameLength = gameLengthList[lengthSelector % gameLengthList.size()]; 
			bullets = gameLength / 2.5 + 1;
			magazine = bullets;
		}
	}
}

void Game::_keyReleased(int key) {
	switch(key) {
	case 32: 
		flashColor.set(255,255,255,0);  //'unflash' when space is released
	 }
}

void Game::detectDuck(int x, int y) {	
		if ((x - adjustHitZone >= d->x && x + adjustHitZone <= d->x + d->size) && (y <= d->y + d->size && y >= d->y) && !d->killed) {
			d->time = d->currentTime;
			hit++;
			d->killed = true;
			isFalling = true;
		}
		//if duck isn't dead, flip x velocity if shot is missed 
		if (!d->killed) {
			d->dy -= 3;
			d->dx *= -1;
		}
}

void Game::deadDuck() {
	if (d->killed) {
		d->dy += gravity; 
		if (isFalling) {
			character.mirror(true, false);
			isFalling = false;
		}
		if (d->y >= ofGetHeight()) {  
			if (d->delta > d->delay) {   // sets delay for next bird to spawn
				if (!isFalling) {
					character.mirror(true, false);
					isFalling = true;
					d->resetDuck();
					isFalling = false;
					d->killed = false;
				}

			} 
		}
	}
}

bool Game::isEmpty() {
	if (magazine <= 0) {
		magazine = 0;
		return true;
	}
	return false;
}

void Game::restartGame() { 

	//reload all characters so it reverts to original orientation
	for (int i = 0; i < characters.size(); i++) {
		character.load(characters[i]);
	} 

	//reset duck attributes 
	d->flipped = false;
	d->killed = false;

	//reset times
	delta = 0;
	time = 0;

	//get data

	
	if (!quitGame) {
		score = hit;
		scores.push_back(score);  //track scores 
		highScore = isHighScore();
	}
	else {
		score = 0;
	}
	
	//reset data 
	magazine = bullets;
	hit = 0;
	miss = 0;
	shot = 0;

	quitGame = false;

	//kill loop until user hits enter
	ofApp::gameLoop = false;

	//resest duck
	d->resetDuck();

}

//determine if high schore or not
bool Game::isHighScore() {
	bool highScore = false;
	int recentScore = scores[scores.size() - 1];   //most recent score that was pushed into vector
	if (scores.size() > 1) { 
		for (int i = 0; i < scores.size()-1; i++) {
			if (recentScore > scores[i]) {
				highScore = true;
			}
			else {
				return false;
			}
		}
	}
	return highScore;
}


 





