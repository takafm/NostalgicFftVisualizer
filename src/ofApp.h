#pragma once

#include "ofMain.h"
#include "ofxProcessFft.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	private:
		int halfWidth = ofGetWidth() / 2;
		int halfHeight = ofGetHeight() / 2;

	public:
		void setup();
		void update();
		void draw();
		void scanLine();

		ProcessFFT fft;
		ofxPanel gui;
		ofxFloatSlider level;
		ofImage myImage;
};
