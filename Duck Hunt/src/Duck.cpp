#include "Duck.h"
#include "ofMain.h" 
#include "ofApp.h"
#include "Game.h" 
void Duck::setup()
{
	size = ofGetHeight()/10.6; 
	x = ofRandom(0, ofGetWidth() - size);
	y = ofGetHeight();  
	maxVel = 7;
	minVel = maxVel - 2;
	dx = ofRandom(-maxVel, minVel);
	dy = ofRandom(-maxVel, -minVel);
	delay = 2;  //delays bird from flying again(in seconds)   
	quack.load("sounds/quack.mp3");
}

void Duck::update()
{       
		
		//update duck every frame in case user changes window size
	    size = ofGetHeight() / 10.6; 

		//keep track of time passed since bird died
		currentTime = ofGetElapsedTimef();
		delta = currentTime - time;

		y += dy;
		x += dx;

		flewAway = false;

		//keeps duck in bounds
		if (x >= ofGetWidth() - size || x <= 0) {
			dx *= -1;
		}

		//handles duck flying away
		else if (y+size <= 0)  {   
			if (delta > delay) {  //set delay
				resetDuck();
				flewAway = true;
			}
		}

		//flips bird based on direction its flying
		if (dx < 0 && !flipped) {
			Game::character.mirror(false, true);
			flipped = true;
		} 
		if (dx > 0 && flipped) {
			Game::character.mirror(false, true);
			flipped = false;
		}	
}

void Duck::draw()
{
	Game::character.draw(x, y, size, size);
}

void Duck::resetDuck() { 
	if (ofApp::gameLoop) {
		quack.play();
	}  
	x = ofRandom(0, ofGetWidth() - size);
	y = ofGetHeight() - 50;
	minVel = maxVel - 1.5;
	dx = ofRandom(-maxVel, minVel);
	dy = ofRandom(-maxVel, -minVel); 
	time = currentTime;
}



