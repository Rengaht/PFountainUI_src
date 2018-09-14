#include "SceneBase.h"
#include "ofApp.h"


ofEvent<int> SceneBase::sceneInFinish=ofEvent<int>();
ofEvent<int> SceneBase::sceneOutFinish=ofEvent<int>();


SceneBase::SceneBase(ofApp *set_ptr){

	_ptr_app=set_ptr;
	
	float due=400;
	float delay=350;

	for(int i=0;i<4;++i){
		_timer_in[i]=FrameTimer(due,i*delay+delay*2);
		_timer_out[i]=FrameTimer(due,(3-i)*delay);
	}
	

}
SceneBase::~SceneBase(){

}
void SceneBase::drawScaled(bool debug_){

	ofPushMatrix();
	ofScale(1.0/WinScale,1.0/WinScale);
		draw(debug_);
	ofPopMatrix();
}
void SceneBase::draw(bool debug_){

	for(int i=0;i<4;++i){
		
		ofPushStyle();
		ofSetColor(255,255*_timer_in[i].eval()*(1-_timer_out[i].eval()));
		
			_img_ui[i].draw(0,0);
	
		ofPopStyle();
	
	}

	if(debug_){
		ofPushStyle();
		ofSetColor(0,255,0);
		ofNoFill();
		for(auto &r:_button){
			ofDrawRectangle(r);
		}
		ofPopStyle();
	}
	


}

void SceneBase::init(){
	
	for(int i=0;i<4;++i){
		_timer_out[i].reset();
		_timer_in[i].restart();
	}
	_status=SceneStatus::Init;
	_trigger_in=false;
	_trigger_out=false;
}

void SceneBase::end(){

	for(int i=0;i<4;++i) _timer_out[i].restart();
	_status=SceneStatus::End;

}

void SceneBase::update(float dt_){

	switch(_status){
		case Init:
			for(int i=0;i<4;++i) _timer_in[i].update(dt_);
			if(_timer_in[3].finish()){
				_status=Due;
				if(!_trigger_in){
					ofNotifyEvent(sceneInFinish,_order_scene,this);
					_trigger_in=true;
				}
			}
			break;
		case End:
			for(int i=0;i<4;++i) _timer_out[i].update(dt_);
			if(_timer_out[0].finish()){
				if(!_trigger_out){
					ofNotifyEvent(sceneOutFinish,_order_scene,this);		
					_trigger_out=true;
				}
			}
			break;
		case Due:

			break;
	}
}

void SceneBase::reset(){
	for(int i=0;i<4;++i){
		_timer_in[i].reset();
		_timer_out[i].reset();
	}
}

void SceneBase::handleMousePressed(float mouse_x,float mouse_y){
	
	if(_status!=SceneStatus::Due) return;
	
	float scalex=mouse_x*WinScale;
	float scaley=mouse_y*WinScale;

	int len=_button.size();
	for(int i=0;i<len;++i){
		if(_button[i].inside(scalex,scaley)){
			buttonEvent(i);
		}
	}
}