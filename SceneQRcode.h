#pragma once

#ifndef SCENE_QRCODE_H
#define SCENE_QRCODE_H

#include "SceneBase.h"

class SceneQrcode:public SceneBase{
	ofSoundPlayer _sound_finish;
public:
	SceneQrcode(ofApp *set_ptr):SceneBase(set_ptr){
		loadImage();
		_order_scene=4;

		ofAddListener(_timer_in[0].finish_event,this,&SceneQrcode::onSceneInFinish);
	}
	void loadImage(){
		_img_ui[0].loadImage("ui/back/05.png");
		_img_ui[1].loadImage("ui/title/05.png");
		_img_ui[2].loadImage("ui/content/05.png");
		_img_ui[3].loadImage("ui/button/05.png");

		_button.push_back(ofRectangle(703,2227,641,221));
		_sound_finish.load("sound/finish.wav");
	}

	void draw(bool debug_){
		SceneBase::draw(debug_);

	}
	
	void buttonEvent(int index){

		_ptr_app->setScene(ofApp::SceneMode::SLEEP);
	}
	void onSceneInFinish(int &e){	
		//if(e==_order_scene){
			_sound_finish.play();
		//}

	}
};


#endif