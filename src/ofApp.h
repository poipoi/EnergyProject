#pragma once

#include "ofMain.h"

#include "ofxHttpUtils.h"
#include "ofxUI.h"
#include "ofxJSON.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void newResponse(ofxHttpResponse & response);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofSerial twelite;
    string buff;
    float analogVal;
    float powerVal;
    float energyVal;
    
    ofxHttpUtils httpUtils;
    string url;
    
    ofxUICanvas *p_gui;
};
