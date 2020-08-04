#include "ofApp.h"
#include <random>


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofSetFrameRate(24);
    
    numVoices = NUMVOICES;
    //********** Gui ***********//
    
    volGui.setup();
    volGui.add(masterVol.setup("masterVol", 0.5, 0.0, 1.0));
    
    //********************Maxim Setup**********************//
    
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    int current = 0;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2, 2, this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    
    //******* Rapidmix Setup (code from oF example rapidAPI_006) ***************//
    
    trained = false;
    recording = false;
    drawGui = true;
    
    av.avSetup(numVoices);
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    //*********** Maxim *****************//
    
    ofSoundStreamStop();
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    av.visual(numVoices);
    // commented out as trained was being reset to false for testing of chapter 4 text
    //trained = av.readWrite(numVoices);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    stringstream s;
    s << "trained: " << trained;
    ofDrawBitmapString(s.str(), ofGetWidth()*0.33, 10);
    s.str("");
    s << "recording: " << recording;
    ofDrawBitmapString(s.str(), ofGetWidth()*0.66, 10);
    s.str("");
    
    /************ Gui ***********/
    if(drawGui){
        av.drawPanel(numVoices);
        volGui.draw();
    }
    
    /********** Camera & Meshes *********/
    
    float rot = 2 * DEG_TO_RAD * ofGetFrameNum();
    float xPos = cos(rot) * 500;
    float zPos = sin(rot) * 500;
    float yPos = cos(rot) * 500;
    
    ofVec3f camPos;
    ofVec3f lookAtPos;
    
    camPos = ofVec3f(-ofGetWidth()/8 + xPos, -ofGetHeight()/8 + yPos, zPos);
    lookAtPos = ofVec3f(-ofGetWidth()/8, -ofGetHeight()/8, 0);
    
    cam.setPosition(camPos);
    
    cam.lookAt(lookAtPos, ofVec3f(0, 1, 0));
    
    cam.setFov(60);
    cam.setNearClip(1);
    cam.setFarClip(2000);
    
    cam.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/8, -ofGetHeight()/8);
    av.drawVisual(numVoices);
    ofPopMatrix();
    
    cam.end();
    
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        synthOut = av.audio(numVoices);
        
        double synthMix[numVoices];
        
        for(int i = 0; i < numVoices; i++){
            synthMix[i] = *(synthOut+i);
            finalSig += (synthMix[i] / numVoices) * masterVol;
        }
        
        /*** Limiter ***/
        
        if (finalSig > 0.8) {
            finalSig = 0.8;
            mymix.stereo(finalSig, outputs, 0.5);
            
        } else if (finalSig < -0.8) {
            finalSig = -0.8;
            mymix.stereo(finalSig, outputs, 0.5);
        } else {
            mymix.stereo(finalSig, outputs, 0.5);
        }
        
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];
    }
}


//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    
    switch (key) {
            
            /*r*/
        case 114: {
            recording = true;
            break;
        }
            /*t*/
        case 116: {
            trained = av.trainModel(numVoices);
            break;
        }
            /*space*/
        case 32: {
            av.randomParams(numVoices);
            break;
        }
            /*q*/
        case 113: {
            drawGui = !drawGui;
        }
            
    }
    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    //********** Rapidmix (code from oF example rapidAPI_006) ************//
    
    switch (key) {
        case 114:
            recording = false;
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    //********** Rapidmix (code from oF example rapidAPI_006) ************//
    
    if (recording) {
        av.trainingExamples(numVoices, x, y);
        
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    //********** Rapidmix (code from oF example rapidAPI_006) ************//
    
    if (trained) {
        av.trainedOutput(numVoices, x, y);
    }
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    //********** Rapidmix (code from oF example rapidAPI_006) ************//
    
    mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
