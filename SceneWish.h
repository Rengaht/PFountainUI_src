#pragma once

#ifndef SCENE_WISH_H
#define SCENE_WISH_H

#include "SceneBase.h"

class SceneWish:public SceneBase{
	
	ofImage _img_check;
	int _select_color;

public:
	SceneWish(ofApp *set_ptr):SceneBase(set_ptr){
		loadImage();
		_order_scene=1;
		_select_color=0;
	}

	void loadImage(){
		_img_ui[0].loadImage("ui/back/02.png");
		_img_ui[1].loadImage("ui/title/02.png");
		_img_ui[2].loadImage("ui/content/02.png");
		_img_ui[3].loadImage("ui/button/02.png");

		_img_check.loadImage("ui/check.png");
		_img_check.setAnchorPercent(.5,.5);

		_button.push_back(ofRectangle(703,1647,641,221));
		
		for(int i=0;i<5;++i){
			_button.push_back(ofRectangle(641.5+165*i,1292,105,105));
		}

	}


	void draw(bool debug_){
		
		SceneBase::draw(debug_);
		_img_check.draw(694+165*_select_color,1344.5);

	}

	

	void buttonEvent(int index_){
		switch(index_){
			case 0:
				_ptr_app->setScene(ofApp::SceneMode::DECO);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				setColor(index_-1);
				break;
		}
	}
	void setColor(int index_){
		_select_color=index_;
	}
	void init(){
		SceneBase::init();
		_select_color=0;
	}

};


#endif