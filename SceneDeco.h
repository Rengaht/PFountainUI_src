#pragma once

#ifndef SCENE_DECO_H
#define SCENE_DECO_H

#include "SceneBase.h"
#include "DecoStep.h"

class SceneDeco:public SceneBase{

	int _select_color;
	int _select_icon;
	ofImage _img_icon[5];
	ofImage _img_check;
	ofImage _img_mask;
	
	vector<DecoStep> _step_record;
	int _index_step;

	ofVec2f _pos_center;
	float _rad_in,_rad_out,_rad_text;

	wstring _wish;
	int _color_wish;
	int _index_wish;
	FrameTimer _timer_text;

public:
	SceneDeco(ofApp *set_ptr):SceneBase(set_ptr){
		loadImage();
		_order_scene=2;

		_select_color=0;
		_select_icon=0;
		
		_pos_center=ofVec2f(1024,1301);
		_rad_in=269;
		_rad_out=722;
		_rad_text=550;

		_timer_text=FrameTimer(100);

		ofAddListener(SceneBase::sceneInFinish,this,&SceneDeco::onSceneInFinish);

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

		_img_mask.loadImage("ui/mask.png");
		_img_mask.setAnchorPercent(.5,.5);

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

		// canvas
		_button.push_back(ofRectangle(302,579,1444,1444));

	}


	void draw(bool debug_=false){


		for(int i=0;i<4;++i){

			float alpha_=255*_timer_in[i].eval()*(1-_timer_out[i].eval());

			ofPushStyle();
			ofSetColor(255,alpha_);

				if(i==2) drawCanvas(alpha_);
				_img_ui[i].draw(0,0);				
				if(i==2) drawButton(alpha_);				

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
	void drawCanvas(float alpha_){
		ofPushMatrix();
		ofTranslate(_pos_center);

		ofPushStyle();
		ofSetColor(0,alpha_);
		ofDrawCircle(0,0,722);
		ofPopStyle();

		ofPushStyle();
		
		// wish
		int len=_wish.length();
		float ang_=-360.0/len;
		for(int i=0;i<_index_wish;++i){

			if(i==_index_wish-1) 
				ofSetColor(ofApp::MainColor[_color_wish],alpha_*_timer_text.val());
			else 
				ofSetColor(ofApp::MainColor[_color_wish],alpha_);
			ofPushMatrix();
			ofRotate(ang_*i);
			ofTranslate(0,_rad_text);
			auto str_=_ptr_app->ws2s(_wish.substr(i,1));
			auto rect_=_ptr_app->_font_wish.getStringBoundingBox(str_,0,0);

			auto pt_=rect_.getCenter();
			auto br_=rect_.getBottomLeft();
			//ofTranslate(0,-pt_.y);
			//ofRotate(-90);
			//ofTranslate(-pt_.x,0);
			//	//ofDrawRectangle(rect_);
			//	ofDrawAxis(100);
				_ptr_app->_font_wish.drawString(str_,-pt_.x,0);
			ofPopMatrix();
		}
		/*ofPushStyle();
		ofSetColor(255,0,0);
		ofNoFill();
			ofDrawCircle(0,0,_rad_text);
		ofPopStyle();*/

		ofPopStyle();

		
		for(int i=0;i<_index_step;++i){

			ofPushStyle();
			ofSetColor(ofApp::MainColor[_step_record[i]._color],alpha_);

			ofPushMatrix();
			ofTranslate(_step_record[i]._pos);
			ofRotate(_step_record[i]._ang);
				_img_icon[_step_record[i]._icon].draw(0,0);
			ofPopMatrix();

			ofPopStyle();
		}
		_img_mask.draw(0,0);

		ofPopMatrix();

	}
	void drawButton(float alpha_){
		ofPushStyle();
		ofSetColor(255,alpha_);

		for(int i=0;i<5;++i){
			ofPushStyle();
			ofSetColor(ofApp::MainColor[i],alpha_);
				ofDrawCircle(168.5,981.5+167*i,60.5);
			ofPopStyle();
		}


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
			case 13:
				addStep(_mouse_pos);
				break;
		}
	
	}

	void init(){
		SceneBase::init();
		_select_color=0;
		_select_icon=0;	

		_step_record.clear();
		_index_step=0;
		_index_wish=0;
		_timer_text.reset();
	}
	void setColor(int index_){
		_select_color=index_;
	}
	void setIcon(int index_){
		_select_icon=index_;
	}

	void addStep(ofVec2f pos_){
		
		pos_-=_pos_center;
		if(pos_.length()>_rad_out || pos_.length()<_rad_in) return;


		DecoStep step_;
		step_._ang=ofRandom(360);
		step_._color=_select_color;
		step_._icon=_select_icon;
		step_._pos=pos_;
		
		
		if(_index_step<_step_record.size()) _step_record.resize(_index_step);
		
		_step_record.push_back(step_);
		_index_step++;
	}

	void redoStep(){
		if(_index_step<_step_record.size()) _index_step++;
	}
	void undoStep(){
		if(_index_step>0) _index_step--;
	}
	void setWish(wstring set_,int color_){
		_wish=set_;
		_color_wish=color_;
		_index_wish=0;
	}
	void onSceneInFinish(int &e){	
		if(e==_order_scene) _timer_text.restart();
	}
	void update(float dt_){
		SceneBase::update(dt_);
		_timer_text.update(dt_);
		if(_timer_text.val()==1 && _index_wish<_wish.length()){
			_index_wish++;
			_timer_text.restart();			
		}
	}
};


#endif