#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed( int key ) override;

    ofxOscSender    sender;
    ofxOscReceiver  receiver;

    string adressText = "/text";
    string adressCreate = "/create";
    string textCurrent = "";

    ofTrueTypeFont textFont;
    int xText = 100;
    int yText = 300;


    ofxPanel gui;
    ofxIntSlider textLength;
    ofxIntSlider textMovementHight;
    ofxIntSlider textMovementSpeed;
    ofxIntSlider textShift;
    bool showGui = false;
};
