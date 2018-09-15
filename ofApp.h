#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "SceneBase.h"


//#define DRAW_DEBUG

class ofApp : public ofBaseApp{

	public:
		static float WinScaleX,WinScaleY;
		static ofColor MainColor[5];
		

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		

		enum SceneMode {SLEEP,WISH,DECO,SHOW,QRCODE};

		float _last_millis;
		float _dmillis;

		SceneMode _mode,_mode_pre;
		bool _in_transition;

		SceneBase* _scene[5];
		void loadScene();
		void setScene(SceneMode set_);

		void onSceneInFinish(int &e);
		void onSceneOutFinish(int &e);
		
		ofxTrueTypeFontUC _font_wish;
		string ws2s(const wstring& wstr);

		wstring _user_wish;
		int _user_color_wish;
		
};
