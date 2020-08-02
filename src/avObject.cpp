//
//  avObject.cpp
//  regMap
//
//  Created by Bryan Dunphy on 20/02/2017.
//
//

#include <avObject.hpp>

avObject::avObject(){
}

void avObject::avSetup(int _numVoices){
    
    int numVoices = _numVoices;
    
    //*************** GUI Setup ******************//
    
    for(int i = 0; i < numVoices; i++){
        gui[i].setup();
        gui[i].add(vertices[i].setup("vertices"+ofToString(i), 5, 0, 10));
        gui[i].add(depthJitter[i].setup("depthJitter"+ofToString(i), 0, 0, 1000));
        gui[i].add(vertDist[i].setup("vertDist"+ofToString(i), 350, 0, 700));
        gui[i].add(shape[i].setup("shape"+ofToString(i), 1, 0, 1));
        
        gui[i].add(FM[i].setup("FM"+ofToString(i), true));
        gui[i].add(lfoOn[i].setup("lfoOn"+ofToString(i), true));
        gui[i].add(lfoFreq[i].setup("lfoFreq"+ofToString(i), 10, 0, 50));
        gui[i].add(harmRatio[i].setup("harmRatio"+ofToString(i), 10, 0, 100));
        gui[i].add(modInd[i].setup("modInd"+ofToString(i), 0.5, 0.0, 5.0));
        gui[i].add(controlVoltage[i].setup("controlVoltage"+ofToString(i), 1, 0, 100));
        gui[i].add(sawAmp[i].setup("sawAmp"+ofToString(i), 0.25, 0.0, 0.5));
        gui[i].add(sawFreq[i].setup("sawFreq"+ofToString(i), 200, 0, 500));
        gui[i].add(pulseAmp[i].setup("pulseAmp"+ofToString(i), 0.25, 0.0, 0.5));
        gui[i].add(pulseDuty[i].setup("pulseDuty"+ofToString(i), 0.5, 0.0, 1.0));
        gui[i].add(pulseFreq[i].setup("pulseFreq"+ofToString(i), 5, 0, 500));
        gui[i].add(noiseFiltLowCut[i].setup("noisefiltLowCut"+ofToString(i), 0.2, 0.0, 1.0));
        gui[i].add(noiseFiltHiCut[i].setup("noiseFiltHiCut"+ofToString(i), 0.7, 0.0, 1.0));
        gui[i].add(cf[i].setup("cf"+ofToString(i), 500, 20, 10000));
        gui[i].add(q[i].setup("q"+ofToString(i), 10, 2, 50));
        gui[i].add(res[i].setup("res"+ofToString(i), 2.0, 1.0, 20.0));
        gui[i].add(attack[i].setup("attack"+ofToString(i), 300, 0, 3000));
        gui[i].add(decay[i].setup("decay"+ofToString(i), 1, 1, 500));
        gui[i].add(sustain[i].setup("sustain"+ofToString(i), 1, 1, 1000));
        gui[i].add(release[i].setup("release"+ofToString(i), 1000, 0, 3000));
        gui[i].add(delaySig[i].setup("delaySig"+ofToString(i), true));
        
        guiRW[i].setup();
        guiRW[i].add(saveParams[i].setup("saveParams"+ofToString(i), 20, 20));
        guiRW[i].add(loadParams[i].setup("loadParams"+ofToString(i), 20, 20));
        guiRW[i].add(regNum[i].setup("regNum"+ofToString(i), 0, 0, 4));
        guiRW[i].add(r1[i].setup("r1"+ofToString(i), 20, 20));
        guiRW[i].add(r2[i].setup("r2"+ofToString(i), 20, 20));
        guiRW[i].add(r3[i].setup("r3"+ofToString(i), 20, 20));
        guiRW[i].add(r4[i].setup("r4"+ofToString(i), 20, 20));
        guiRW[i].add(r5[i].setup("r5"+ofToString(i), 20, 20));
        guiRW[i].add(w1[i].setup("w1"+ofToString(i), 20, 20));
        guiRW[i].add(w2[i].setup("w2"+ofToString(i), 20, 20));
        guiRW[i].add(w3[i].setup("w3"+ofToString(i), 20, 20));
        guiRW[i].add(w4[i].setup("w4"+ofToString(i), 20, 20));
        guiRW[i].add(w5[i].setup("w5"+ofToString(i), 20, 20));
        
        
        
        
        //************** Audio Setup ****************//
        
        
        hpc[i] = 0;
        lpc[i] = 0;
        hp[i] = 0;
        lp[i] = 0;
        
        
        
        ampEnv[i].setAttack(attack[i]);
        ampEnv[i].setDecay(decay[i]);  // Needs to be at least 1
        ampEnv[i].setSustain(sustain[i]);
        ampEnv[i].setRelease(release[i]);
        
        
        //*************** Visual Setup ****************//
        
        for(int j=0; j<MESHES; ++j){
            meshes[i][j].setMode(OF_PRIMITIVE_LINES);
            meshes[i][j].enableColors();
            meshes[i][j].enableIndices();
        }
        
    }
    selVis = false;
    selDrawVis = false;
    result = false;
    isTrained = false;
    
}

void avObject::visual (int _numVoices){
    
    int numVoices = _numVoices;
    
    for(int i = 0; i < numVoices; i++){
        
        if(shape[i] == 0){
            
            /********* Cube **********/
            
            for(int x=0; x<vertices[i]; ++x){
                for(int y=0; y<vertices[i]; ++y){
                    for(int z=0; z<vertices[i]; ++z){
                        int jit = ofRandom(-depthJitter[i], depthJitter[i]);
                        float xPos, yPos, zPos;
                        int offset = 50;
                        xPos = x * offset + jit;
                        yPos = y * offset + jit;
                        zPos = z * offset + jit;
                        ofVec3f vertex(xPos, yPos, zPos);
                        meshes[i][selVis].addVertex(vertex);
                        meshes[i][selVis].addColor(ofColor(ofRandom(50, 100), ofRandom(100, 200), ofRandom(50, 150)));
                    }
                }
            }
            
        } else if(shape[i] == 1){
            
            /********* Sphere ***********/
            
            /**** code from https://github.com/nicohsieh/sphere-freq/blob/master/src/testApp.cpp ***/
            
            int radius = 250;
            meshes[i][selVis].addVertex(ofVec3f(0,0,1*radius));
            
            for (int j=1; j<vertices[i]; j++) {
                double xPos, yPos, zPos;
                double phi = PI * double(j)/(vertices[i]);
                double cosPhi = cos(phi);
                double sinPhi = sin(phi);
                for (int k=0; k<vertices[i]; k++) {
                    float jitter = ofRandom(-depthJitter[i], depthJitter[i]);
                    double theta = TWO_PI * double(k)/(vertices[i]);
                    xPos = cos(theta)*sinPhi*radius + jitter;
                    yPos = sin(theta)*sinPhi*radius + jitter;
                    zPos = cosPhi*radius + jitter;
                    meshes[i][selVis].addColor(ofColor(ofRandom(50, 100), ofRandom(100, 200), ofRandom(50, 150)));
                    meshes[i][selVis].addVertex(ofVec3f(xPos, yPos, zPos));
                    
                }
            }
            meshes[i][selVis].addVertex(ofVec3f(0,0,-1*radius));
        }
        
        //********* From ofBook Graphics Mesh Tutorial *********//
        float connectionDistance = vertDist[i];
        int numVerts = meshes[i][selVis].getNumVertices();
        for (int a=0; a<numVerts; ++a) {
            ofVec3f verta = meshes[i][selVis].getVertex(a);
            for (int b=a+1; b<numVerts; ++b) {
                ofVec3f vertb = meshes[i][selVis].getVertex(b);
                float distance = verta.distance(vertb);
                if (distance <= connectionDistance) {
                    // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
                    // connected to form a line
                    meshes[i][selVis].addIndex(a);
                    meshes[i][selVis].addIndex(b);
                }
            }
        }
    }
    
    selVis = !selVis;
    
}

void avObject::drawVisual(int _numVoices){
    
    int numVoices = _numVoices;
    
    for(int i = 0; i < numVoices; i++){
        meshes[i][selDrawVis].draw();
        meshes[i][selDrawVis].clear();
    }
    
    selDrawVis = !selDrawVis;
}

double * avObject::audio(int _numVoices){
    
    int numVoices = _numVoices;
    
    for(int i = 0; i < numVoices; i++){
        
        ampEnv[i].setAttack(attack[i]);
        ampEnv[i].setDecay(decay[i]);  // Needs to be at least 1
        ampEnv[i].setSustain(sustain[i]);
        ampEnv[i].setRelease(release[i]);
        
        /********* Synth ****************/
        
        delColl[i] = 0;
        filteredSig[i] = 0;
        
        /*** Oscillators ***/
        
        if(FM[i] && lfoOn[i]){
            lfo[i] = lfOsc[i].sinewave(lfoFreq[i]);
            harmonicity[i] = sawFreq[i] * (harmRatio[i] * lfo[i]);
            modAmp[i] = harmonicity[i] * (modInd[i] * lfo[i]);
            modulator[i] = mod[i].sinewave(harmonicity[i]) * modAmp[i];
            saw[i] = sawOsc[i].square(modulator[i] + sawFreq[i]) * sawAmp[i];
            pulse[i] = pulseGen[i].pulse(pulseFreq[i] + saw[i], pulseDuty[i] * lfo[i]) * pulseAmp[i];
        } else if (FM[i] && !lfoOn[i]){
            harmonicity[i] = sawFreq[i] * harmRatio[i];
            modAmp[i] = harmonicity[i] * modInd[i];
            modulator[i] = mod[i].sinewave(harmonicity[i]) * modAmp[i];
            saw[i] = sawOsc[i].square(modulator[i] + sawFreq[i]) * sawAmp[i];
            pulse[i] = pulseGen[i].pulse(pulseFreq[i] + saw[i], pulseDuty[i]) * pulseAmp[i];
        } else {
            saw[i] = sawOsc[i].saw(sawFreq[i]) * sawAmp[i];
            pulse[i] = pulseGen[i].pulse(pulseFreq[i], pulseDuty[i]) * pulseAmp[i];
        }
        
        sigMix[i] = (saw[i] + pulse[i]) * 0.5;
        
        /*** Filters & Envelopes ***/
        
        hiPass[i] = noiseFiltHi[i].hipass(sigMix[i], noiseFiltHiCut[i]);
        
        lowPass[i] = noiseFiltLow[i].lopass(sigMix[i], noiseFiltLowCut[i]);
        
        hpc[i] = (double)cf[i] + ((double)q[i] * 0.5);
        lpc[i] = (double)cf[i] - ((double)q[i] * 0.5);
        
        hp[i] = hiRes[i].hires(sigMix[i], hpc[i], (double)res[i]);
        lp[i] = loRes[i].lores(sigMix[i], lpc[i], (double)res[i]);
        
        band[i] = (hp[i] + lp[i]) * 0.5;
        
        filteredSig[i] = (hiPass[i] + lowPass[i] + band[i]) * 0.33f;
        
        amplitudeEnvelope[i]=ampEnv[i].adsr(1.,ampEnv[i].trigger);
        
        noteTrig[i]=counter[i].phasor(controlVoltage[i], 1, 9);//phasor can take three arguments; frequency, start value and end value.
        
        if (noteTrig[i]==1) ampEnv[i].trigger=1; //trigger the envelope
        
        else ampEnv[i].trigger=0;//release the envelope to make it fade out only if it's been triggered
        
        /*** Delay ***/
        
        if(delaySig[i]){
            
            for(int j=0; j<NUMTAPS; ++j){
                delBoy[i][j] = delay[i][j].dl(filteredSig[i], 4100*i, 0.8);
                delColl[i] += delBoy[i][j];
            }
            envOutput[i] = (filteredSig[i] + delColl[i]) * amplitudeEnvelope[i] * 0.5;
        } else {
            envOutput[i] = filteredSig[i] * amplitudeEnvelope[i];
        }
        
        outSig[i] = envOutput[i];
        
    }
    
    multiOut = &outSig[0];
    return multiOut;
    
}

void avObject::randomParams(int _numVoices){
    
    int numVoices = _numVoices;
    
    //********** Random Visual *************//
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    for(int i = 0; i < numVoices; i++){
        vertices[i] = abs(10 * distribution(generator));
        if(vertices[i] <= 1){
            vertices[i] = 2;
        }
        
        depthJitter[i] = abs(1000 * distribution(generator));
        
        vertDist[i] = abs(700 * distribution(generator));
        
        shape[i] = rand() % 2;
        
        //************ Random Audio ****************//
        
        lfoFreq[i] = abs(50 * distribution(generator));
        
        harmRatio[i] = abs(100 * distribution(generator));
        
        modInd[i] = 5.0 * distribution(generator);
        
        controlVoltage[i] = abs(100 * distribution(generator));
        if (controlVoltage[i] <= 1){
            controlVoltage[i] = 1;
        }
        
        sawAmp[i] = 0.5 * distribution(generator);
        
        sawFreq[i] = abs(500 * distribution(generator));
        
        pulseAmp[i] = 0.5 *  distribution(generator);
        
        pulseDuty[i] = distribution(generator);
        
        pulseFreq[i] = abs(500 * distribution(generator));
        
        noiseFiltLowCut[i] = distribution(generator);
        if (noiseFiltLowCut[i] <= 0.01){
            noiseFiltLowCut[i] = 0.01;
        }
        
        noiseFiltHiCut[i] = distribution(generator);
        if (noiseFiltHiCut[i] <= 0.01){
            noiseFiltHiCut[i] = 0.01;
        }
        
        cf[i] = abs(10000 * distribution(generator));
        if (cf[i] <= 1){
            cf[i] = 1;
        }
        
        q[i] = abs(50 * distribution(generator));
        if (q[i] <= 1){
            q[i] = 1;
        }
        
        res[i] = 20.0 * distribution(generator);
        if (res[i] <= 1.0){
            res[i] = 1.0;
        }
        
        attack[i] = abs(3000 * distribution(generator));
        if (attack[i] <= 1){
            attack[i] = 1;
        }
        
        decay[i] = abs(500 * distribution(generator));
        if (decay[i] <= 1){
            decay[i] = 1;
        }
        
        sustain[i] = abs(1000 * distribution(generator));
        if (sustain[i] <= 1){
            sustain[i] = 1;
        }
        
        release[i] = abs(3000 * distribution(generator));
        if (release[i] <= 1){
            release[i] = 1;
        }
        
    }
}

void avObject::trainingExamples(int _numVoices, int _x, int _y){
    
    int numVoices = _numVoices;
    int x = _x;
    int y = _y;
    
    for(int i = 0; i < numVoices; i++){
        trainingExample tempExample[numVoices];
        tempExample[i].input = {double(x), double(y)};
        tempExample[i].output = {(double) vertices[i], (double) depthJitter[i], (double) vertDist[i], (double) lfoFreq[i], (double) harmRatio[i], (double) modInd[i], (double) controlVoltage[i], (double) sawAmp[i], (double) sawFreq[i], (double) pulseAmp[i], (double) pulseDuty[i], (double) pulseFreq[i], (double) noiseFiltLowCut[i], (double) noiseFiltHiCut[i], (double) cf[i], (double) q[i], (double) res[i], (double) attack[i], (double) decay[i], (double) sustain[i], (double) release[i]};
        trainingSet[i].push_back(tempExample[i]);
    }
}

bool avObject::trainModel(int _numVoices){
    
    int numVoices = _numVoices;
    
    for(int i = 0; i < numVoices; i++){
        result = reg[i][regNum[i]].train(trainingSet[i]);
    }
    
    return result;
}

void avObject::trainedOutput(int _numVoices, int _x, int _y){
    int numVoices = _numVoices;
    int x = _x;
    int y = _y;
    std::vector<double> input[numVoices];
    std::vector<double> output[numVoices];
    
    for(int i = 0; i < numVoices; i++){
        
        input[i].push_back (double(x));
        input[i].push_back (double(y));
        output[i] = reg[i][regNum[i]].process(input[i]);
        
        vertices[i] = output[i][0];
        if (output[i][0] < 2){
            vertices[i] = 2;
        }
        
        depthJitter[i] = output[i][1];
        if (output[i][1] < 0){
            depthJitter[i] = 0;
        }
        
        vertDist[i] = output[i][2];
        if (output[i][2] < 0){
            vertDist[i] = 0;
        }
        
        lfoFreq[i] = output[i][3];
        if (output[i][3] < 0){
            lfoFreq[i] = 0;
        }
        
        harmRatio[i] = output[i][4];
        if (output[i][4] < 0){
            harmRatio[i] = 0;
        }
        
        modInd[i] = output[i][5];
        if (output[i][5] < 0){
            modInd[i] = 0;
        }
        
        controlVoltage[i] = output[i][6];
        if (output[i][6] < 1){
            controlVoltage[i] = 1;
        }
        
        sawAmp[i] = output[i][7];
        if (output[i][7] < 0.1){
            sawAmp[i] = 0.1;
        } else if (output[i][7] > 0.5){
            sawAmp[i] = 0.5;
        }
        
        sawFreq[i] = output[i][8];
        if (output[i][8] < 0){
            sawFreq[i] = 0;
        }
        
        pulseAmp[i] = output[i][9];
        if(output[i][9] < 0.1){
            pulseAmp[i] = 0.1;
        } else if (output[i][9] > 0.5){
            pulseAmp[i] = 0.5;
        }
        
        pulseDuty[i] = output[i][10];
        if (output[i][10] < 0){
            pulseDuty[i] = 0;
        }
        
        pulseFreq[i] = output[i][11];
        if (output[i][11] < 0){
            pulseFreq[i] = 0;
        }
        
        noiseFiltLowCut[i] = output[i][12];
        if (output[i][12] < 0.01){
            noiseFiltLowCut[i] = 0.01;
        }
        
        noiseFiltHiCut[i] = output[i][13];
        if (output[i][13] < 0.01){
            noiseFiltHiCut[i] = 0.01;
        }
        
        cf[i] = output[i][14];
        if (output[i][14] < 1){
            cf[i] = 1;
        }
        
        q[i] = output[i][15];
        if(output[i][15] < 1){
            q[i]= 1;
        } else if(output[i][15] > 50){
            q[i] = 50;
        }
        
        res[i] = output[i][16];
        if(output[i][16] < 1.0){
            res[i] = 1.0;
        } else if (output[i][16] > 20.0){
            res[i] = 20.0;
        }
        
        attack[i] = output[i][17];
        if (output[i][17] < 1){
            attack[i] = 1;
        }
        
        decay[i] = output[i][18];
        if (output[i][18] < 1){
            decay[i]= 1;
        }
        
        sustain[i] = output[i][19];
        if (output[i][19] < 1){
            sustain[i] = 1;
        }
        
        release[i] = output[i][20];
        if (output[i][20] < 1){
            release[i] = 1;
        }
        
    }
    
}

bool avObject::readWrite(int _numVoices){
    
    int numVoices = _numVoices;
    
    for(int i = 0; i < numVoices; i++){
        
        int currentReg = regNum[i];
        
        if(saveParams[i]) {gui[i].saveToFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/avParams_"+ofToString(i)+"_"+ofGetTimestampString()+".xml");}
        if(loadParams[i]) {gui[i].loadFromFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/avParams_"+ofToString(i)+"_"+ofToString(currentReg)+".xml");}
        
        if(r1[i]) {isTrained = reg[i][regNum[i]].readJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/newTestReg1_"+ofToString(i)+".JSON");}
        if(r2[i]) {isTrained = reg[i][regNum[i]].readJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/newTestReg2_"+ofToString(i)+".JSON");}
        if(r3[i]) {isTrained = reg[i][regNum[i]].readJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/newTestReg3_"+ofToString(i)+".JSON");}
        if(r4[i]) {isTrained = reg[i][regNum[i]].readJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/newTestReg4_"+ofToString(i)+".JSON");}
        if(r5[i]) {isTrained = reg[i][regNum[i]].readJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/newTestReg5_"+ofToString(i)+".JSON");}
        
        if(w1[i]) {reg[i][regNum[i]].writeJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/newTestReg1_"+ofToString(i)+".JSON");}
        if(w2[i]) {reg[i][regNum[i]].writeJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/newTestReg2_"+ofToString(i)+".JSON");}
        if(w3[i]) {reg[i][regNum[i]].writeJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/newTestReg3_"+ofToString(i)+".JSON");}
        if(w4[i]) {reg[i][regNum[i]].writeJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/newTestReg4_"+ofToString(i)+".JSON");}
        if(w5[i]) {reg[i][regNum[i]].writeJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/postUpgrade/newTestReg5_"+ofToString(i)+".JSON");}
    }
    
    return isTrained;
    
}

void avObject::drawPanel(int _numVoices){
    
    int numVoices = _numVoices;
    
    for(int i = 0; i < numVoices; i++){
        
        gui[i].draw();
        guiRW[i].draw();
    }
    
}
