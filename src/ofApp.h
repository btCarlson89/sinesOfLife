#pragma once

#include "ofMain.h"

//	Addons
#include "ofxSpout.h"

//	Project
#include "Background.h"
#include "BubbleLayer.h"
#include "Heat.h"
#include "MultiDot.h"
#include "Origami.h"
#include "Panel.h"
#include "Wind.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void setupScene1();
	void setupScene2();
	void setupScene3();
	void setupScene4();
	void setupScene5();

	void update();

	void draw();
	void drawScene1();
	void drawScene2();
	void drawScene3();
	void drawScene4();
	void drawScene5();
	

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

	void reloadShaders();

	//	Window
	float w, h;

	//	Spout
	ofxSpout::Sender spoutSender;
	ofTexture displayTex;

	//------------------------------------------------
	//	SCENE 1
	//------------------------------------------------
	Background bg1;

	//------------------------------------------------
	//	SCENE 2
	//------------------------------------------------
	//	Background
	Background bg2;

	//	Heat
	Heat heat2;

	//	Bubble layer
	BubbleLayer bubbles2;

	//	Wind
	Wind wind2a;
	Wind wind2b;

	//	Panel
	Panel panel2;

	//	Image
	ofImage sunImage;

	//	Multidot
	MultiDot mDot2;

	//------------------------------------------------
	//	SCENE 3
	//------------------------------------------------
	//	Background
	Background bg3;

	//	Heat
	Heat heat3;

	//	Bubble layer
	BubbleLayer bubbles3;

	//	Wind
	Wind wind3a;

	//	Panel
	Panel panel3;

	//	Origami
	Origami origami3;

	//------------------------------------------------
	//	SCENE 4
	//------------------------------------------------
	//	Background
	Background bg4;

	//------------------------------------------------
	//	SCENE 5
	//------------------------------------------------
	//	Background
	Background bg5;
};
