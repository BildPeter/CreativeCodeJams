#include "ofApp.h"
#include <iostream>
#include <string>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAntiAliasing();
    glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
    glPointSize(3);
    
//    // --- Loading files
    ofFileDialogResult openFileResult = ofSystemLoadDialog("Get the txt data", true);
    ofLogNotice()  << "Folder: " << openFileResult.getPath();
    ofDirectory     dirFiles;
    dirFiles.listDir( openFileResult.getPath() );
    ofDrawBitmapString("Loading files", ofGetWidth()/2 - 20, ofGetHeight() / 2 );
    
    for ( int indexOfFile = 0; indexOfFile < dirFiles.size(); ++indexOfFile )
    {
//        ofLogNotice() << "file: " << dirFiles.getPath( indexOfFile );
        ofBuffer buffer = ofBufferFromFile( dirFiles.getPath( indexOfFile ) );
        std::vector< weatherData >     currentWeatherData;
        
        if(buffer.size()) {
            buffer.getNextLine();
            while(buffer.isLastLine() == false) {
                string              line = buffer.getNextLine();
                std::stringstream   lineStream( line );
                string              cell;
                std::getline( lineStream, cell, ';' );
                weatherData data;
                
                std::getline( lineStream, cell, ';' );
                data.lon = ofToDouble( cell );
                std::getline( lineStream, cell, ';' );
                data.lat = ofToDouble( cell );
                std::getline( lineStream, cell, ';' );
                data.temp = ofToDouble( cell );
                std::getline( lineStream, cell, ';' );
                data.velWind = ofToDouble( cell );
                
                currentWeatherData.push_back( data );
//                std::cout << data.lon << "\t" << data.lat << "\t" << data.temp << "\n";
            }
        }
        weatherTimed.weatherDataVector.push_back( currentWeatherData );
        
        // --- transform into pixel vec
        ofMesh  currentMeshTemp, currentMeshWind;
        currentMeshTemp.setMode(OF_PRIMITIVE_POINTS);
        currentMeshWind.setMode(OF_PRIMITIVE_POINTS);
        
        for ( auto &data : weatherTimed.weatherDataVector[ indexOfFile ] )
        {
            data.point = ofVec3f( ofMap( data.lon, 0, 357, 0, 300 ),
                                  ofMap( data.lat, 32, 77, 0, 100),
                                  ofMap( data.temp, 273, 320, 0, 100 ) );
            currentMeshTemp.addColor( ofColor(ofMap( data.temp, 273, 320, 0, 255, true ), 0, 0 ) );
            currentMeshTemp.addVertex( data.point );
            
            currentMeshWind.addColor( ofColor( 0, 0, ofMap( std::abs( data.velWind ), 0, 45, 0, 255, true ) ) );
            currentMeshWind.addVertex( ofVec3f( ofMap( data.lon, 0, 357, 0, 300 ),
                                               ofMap( data.lat, 32, 77, 0, 100),
                                               ofMap( data.velWind, -55, 55, -100, 100 ) ) );
        }
        weatherTimed.meshVecTemp.push_back( currentMeshTemp );
        weatherTimed.meshVecWind.push_back( currentMeshWind );
    }
    
    ofLogNotice() << "Loaded file amount: " << weatherTimed.meshVecTemp.size();

    tempButton.addListener( this, &ofApp::tempPlotActivation );
    windButton.addListener( this, &ofApp::windPlotActivation );
    
    gui.setup();
    gui.add( tempButton.setup( "Temperature Plot", true ) );
    gui.add( windButton.setup("Wind Velocity Plot", false ) );
	gui.add( timeSlider.setup("time", 0, 0, weatherTimed.meshVecTemp.size() - 1 ) );
    gui.add( playButton.setup("play time", false ) );
    gui.add( rotation.setup( "rotation", 0, 0, 360 ) );
    gui.add( autoRotate.setup("Auto Rotate", true ) );
    
    cam.disableMouseInput();
    rotation = 0.0;
    tempPlotActivation();
    
    picturePlot.loadImage("Plot1.png");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (playButton ) {
        if ( ( (ofGetFrameNum() % 10) == 0 ) && ( timeSlider != 0 ) ) {
            timeSlider = (timeSlider + 1) % timeSlider.getMax();
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::lightGrey, ofColor::black, OF_GRADIENT_CIRCULAR);
    picturePlot.draw( ofGetWidth() / 2 - 200 , 30, 400, 200 );
    

    int xPos = (ofGetWidth() / 2 - 200) + ofMap( timeSlider, 0, weatherTimed.meshVecTemp.size(), 0, 400 );
    ofSetLineWidth( 3 );
    ofSetColor( ofColor::black );
    ofDrawArrow( ofVec3f( xPos, 240, 0),
                ofVec3f( xPos, 20, 0) );

    ofSetLineWidth( 1 );
    ofSetColor( ofColor::white );
    ofDrawArrow( ofVec3f( xPos, 240, 0),
                 ofVec3f( xPos, 20, 0) );
    
    cam.begin();
    ofScale(2, 2, 2); // flip the y axis and zoom in a bit
        if ( autoRotate )
        {
            rotation = ( (float)ofGetElapsedTimeMillis() /  500 );
        }
    ofRotateZ( rotation );

    ofTranslate( -150, -50 );

    if (drawGrid) {
//    ofDrawGrid( 300, 1, true, false, false, true );
        ofDrawArrow( ofVec3f( 0, 0, 0 ),  ofVec3f( 300, 0, 0 ) );
        ofDrawArrow( ofVec3f( 0, 0, 0 ),  ofVec3f( 0, 100, 0 ) );
    }
    if (useTemp) {
        weatherTimed.meshVecTemp[ timeSlider ].draw();
    }
    else
    {
        weatherTimed.meshVecWind[ timeSlider ].draw();
    }

    cam.end();

    ofFill();
    ofSetColor( ofColor::white );
    gui.draw();
    
    ofDrawBitmapString( chosenPlot, 40, 180);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch ( key ) {
        case 'a':
             cam.enableMouseInput();
            break;
        case 'f':
            ofSetFullscreen( isFullscreen );
            isFullscreen = !isFullscreen;
            break;
            case 'g':
            drawGrid = !drawGrid;
            break;
        case 's':
            ofSaveFrame();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    cam.disableMouseInput();
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::windPlotActivation()
{
    useTemp     = false;
    useWindVel  = true;
    chosenPlot  = "Wind Plot";
}

void    ofApp::tempPlotActivation()
{
    useWindVel  = false;
    useTemp     = true;
    chosenPlot  = "Temp Plot";
}

//--------------------------------------------------------------
std::vector<std::string> ofApp::getNextLineAndSplitIntoTokens(std::istream& str)
{
    std::vector<std::string>   result;
    std::string                line;
    std::getline(str,line);
    
    std::stringstream          lineStream(line);
    std::string                cell;
    
    while(std::getline(lineStream,cell,';'))
    {
        result.push_back(cell);
    }
    return result;
}