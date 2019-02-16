#pragma once

#include "ofMain.h"

//	Addons
#include "ofxGui.h"
#include "ofxSpout.h"

//	Project
#include "Background.h"
#include "Blood.h"
#include "BubbleLayer.h"
#include "Heat.h"
#include "MultiDot.h"
#include "Octogons.h"
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

	void reset();
	
	//	Listeners
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
	float w1, w2, w3, w4, w5;

	//	Spout
	ofxSpout::Sender spoutSender;
	ofTexture displayTex;

	//------------------------------------------------
	//	GUI
	//------------------------------------------------
	ofxPanel guiPanel;
	ofxTextField w1TF;
	ofxTextField w2TF;
	ofxTextField w3TF;
	ofxTextField w4TF;
	ofxTextField w5TF;
	bool showGUI = true;

	void w1Update(string& w1);
	void w2Update(string& w2);
	void w3Update(string& w3);
	void w4Update(string& w4);
	void w5Update(string& w5);

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
	ofImage origamiImage;

	//	Wind
	Wind wind3b;
	
	//	Skulls
	ofImage skullImage;

	//	Blood
	Blood blood3;

	//	Oct Layer A
	OctLayer oct3a;

	//	Oct Layer B
	OctLayer oct3b;

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
