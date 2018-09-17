#pragma once

#ifndef SCENE_SLEEP_H
#define SCENE_SLEEP_H

#include "SceneBase.h"


class SceneSleep:public SceneBase{
	
	ofImage _img_hint;
	FrameTimer _timer_hint;

public:
	SceneSleep(ofApp *set_ptr):SceneBase(set_ptr){
		loadImage();
		_order_scene=0;

		ofAddListener(SceneBase::sceneInFinish,this,&SceneSleep::onSceneInFinish);
	}
	void loadImage(){
		_img_ui[0].loadImage("ui/back/01.png");
		_img_ui[1].loadImage("ui/title/01.png");
		_img_ui[2].loadImage("ui/content/01.png");
		_img_ui[3].loadImage("ui/button/01.png");


		_img_hint.loadImage("ui/content/01-1.png");
		_timer_hint=FrameTimer(1500);


		_button.push_back(ofRectangle(703,2227,641,221));
	}

	void draw(bool debug_){
		SceneBase::draw(debug_);

		float alpha_=255*(1.0-_timer_out[3].val())*_timer_in[3].val();
		ofPushStyle();
		ofSetColor(255,alpha_*(sin(PI*_timer_hint.val())));
			_img_hint.draw(0,0);
		ofPopStyle();
	}
	void update(float dt_){
		SceneBase::update(dt_);

		_timer_hint.update(dt_);
		if(_timer_hint.val()==1){
			_timer_hint.restart();
		}
	}
	
	void buttonEvent(int index){
		_ptr_app->setScene(ofApp::SceneMode::WISH);

	}

	void onSceneInFinish(int &e){	
		if(e==_order_scene) _timer_hint.restart();
	}

	void init(){
		SceneBase::init();
		_timer_hint.reset();
	}
	

};


#endif