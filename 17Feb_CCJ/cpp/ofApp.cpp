#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    sender.setup( "127.0.0.1", 5000 );
    receiver.setup( 6000 );

    textFont.load( "MISFITS_.TTF", 40 );

    gui.setup();
    gui.add( textLength.setup( "Length", 60, 0, 150 ) );
    gui.add( textShift.setup( "Shift", 20, 0, 50 ) );
    gui.add( textMovementHight.setup( "Hight", 20, 0, 50 ) );
    gui.add( textMovementSpeed.setup( "Speed", 5, 0, 20 ) );
}

//--------------------------------------------------------------
void ofApp::update()
{
    while ( receiver.hasWaitingMessages() )
    {
        ofxOscMessage message;
        receiver.getNextMessage( message );
        if ( message.getAddress() == adressText )
        {
            textCurrent = message.getArgAsString( 0 );
            ofLogNotice() << "Text received: " << textCurrent;
            string cmd = "say -v Markus " + textCurrent + " &";   // create the command
            system(cmd.c_str());
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground( ofColor::black );

    auto shiftTotal = 0;
    int idLetter = 0;
    
    for ( auto &letter : textCurrent ) {
        auto parameter = ofGetElapsedTimef() + idLetter;
        float yAddText = (float)( ofNoise( parameter * textMovementSpeed ) - 0.5 ) * textMovementHight;
//        auto width = textFont.getStringBoundingBox( ofToString( letter ), 0, 0 ).getWidth();

        ofPushMatrix(); // TODO use ofNode()
        {
            ofRotate( yAddText );
            ofTranslate( xText + shiftTotal, yText + yAddText );
            textFont.drawString( ofToString( letter ), 0, 0 );
        }
        ofPopMatrix();

        shiftTotal += textShift;
        
        idLetter++;
    }

    if ( showGui )
    {
        gui.draw();
    }
}

void ofApp::keyPressed( int key )
{
    if ( key == 's' )
    {
        ofxOscMessage message;
        message.setAddress( adressCreate );
        message.addIntArg( textLength );
        sender.sendMessage( message );
        ofLogNotice() << "Message sent: " << message.getArgAsString( 0 );
    }

    if ( key == 'F' )
    {
        ofToggleFullscreen();
        yText = ofGetHeight() / 2;
    }

    if ( key == 'g' ) { showGui = !showGui; }
}
