#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // setting http
    url = "http://192.168.3.38:8080/api/posts";
    ofAddListener(httpUtils.newResponseEvent, this, &ofApp::newResponse);
    httpUtils.start();

    // setting twe-lite
    twelite.setup("/dev/tty.usbserial-AHXMUJD0", 115200);
    buff.clear();
    
    analogVal = 0;
    
    // setting gui
    p_gui = new ofxUICanvas(320, ofGetHeight());
    
    p_gui->addSlider("AnalogValue", 0, 5000, &analogVal, 300, 20);
    p_gui->addSlider("PowerValue", 0, 100, &powerVal, 300, 20);
    p_gui->addSlider("EnergyValue", 0, 10, &energyVal, 300, 20);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (twelite.isInitialized() && twelite.available()) {
        unsigned char valChar = twelite.readByte();
        buff += valChar;

        if (buff.c_str()[buff.length() - 1] == '\n') {
            if (buff.c_str()[buff.length() - 2] == '\r') {
                if (buff.c_str()[0] == ':') {
                    if (buff.length() == 51) {
                        string dataStr = buff.substr(1, 48);
                        // cout << dataStr << std::endl;
                        
                        int a0 = ofHexToInt(dataStr.substr(36, 2));
                        int f = ofHexToInt(dataStr.substr(44, 2));
                        int f0 = f & 0x03;
                        
                        analogVal = (a0 * 4 + f0) * 4;
                        powerVal = analogVal * analogVal / 100000;
                        energyVal += powerVal / 3600;
                        
                        // cout << a0 << ":" << f << ":" << analogVal << ":" << powerVal << ":" << energyVal << endl;
                    }
                }
                
                buff.clear();
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
}

void ofApp::newResponse(ofxHttpResponse & response) {
    string responseStr = ofToString(response.status) + ": " + (string)response.responseBody;
    std::cout << responseStr << std::endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 32) {        // 32 is key code of SPACE KEY

        ofxJSONElement json;
        json["device_id"]   = 0;
        json["user_name"]   = "izumida";
        json["lat"]         = 35.41;
        json["lng"]         = 139.41;
        json["solar"]       = energyVal;
        
        cout << json.getRawString() << endl;
        
        ofBuffer buff;
        buff.set(json.getRawString());
    
        httpUtils.postData(
                       url,
                       buff,
                       "application/json"
                       );
    
        // reset energy
        energyVal = 0;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
