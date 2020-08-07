//
//  avObject.hpp
//  regMap
//
//  Created by Bryan Dunphy on 20/02/2017.
//
//

#ifndef avObject_hpp
#define avObject_hpp

#include <stdio.h>
#include <ofxGui.h>
#include <ofxXmlSettings.h>
#include <vector>
#include <ofMain.h>
#include <ofxMaxim.h>
#include <maximilian.h>
#include <random>
#include <ofxRapidLib.h>

#define NUMTAPS 4
#define NUMREGS 5
#define MESHES 2
#define numParams 21
#define numRandParams 22
#define numAvs 5

class avObject {
    
public:
    
    avObject();
    void avSetup(int _numVoices);
    void visual(int _numVouices);
    void drawVisual(int _numVoices);
    double * audio(int _numVoices);
    void randomParams(int _numVoices);
    void trainingExamples(int _numVoices, int _x, int _y);
    bool trainModel(int _numVoices);
    void trainedOutput(int _numVoices, int _x, int _y);
    bool readWrite(int _numVoices);
    void drawPanel(int _numVoices);
    
    double outVertices;
    double outDepthJitter;
    double outVertDist;
    double outLfoFreq;
    double outHarmRatio;
    double outModInd;
    double outControlVoltage;
    double outSawAmp;
    double outSawFreq;
    double outPulseAmp;
    double outPulseDuty;
    double outPulseFreq;
    double outNoiseFiltLowCut;
    double outNoiseFiltHiCut;
    double outCf;
    double outQ;
    double outRes;
    double outAttack;
    double outDecay;
    double outSustain;
    double outRelease;
    
private:
    
    //*************** Gui **************//
    
    ofxPanel gui[numAvs];
    ofxPanel guiRW[NUMREGS];
    
    //*** visuals ***//
    
    ofxIntSlider vertices[numAvs];
    ofxIntSlider depthJitter[numAvs];
    ofxIntSlider vertDist[numAvs];
    ofxIntSlider shape[numAvs];
    
    //*** audio ***//
    ofxToggle FM[numAvs];
    ofxToggle lfoOn[numAvs];
    ofxIntSlider lfoFreq[numAvs];
    ofxIntSlider harmRatio[numAvs];
    ofxFloatSlider modInd[numAvs];
    ofxIntSlider controlVoltage[numAvs];
    ofxFloatSlider sawAmp[numAvs];
    ofxFloatSlider pulseAmp[numAvs];
    ofxFloatSlider pulseDuty[numAvs];
    ofxFloatSlider noiseFiltLowCut[numAvs];
    ofxFloatSlider noiseFiltHiCut[numAvs];
    ofxIntSlider sawFreq[numAvs];
    ofxIntSlider pulseFreq[numAvs];
    ofxIntSlider cf[numAvs];
    ofxIntSlider q[numAvs];
    ofxFloatSlider res[numAvs];
    ofxIntSlider attack[numAvs];
    ofxIntSlider decay[numAvs];
    ofxIntSlider sustain[numAvs];
    ofxIntSlider release[numAvs];
    ofxToggle delaySig[numAvs];
    
    //*** read/write ***//
    ofxIntSlider regNum[numAvs];
    ofxButton saveParams[numAvs];
    ofxButton loadParams[numAvs];
    ofxButton r1[numAvs];
    ofxButton r2[numAvs];
    ofxButton r3[numAvs];
    ofxButton r4[numAvs];
    ofxButton r5[numAvs];
    ofxButton w1[numAvs];
    ofxButton w2[numAvs];
    ofxButton w3[numAvs];
    ofxButton w4[numAvs];
    ofxButton w5[numAvs];
    
    //********* Visual Variables ***********//
    
    ofMesh meshes[numAvs][MESHES];
    vector <int> verts;
    float input, count, currentCount;
    bool selVis, selDrawVis;
    int currentVert, prevVert;
    ofColor cols[numAvs];
    
    //*********** Audio Variables **************//
    
    maxiOsc pulseGen[numAvs];
    maxiOsc sawOsc[numAvs];
    maxiOsc counter[numAvs];
    maxiOsc mod[numAvs];
    maxiOsc lfOsc[numAvs];
    maxiFilter noiseFiltLow[numAvs];
    maxiFilter noiseFiltHi[numAvs];
    maxiFilter hiRes[numAvs];
    maxiFilter loRes[numAvs];
    maxiEnv ampEnv[numAvs];
    maxiDelayline delay[numAvs][NUMTAPS];
    maxiDyn gate[numAvs];
    
    double modulator[numAvs];
    double harmonicity[numAvs];
    double modAmp[numAvs];
    double pulse[numAvs];
    double noiseFilter[numAvs];
    double saw[numAvs];
    double lfo[numAvs];
    double sigMix[numAvs];
    double lowPass[numAvs];
    double hiPass[numAvs];
    double band[numAvs];
    double filteredSig[numAvs];
    double amplitudeEnvelope[numAvs];
    double envOutput[numAvs];
    double gateOut[numAvs];
    double hpc[numAvs];
    double lpc[numAvs];
    double hp[numAvs];
    double lp[numAvs];
    double delRes [numAvs][NUMTAPS];
    double delTot[numAvs];
    int noteTrig[numAvs];
    double outSig[numAvs];
    double * multiOut;
    
    //***************** AV Gui Params ************//
    
    double params[numParams];
    float randParams[numRandParams];
    
    //********** Rapidmix ************//
    
    rapidlib::regression reg[numAvs][NUMREGS];
    std::vector<rapidlib::trainingExample> trainingSet[numAvs];
    bool result;
    bool isTrained;
};

#endif /* avObject_hpp */
