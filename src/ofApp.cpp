#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(832, 624);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0);
	myImage.loadImage("portrait.jpg");
	myImage.resize(ofGetWidth(), ofGetHeight());

	//FFT Setup
	fft.setup();
	fft.setNumFFTBins(16);
	fft.setNormalize(true);

	//GUI
	gui.setup();
	gui.add(level.setup("Input Level", 800, 0, 5000));
}

//--------------------------------------------------------------
void ofApp::update(){
	fft.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	myImage.draw(0, 0);

	//Get FFT Value
	float lowValue = ofMap(fft.getLowVal(), 0, 1, 0, level);
	float midValue = ofMap(fft.getMidVal(), 0, 1, 0, level);
	float highValue = ofMap(fft.getHighVal(), 0, 1, 0, level);

	//Paint Background
	ofSetColor(lowValue, midValue, highValue, 100);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());

	//Draw Scanning Lines
	scanLine();

	//GUI
	//gui.draw();
}

void ofApp::scanLine() {
	ofPushMatrix();
	ofTranslate(halfWidth, halfHeight);

	//Right lines
	float rxFromLowVal = ofMap(fft.getLowVal(), 0, 1, 0, halfWidth / 3);
	float rxFromMidVal = ofMap(fft.getMidVal(), 0, 1, halfWidth / 3, halfWidth / 3 * 2);
	float rxFromHighVal = ofMap(fft.getHighVal(), 0, 1, halfWidth / 3 * 2, halfWidth);
	//Left lines
	float lxFromLowVal = ofMap(fft.getLowVal(), 0, 1, -halfWidth / 3, 0);
	float lxFromMidVal = ofMap(fft.getMidVal(), 0, 1, -halfWidth / 3 * 2, -halfWidth / 3);
	float lxFromHighVal = ofMap(fft.getHighVal(), 0, 1, -halfWidth, -halfWidth / 3 * 2);

	//Draw
	ofColor col;
	col.setHsb(ofMap(fft.getLowVal(), 0, 1, 0, 160), ofMap(fft.getLowVal(), 0, 1, 0, 255), ofMap(fft.getLowVal(), 0, 1, 0, 255));
	ofSetColor(col);
	ofLine(rxFromLowVal, -halfHeight, rxFromLowVal, halfHeight);
	ofLine(rxFromMidVal, -halfHeight, rxFromMidVal, halfHeight);
	ofLine(rxFromHighVal, -halfHeight, rxFromHighVal, halfHeight);
	ofLine(lxFromLowVal, -halfHeight, lxFromLowVal, halfHeight);
	ofLine(lxFromMidVal, -halfHeight, lxFromMidVal, halfHeight);
	ofLine(lxFromHighVal, -halfHeight, lxFromHighVal, halfHeight);
	ofPopMatrix();
}

