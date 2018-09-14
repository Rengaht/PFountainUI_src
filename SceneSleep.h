#pragma once

#ifndef SCENE_SLEEP_H
#define SCENE_SLEEP_H

#include "SceneBase.h"


class SceneSleep:public SceneBase{

public:
	SceneSleep(ofApp *set_ptr):SceneBase(set_ptr){
		loadImage();
		_order_scene=0;
	}
	void loadImage(){
		_img_ui[0].loadImage("ui/back/01.png");
		_img_ui[1].loadImage("ui/title/01.png");
		_img_ui[2].loadImage("ui/content/01.png");
		_img_ui[3].loadImage("ui/button/01.png");

		_button.push_back(ofRectangle(703,2227,641,221));
	}

	void draw(bool debug_){
		SceneBase::draw(debug_);

	}

	
	void buttonEvent(int index){
		_ptr_app->setScene(ofApp::SceneMode::WISH);

	}

};


#endif