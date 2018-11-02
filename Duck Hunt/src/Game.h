#pragma once
#include "ofMain.h"
#include "Duck.h"
#include <map>
class Game {
public: 
	static Duck* d;
	string selection;
	float mouseX, mouseY, hit, miss, shot, fireRate, gravity;
	int size, currentTime, delta, time, magazine, timer, gameLength, score, adjustHitZone, bullets;
	bool isFalling,highScore,quitGame = false; 
	vector<int> scores;
	vector<int>::iterator scoresIt;
	vector<int> gameLengthList;
	vector<ofColor> colorWheel;
	vector<string> characters;
	map<string, float> difficulty; 
	vector<string> diffVector;
	ofColor crosshairColor;
	ofColor flashColor;
	ofSoundPlayer shotSound; 
	ofSoundPlayer dryfire;
	ofSoundPlayer duckLands; 
	static ofImage character; 
	void setup();
	void update();
	void draw();  
	void _mouseMoved(int x, int y);
	void _keyPressed(int key);
	void _keyReleased(int key);
	void detectDuck(int x, int y);
	void drawCrosshairs();
	void deadDuck(); 
	bool isEmpty();
	bool isHighScore();
	void restartGame();

};
