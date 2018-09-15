#include "ofMain.h"
#include "ofApp.h"

float ofApp::WinScaleX=2.56;
float ofApp::WinScaleY=2.13;
float SceneBase::WinScale=max(ofApp::WinScaleX,ofApp::WinScaleY);

//========================================================================
int main( ){
	ofSetupOpenGL(800,1280,OF_WINDOW);			// <-------- setup the GL context
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN111
	// pass in width and height too:
	ofRunApp(new ofApp());


	
}
