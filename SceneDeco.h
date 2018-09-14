#pragma once

#ifndef SCENE_DECO_H
#define SCENE_DECO_H

#include "SceneBase.h"

class SceneDeco:public SceneBase{

	int _select_color;
	int _select_icon;
	ofImage _img_icon[5];
	ofImage _img_check;
	

public:
	SceneDeco(ofApp *set_ptr):SceneBase(set_ptr){
		loadImage();
		_order_scene=2;

		_select_color=0;
		_select_icon=0;
	}

	void loadImage(){
		_img_ui[0].loadImage("ui/back/03.png");
		_img_ui[1].loadImage("ui/title/03.png");
		_img_ui[2].loadImage("ui/content/03.png");
		_img_ui[3].loadImage("ui/button/03.png");

		for(int i=0;i<5;++i){
			_img_icon[i].loadImage("ui/icon-"+ofToString(i+1)+".png");
			_img_icon[i].setAnchorPercent(.5,.5);
		}
		_img_check.loadImage("ui/check.png");
		_img_check.setAnchorPercent(.5,.5);

		_button.push_back(ofRectangle(703,2248,641,221));
		for(int i=0;i<5;++i){
			_button.push_back(ofRectangle(108,921+167*i,121,121));
		}
		for(int i=0;i<5;++i){
			_button.push_back(ofRectangle(1819,921+167*i,121,121));
		}
		// undo & redo
		_button.push_back(ofRectangle(371,1862,150,150));
		_button.push_back(ofRectangle(1523,1862,150,150));

	}


	void draw(bool debug_=false){
		SceneBase::draw(debug_);

		float alpha_=255*_timer_in[3].eval()*(1-_timer_out[3].eval());
		ofPushStyle();
		ofSetColor(255,alpha_);

		ofPushStyle();
		ofSetColor(ofApp::MainColor[_select_color],alpha_);
		for(int i=0;i<5;++i){
			_img_icon[i].draw(1879.5,981.5+167*i);
		}
		ofPopStyle();
		
		_img_check.draw(168.5,981.5+167*_select_color);
		_img_check.draw(1879.5,981.5+167*_select_icon);

		ofPopStyle();
	}


	void buttonEvent(int index_){
		switch(index_){
			case 0:
				_ptr_app->setScene(ofApp::SceneMode::SHOW);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				setColor(index_-1);
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				setIcon(index_-6);
				break;
			case 11:
				redoStep();
				break;
			case 12:
				undoStep();
				break;
		}
	
	}

	void init(){
		SceneBase::init();
		_select_color=0;
		_select_icon=0;	
	}
	void setColor(int index_){
		_select_color=index_;
	}
	void setIcon(int index_){
		_select_icon=index_;
	}
	void redoStep(){
	
	}
	void undoStep(){
	
	}

};


#endif