#include "October.h"

//--------------------------------------------------------------
void October::setup(){
    initSquare( );
    initCircle( );
}


//--------------------------------------------------------------
void October::update(){

}

//--------------------------------------------------------------
void October::draw(){
    ofBackground( ofColor::darkBlue );
    auto time = ofGetElapsedTimeMillis() / 300.0;

    ofSetColor( ofColor::lightBlue);
    drawLines( time );

    ofSetColor( ofColor::orange);
    drawCircle( time );

    
}

//--------------------------------------------------------------
void October::keyPressed(int key){

}

//--------------------------------------------------------------
void October::keyReleased(int key){

}

//--------------------------------------------------------------
void October::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void October::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void October::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void October::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void October::windowResized(int w, int h){

}

//--------------------------------------------------------------
void October::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void October::dragEvent(ofDragInfo dragInfo){

}

void October::initCircle()
{
    for( int i = 0; i < 10; i++ )
    {
        double angle = i*(PI/2) / 10.0;
        topCircle.emplace_back( cos( angle ) * circleRadius, sin( angle ) * circleRadius );
        angle += PI/2;
        bottomCircle.emplace_back( cos( angle ) * circleRadius, sin( angle  ) * circleRadius );
        angle += PI/2;
        rightCircle.emplace_back( cos( angle ) * circleRadius, sin( angle ) * circleRadius );
        angle += PI/2;
        leftCircle.emplace_back( cos( angle ) * circleRadius, sin( angle ) * circleRadius );
    }
}

void October::initSquare()
{
    for( int i = 0; i < 10; i++ )
    {
        int stepSize = i * lengthSide / 10;
        top.emplace_back( lengthSide / 2 - stepSize, -lengthSide / 2);
        bottom.emplace_back( lengthSide / 2 - stepSize, lengthSide / 2);
        right.emplace_back( -lengthSide / 2, lengthSide / 2 - stepSize);
        left.emplace_back( lengthSide / 2, lengthSide / 2 - stepSize);
    }
}



void October::drawLines( double time )
{
    for( int i = 0; i < 10; i++ )
    {
        ofDrawLine( topCircle[i] + centerPoint, rotatePt( top[i], time) + centerPoint );
        ofDrawLine( bottomCircle[i] + centerPoint, rotatePt( bottom[i], time) + centerPoint );
        ofDrawLine( leftCircle[i] + centerPoint, rotatePt( left[i], time) + centerPoint );
        ofDrawLine( rightCircle[i] + centerPoint, rotatePt( right[i], time) + centerPoint );

//        ofDrawCircle( rotatePt(bottom[i], t) + centerPoint, smallRad);
//        ofDrawCircle( rotatePt(left[i], t) + centerPoint, smallRad);
//        ofDrawCircle( rotatePt(right[i], t) + centerPoint, smallRad);
    }
}

void October::drawCircle( double time )
{
    for( int i = 0; i < 10; i++ )
    {
        ofDrawCircle( rotatePt( top[i], time) + centerPoint, smallRad / 2);
        ofDrawCircle( rotatePt( bottom[i], time) + centerPoint, smallRad / 2);
        ofDrawCircle( rotatePt( left[i], time) + centerPoint, smallRad / 2);
        ofDrawCircle( rotatePt( right[i], time) + centerPoint, smallRad / 2);

        ofDrawCircle( topCircle[i] + centerPoint, smallRad );
        ofDrawCircle( bottomCircle[i] + centerPoint, smallRad );
        ofDrawCircle( leftCircle[i] + centerPoint, smallRad );
        ofDrawCircle( rightCircle[i] + centerPoint, smallRad );

    }
}

ofPoint October::rotatePt( ofPoint pt, double t ) {

    auto newX = cos(t)*pt.x + sin(t)*pt.y;
    auto newY = -sin(t)*pt.x + cos(t)*pt.y;
    return ofPoint(newX, newY);
}