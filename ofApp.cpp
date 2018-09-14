#include "ofApp.h"
#include "SceneSleep.h"
#include "SceneDeco.h"
#include "SceneWish.h"
#include "SceneQrcode.h"
#include "SceneShow.h"



ofColor ofApp::MainColor[5]={ofColor(255,108,230),ofColor(108,255,176),ofColor(108,191,255),ofColor(255,173,108),ofColor(255,108,120)};

//--------------------------------------------------------------
void ofApp::setup(){
	
	loadScene();
	_mode_pre=SceneMode::SLEEP;
	setScene(SceneMode::SLEEP);

	_last_millis=ofGetElapsedTimeMillis();
	_dmillis=0;

	ofAddListener(SceneBase::sceneInFinish,this,&ofApp::onSceneInFinish);
	ofAddListener(SceneBase::sceneOutFinish,this,&ofApp::onSceneOutFinish);

}

//--------------------------------------------------------------
void ofApp::update(){

	_dmillis=ofGetElapsedTimeMillis()-_last_millis;
	_last_millis+=_dmillis;

	if(_in_transition) _scene[_mode_pre]->update(_dmillis);
	_scene[_mode]->update(_dmillis);

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetBackgroundColor(255);

	
	if(_in_transition){
#ifdef DRAW_DEBUG
		_scene[_mode_pre]->drawScaled(true);
#else
		_scene[_mode_pre]->drawScaled(false);
#endif
	}


#ifdef DRAW_DEBUG
		_scene[_mode]->drawScaled(true);
#else
		_scene[_mode]->drawScaled(false);
#endif


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case 'a':
			setScene(SceneMode((_mode+1)%5));
			break;
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
	_scene[_mode]->handleMousePressed(x,y);
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
void ofApp::loadScene(){
	
	_scene[0]=new SceneSleep(this);
	_scene[1]=new SceneWish(this);
	_scene[2]=new SceneDeco(this);
	_scene[3]=new SceneShow(this);
	_scene[4]=new SceneQrcode(this);

}
void ofApp::setScene(SceneMode set_){

	ofLog()<<"set scene: "<<set_;

	_mode_pre=_mode;
	_mode=set_;

	_scene[_mode_pre]->end();
	_scene[_mode]->init();
	
	_in_transition=true;
}

void ofApp::onSceneInFinish(int &e){	
	ofLog()<<"scene in finish!";
	_in_transition=false;
}
void ofApp::onSceneOutFinish(int &e){
	ofLog()<<"scene out finish!";

}