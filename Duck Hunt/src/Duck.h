#pragma once

#include "ofMain.h"
class Duck {
	public:
		float x,y,dx,dy,currentTime,time,delta, delay;
		static float minVel, maxVel;
		float size;
		bool flewAway = false;
		ofColor color;
		void setup();
		void update();
		void draw();
		bool flipped,killed = false;
		void resetDuck();
	    ofSoundPlayer quack; 
		ofImage duckTopLeft;
		ofImage duckTopRight;
		ofImage duckBottomLeft;
		ofImage duckBottomRight;
		static vector<ofImage> duckExplosion;

};
