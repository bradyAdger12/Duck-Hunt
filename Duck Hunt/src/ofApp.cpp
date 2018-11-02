#include "ofApp.h"
#include "Duck.h"
#include "Game.h"
#include <map>
Game *game;
ofColor color; 
float Duck::maxVel;
float Duck::minVel; 
Duck* Game::d;
ofImage Game::character; 
//--------------------------------------------------------------
void ofApp::setup() { 
			game = new Game();
			game->setup();
			color.set(255);

			gameLoop = false; 
			scorePresent = false;
			gameOverMusic = false;

			//images
			background.load("images/background.png");
			foreground.load("images/foreground.png");  

			//fonts
			displayScore.load("B20sans.ttf", 30);
			myFont.load("B20sans.ttf", 23);
			displayTimer.load("B20sans.ttf", 90);
			displayTimer.setLetterSpacing(1.2); 

			//audio
			outdoor.load("sounds/outdoor.mp3");
			gameOver.load("sounds/game over.mp3");
			outdoor.play();
			outdoor.setLoop(true);
			
			
}

//--------------------------------------------------------------
void ofApp::update(){ 
		if (gameLoop) {
			outdoor.setPaused(false);
			game->update();
		}
}

//--------------------------------------------------------------
void ofApp::draw() { 
		ofHideCursor();
	    background.draw(0, 0, ofGetWidth(), ofGetHeight());
		if (gameLoop) {
			scorePresent = true;
			game->draw();
			myFont.drawString("C = CHANGE CROSSHAIR COLOR(RANDOM)", 20, 25);
			myFont.drawString("Q = QUIT / NEW GAME", 20, 50);
		}

		//used to even out game data for d
		int evenStrings = (ofGetWidth() / 5) - 50;

		//draw in foreground
		foreground.draw(0, 0, ofGetWidth(), ofGetHeight());
		game->drawCrosshairs();

		if (gameLoop) {
			//displays game stats
			myFont.drawString("Misses: " + ofToString(game->miss), evenStrings * 3, ofGetHeight() - 50);
			myFont.drawString("Shots: " + ofToString(game->shot), evenStrings * 4, ofGetHeight() - 50);
			myFont.drawString("Magazine: " + ofToString(game->magazine), evenStrings * 5, ofGetHeight() - 50);
			myFont.drawString("Space = Shoot", evenStrings - 55, ofGetHeight() / 1.10);
			myFont.drawString("Mouse = Aim", evenStrings - 55, ofGetHeight() / 1.04);
		}

		//change timer to red for the last 10 seconds
		if (game->timer < 11) {
			ofSetColor(255, 0, 0);
		}

		if (gameLoop) {
			//display game timer
			displayTimer.drawString(ofToString(game->timer), ofGetWidth() - 120, 120);
		}

		//default set background to "white"
		ofSetColor(255);


		//if game is over, display scores and give option to change difficulty
		if (!gameLoop) { 
			myFont.drawString("F2 = CHANGE DIFFICULTY: " + game->selection, 20, 25);
			myFont.drawString("T = GAME LENGTH: " + ofToString(game->gameLength) + "s" , 20, 60); 
			myFont.drawString("CHARACTER -> ", 20, 125);
			Game::character.draw(220, 80, 60, 60);
			outdoor.setPaused(true);
			if (!gameOverMusic) {
				gameOver.play();
				gameOverMusic = true;
			}
			if (scorePresent) {
				if (!game->highScore) {
					displayScore.drawString("SCORE " + ofToString(game->score), ofGetWidth() / 2 - 40, ofGetHeight() / 2 - 50);

				}
				else {
					displayScore.drawString("HIGH SCORE  " + ofToString(game->score), ofGetWidth() / 2 - 75, ofGetHeight() / 2 - 50);
				}
			}
			
			displayScore.drawString("PRESS 'ENTER' TO PLAY", ofGetWidth() / 2 - 160, ofGetHeight() / 2 - 10);
		}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ 
		game->_keyPressed(key);
	

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
		game->_keyReleased(key);
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){  
		game->_mouseMoved(x, y);
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){  
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

