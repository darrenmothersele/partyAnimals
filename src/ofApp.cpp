#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    camFrameRate = 60;
    camWidth  = 640;
    camHeight = 360;
    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();
    
    flipVert = false;
    flipHoriz = true;
    
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(camFrameRate);
    vidGrabber.initGrabber(camWidth,camHeight);
    
    finder.setup("haarcascade_frontalface_default.xml");
    
    // grab first frame
    img.setFromPixels(vidGrabber.getPixelsRef());
    img.mirror(flipVert, flipHoriz);
    finder.findHaarObjects(img);
    
    ofSetVerticalSync(true);
    
    // load mask images
    dir.allowExt("png");
    dir.listDir("masks");
    dir.sort();
    noMasks = dir.numFiles();
    for(int i = 0; i < noMasks; i++){
        ofLogNotice(dir.getPath(i));
        masks.push_back(ofImage());
        masks[i].loadImage(dir.getPath(i));
    }
    
    
    mask.loadImage("masks/chimp.png");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vidGrabber.update();
    if (vidGrabber.isFrameNew()) {
        
        // if video grabber has a new frame
        // grab the image and run face finder
        img.setFromPixels(vidGrabber.getPixelsRef());
        img.mirror(flipVert, flipHoriz);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    finder.findHaarObjects(img, 50, 50);
    
    // draw image to fit the whole screen
    img.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    if (finder.blobs.size() > 0) {
    for(unsigned int i = 0; i < finder.blobs.size(); i++) {
        ofRectangle cur = finder.blobs[i].boundingRect;
        masks[i % noMasks].draw(ofMap(cur.x, 0, camWidth, 0, ofGetWidth()), ofMap(cur.y, 0, camHeight, 0, ofGetHeight()),
                  ofMap(cur.width, 0, camWidth, 0, ofGetWidth()), ofMap(cur.height, 0, camHeight, 0, ofGetHeight()));
    }
    }
    else {
        
        std::random_shuffle ( masks.begin(), masks.end() );
    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    
    screenWidth = w;
    screenHeight = h;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
