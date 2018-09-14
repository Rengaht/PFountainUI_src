#pragma once

#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "ofMain.h"
#include "FrameTimer.h"

class ofApp;

class SceneBase{

public:
	static float WinScale;
	enum SceneStatus {Init, Due, End};
	SceneStatus _status;

	ofApp* _ptr_app;
	int _order_scene;

	SceneBase(ofApp *set_ptr);
	virtual ~SceneBase();

	virtual void loadImage(){}
	void drawScaled(bool debug_=false);
	virtual void draw(bool debug_);
	virtual void init();
	virtual void end();
	virtual void update(float dt_);
	virtual void reset();

	void handleMousePressed(float mouse_x,float mouse_y);
	virtual void buttonEvent(int index){}

	vector<ofRectangle> _button;
	FrameTimer _timer_in[4];
	FrameTimer _timer_out[4];
	ofImage _img_ui[4];

	bool _trigger_in;
	bool _trigger_out;

	static ofEvent<int> sceneInFinish;
	static ofEvent<int> sceneOutFinish;
};


#endif