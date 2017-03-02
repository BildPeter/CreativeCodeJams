#pragma once

#include "ofMain.h"
#include "ofxGui.h"


struct  weatherData
{
    double      lon;
    double      lat;
    double      velWind;
    double      temp;
    ofVec3f     point;
};

struct weatherTimedData
{
    std::vector< std::vector< weatherData > >  weatherDataVector;
    std::vector< ofMesh >       meshVecTemp;
    std::vector< ofMesh >       meshVecWind;
};

struct analysisData
{
    
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void    tempPlotActivation();
    void    windPlotActivation();
    
    std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str);
		

    ofEasyCam   cam;
    weatherTimedData    weatherTimed;
    
    bool    isFullscreen, drawGrid;
    
    // --- GUI
    ofxIntSlider    timeSlider;
    ofxFloatSlider  rotation;
    ofxToggle       playButton, autoRotate;
    ofxButton       tempButton, windButton;
    bool            useTemp, useWindVel;
    ofxPanel        gui;
    
    string      chosenPlot;
    
    // ---- Picture Plot
    
    ofImage     picturePlot;
};

