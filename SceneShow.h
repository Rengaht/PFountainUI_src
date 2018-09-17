#pragma once

#ifndef SCENE_SHOW_H
#define SCENE_SHOW_H

#include "SceneBase.h"

class SceneShow:public SceneBase{

	FrameTimer _timer_count;
	FrameTimer _timer_show;
	FrameTimer _timer_blink;

	ofImage _img_number[3];
	ofImage _img_count,_img_show;
	bool _onshow;

	ofSoundPlayer _sound_count;

public:
	SceneShow(ofApp *set_ptr):SceneBase(set_ptr){
		loadImage();
		_order_scene=3;

		_timer_count=FrameTimer(3000);
		_timer_show=FrameTimer(15000);
		_timer_blink=FrameTimer(1000);


		ofAddListener(SceneBase::sceneInFinish,this,&SceneShow::onSceneInFinish);
		

	}
	void loadImage(){
		_img_ui[0].loadImage("ui/back/04.png");
		_img_ui[1].loadImage("ui/title/04.png");
		_img_ui[2].loadImage("ui/content/04.png");
		_img_ui[3].loadImage("ui/button/04.png");

		for(int i=0;i<3;++i){
			_img_number[i].loadImage("ui/"+ofToString(i+1)+".png");
			_img_number[i].setAnchorPercent(.5,.5);
		}

		_img_show.loadImage("ui/show.png");
		_img_show.setAnchorPercent(.5,.5);
		
		_img_count.loadImage("ui/count.png");
		_img_count.setAnchorPercent(.5,.5);

		_sound_count.load("sound/count3.wav");
	}	

	void draw(bool debug_){
		SceneBase::draw(debug_);

		if(_status==SceneStatus::Due){
			
			if(_onshow){
				ofPushStyle();
				ofSetColor(255,255*sin(PI*_timer_blink.val()));
					_img_show.draw(1024,1730);
				ofPopStyle();
			}else{
				//_img_count.draw(1024,);

				int num=ofClamp(floor(_timer_count.val()*3),0,2);
				float v_=_timer_count.val()*3-num;
				ofPushStyle();
				ofSetColor(255,255*sin(PI*v_));
				_img_number[2-num].draw(1024,1730);
				ofPopStyle();
			}
		}
	}
	
	void update(float dt_){
		SceneBase::update(dt_);

		_timer_count.update(dt_);
		if(!_onshow && _timer_count.finish()){
			_onshow=true;
			_timer_show.restart();
			_timer_blink.restart();
		}
		_timer_show.update(dt_);
		if(_status==SceneStatus::Due &&_timer_show.finish()){
			_ptr_app->setScene(ofApp::SceneMode::QRCODE);			
		}

		_timer_blink.update(dt_);
		if(_timer_blink.finish()) _timer_blink.restart();
	}
	
	void init(){
		SceneBase::init();
		_onshow=false;

		_timer_count.reset();
		_timer_show.reset();
	}

	void buttonEvent(int index){


	}
	void onSceneInFinish(int &e){	
		if(e==_order_scene){
			ofLog()<<"scene in finish!";
			_timer_count.restart();
			_sound_count.play();
		}
		
	}

};


#endif