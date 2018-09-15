#pragma once

#ifndef SCENE_WISH_H
#define SCENE_WISH_H

#include "SceneBase.h"

class SceneWish:public SceneBase{
		
	ofImage _img_check;
	int _select_color;
	
	wstring _wish;
	FrameTimer _timer_text;
	int _index_wish;

public:
	SceneWish(ofApp *set_ptr):SceneBase(set_ptr){

		loadImage();

		_timer_text=FrameTimer(500);
		_order_scene=1;
		_select_color=0;
		

		ofAddListener(SceneBase::sceneInFinish,this,&SceneWish::onSceneInFinish);

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

		float alpha_=255*(1.0-_timer_out[3].val());
		
		string str_=_ptr_app->ws2s(_wish.substr(0,_index_wish));
		auto bound_=_ptr_app->_font_wish.getStringBoundingBox(str_,0,0);
		
		ofPushMatrix();
		ofTranslate(1024,890);
		ofScale(.45,.5);
		ofTranslate(-bound_.width/2,0);
		ofPushStyle();
		
		ofSetColor(ofApp::MainColor[_select_color],alpha_);
		_ptr_app->_font_wish.drawString(str_,0,0);
		ofPopStyle();
		
		ofPopMatrix();


		_img_check.draw(694+165*_select_color,1344.5);

	}
	void update(float dt_){
		SceneBase::update(dt_);
		
		_timer_text.update(dt_);
		if(_timer_text.val()==1 && _index_wish<_wish.length()){
			_index_wish++;
			_timer_text.restart();			
		}
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
		_timer_text.reset();
		
		_wish=L"連續放三個暑假!!!YA!!!";//_ptr_app->ws2s(L"連續放三個暑假!!!YA!!!");
		_index_wish=0;

	}
	void end(){
		SceneBase::end();
		_ptr_app->_user_color_wish=_select_color;
		_ptr_app->_user_wish=_wish;
	}

	void onSceneInFinish(int &e){	
		if(e==_order_scene) _timer_text.restart();
	}
	
};


#endif