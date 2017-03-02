#pragma once

#include "ofMain.h"

class October : public ofBaseApp{

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

		ofPoint rotatePt( ofPoint pt, double t );
		vector< ofPoint > left, right, top, bottom;
		vector< ofPoint > leftCircle, rightCircle, topCircle, bottomCircle;
	double 	centerSize     = 400;
	int 	lengthSide     = 200;
	double 	circleRadius   = 300;
	int 	smallRad       = 8;
	ofPoint centerPoint = ofPoint( 400.0, 400.0);

    void initSquare();
    void initCircle();

    void drawCircle( double time );
    void drawLines( double time );
};
//  ----------------------------------------------------------------------
//  ----------------------------------------------------------------------


