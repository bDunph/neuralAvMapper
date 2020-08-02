#pragma once

#include <ofMain.h>
#include <ofxMaxim.h>
#include <maximilian.h>
#include <ofxGui.h>
#include <ofxXmlSettings.h>
#include <avObject.hpp>

#define NUMVOICES 2


class ofApp : public ofBaseApp {
    
public:
    void setup();
    void exit();
    void update();
    void draw();
    
    //******** Maxim **********//
    void audioOut(float * output, int bufferSize, int nChannels);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //************ Visuals **********//
    
    ofEasyCam cam;
    
    bool drawGui;
    
    //*********** Maxim *****************//
    
    double sampleRate, bufferSize;
    double * synthOut;
    double finalSig;
    ofxPanel volGui;
    ofxFloatSlider masterVol;
    maxiMix mymix;
    double outputs[2];
    
    //********** Rapidmix ************//
    
    bool trained;
    bool recording;
    avObject av;
    int numVoices;
    
};
