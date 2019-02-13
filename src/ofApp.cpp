#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//	OF Settings
	ofSetFrameRate(60);

	//	Window
	w = ofGetWidth();
	h = ofGetHeight();

	//	Spout
	spoutSender.init("sinesOfLife");
	displayTex.allocate(w, h, GL_RGBA32F_ARB);

	//	Scenes
	setupScene1();
	setupScene2();
	setupScene3();
	setupScene4();
	setupScene5();
}

void ofApp::setupScene1(){
	//	Dimensions
	float x = (w / 5) - (w / 25);
	float y = 0;
	float width = w / 25;
	float height = h;

	//	Background
	bg1 = Background(x, y, width, height);
	ofColor bgColorTL(0, 0, 0);
	ofColor bgColorTR(253, 114, 83);
	ofColor bgColorBR(255, 145, 82);
	ofColor bgColorBL(0, 0, 0);
	bg1.setColors(bgColorTL, bgColorTR, bgColorBR, bgColorBL);
}

void ofApp::setupScene2(){
	//	Dimensions
	float x = w / 5;
	float y = 0;
	float width = w / 5;
	float height = h;

	//	Background
	bg2 = Background(x, y, width, height);
	ofColor bgColorTL(253, 114, 83);
	ofColor bgColorTR(255, 145, 82);
	ofColor bgColorBR(210, 104, 142);
	ofColor bgColorBL(138, 88, 132);
	bg2.setColors(bgColorTL, bgColorTR, bgColorBR, bgColorBL);

	//	Heat
	heat2 = Heat(x, y, width, height, 16);
	vector<ofFloatColor> colors;
	colors.push_back(ofColor(255, 145, 82));
	heat2.setColors(colors);
	colors.clear();

	//	Bubbles
	bubbles2 = BubbleLayer(x, y, width, height, 32);
	bubbles2.setColor(ofColor(255, 145, 82));

	//	Wind
	wind2a = Wind(x, y, width, height, 32, -0.35, -0.3);
	colors.push_back(ofColor(255, 180, 94));
	colors.push_back(ofColor(255, 145, 82));
	colors.push_back(ofColor(254, 123, 69));
	colors.push_back(ofColor(253, 114, 83));
	wind2a.setColors(colors);
	colors.clear();

	wind2b = Wind(x, y, width, height, 32, 0.8, 0.85);
	colors.push_back(ofColor(38, 25, 40));
	colors.push_back(ofColor(59, 41, 63));
	colors.push_back(ofColor(138, 88, 132));
	colors.push_back(ofColor(186, 107, 134));
	wind2b.setColors(colors);
	colors.clear();

	//	Image
	sunImage.load("images/suns.png");

	//	Panel
	panel2 = Panel(x, y, sunImage.getWidth() + 100, h, 0, 0, 1);

	//	Multidots
	int numRows = 15;
	int numCols = 20;
	mDot2 = MultiDot(x, y, width, height, 40, numCols, numRows);
	colors.push_back(ofColor(38, 25, 40));
	colors.push_back(ofColor(138, 88, 132));
	colors.push_back(ofColor(186, 107, 134));
	colors.push_back(ofColor(243, 132, 156));
	mDot2.setColors(colors);
	colors.clear();
	vector<float> rowChances;
	rowChances.push_back(0.0);	//	1
	rowChances.push_back(0.25);	//	2
	rowChances.push_back(0.5);	//	3
	rowChances.push_back(0.5);	//	4
	rowChances.push_back(0.5);	//	5
	rowChances.push_back(0.5);	//	6
	rowChances.push_back(0.75);	//	7
	rowChances.push_back(0.85);	//	8
	rowChances.push_back(0.95);	//	9
	rowChances.push_back(0.85);	//	10
	rowChances.push_back(0.75);	//	11
	rowChances.push_back(0.5);	//	12
	rowChances.push_back(0.5);	//	13
	rowChances.push_back(0.5);	//	14
	rowChances.push_back(0.0);	//	15
	vector<float> colChances;
	colChances.push_back(0.0);	//	1
	colChances.push_back(0.0);	//	2
	colChances.push_back(0.15);	//	3
	colChances.push_back(0.5);	//	4
	colChances.push_back(0.85);	//	5
	colChances.push_back(0.95);	//	6
	colChances.push_back(0.95);	//	7
	colChances.push_back(0.5);	//	8
	colChances.push_back(0.25);	//	9
	colChances.push_back(0.15);	//	10
	colChances.push_back(0.0);	//	11
	colChances.push_back(0.0);	//	12
	colChances.push_back(0.0);	//	13
	colChances.push_back(0.0);	//	14
	colChances.push_back(0.0);	//	15
	colChances.push_back(0.0);	//	16
	colChances.push_back(0.0);	//	17
	colChances.push_back(0.0);	//	18
	colChances.push_back(0.0);	//	19
	colChances.push_back(0.0);	//	20
	mDot2.setChances(colChances, rowChances);
}

void ofApp::setupScene3(){
	//	Dimensions
	float x = 2 * w / 5;
	float y = 0;
	float width = w / 5;
	float height = h;

	//	Background
	bg3 = Background(x, y, width, height);
	ofColor bgColorTL(18, 41, 50);
	ofColor bgColorTR(179, 97, 98);
	ofColor bgColorBR(0, 191, 248);
	ofColor bgColorBL(255, 255, 255);
	bg3.setColors(bgColorTL, bgColorTR, bgColorBR, bgColorBL);

	//	Heat
	heat3 = Heat(x, y, width, height, 16);
	vector<ofFloatColor> colors;
	colors.push_back(ofColor(207, 90, 110));
	heat3.setColors(colors);
	colors.clear();

	//	Bubbles
	bubbles3 = BubbleLayer(x, y, width, height, 32);
	bubbles3.setColor(ofColor(207, 90, 110));

	//	Panel
	float panelH = h / 4 + 100;
	panel3 = Panel(x, h - panelH, width, panelH, 0, 0, 0);

	//	Wind
	wind3a = Wind(x, y, width, height, 32, 0.65, 0.7);
	colors.push_back(ofColor(137, 59, 76));
	colors.push_back(ofColor(207, 90, 110));
	colors.push_back(ofColor(87, 56, 73));
	colors.push_back(ofColor(255, 255, 255));
	wind3a.setColors(colors);
	colors.clear();

	//	Origami;
	origami3 = Origami(x, y, width, height);
}

void ofApp::setupScene4(){
	//	Dimensions
	float x = 3 * w / 5;
	float y = 0;
	float width = w / 5;
	float height = h;

	//	Background
	bg4 = Background(x, y, width, height);
	ofColor bgColorTL(4, 81, 107);
	ofColor bgColorTR(52, 143, 100);
	ofColor bgColorBR(6, 44, 61);
	ofColor bgColorBL(5, 12, 18);
	bg4.setColors(bgColorTL, bgColorTR, bgColorBR, bgColorBL);
}

void ofApp::setupScene5(){
	//	Dimensions
	float x = 4 * w / 5;
	float y = 0;
	float width = w / 5;
	float height = h;

	//	Background
	bg5 = Background(x, y, width, height);
	ofColor bgColorTL(255, 127, 127);
	ofColor bgColorTR(127, 127, 255);
	ofColor bgColorBR(127, 255, 127);
	ofColor bgColorBL(255, 255, 255);
	bg5.setColors(bgColorTL, bgColorTR, bgColorBR, bgColorBL);
}

//--------------------------------------------------------------
void ofApp::update(){
	//	Window
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
	//	BG
	ofBackground();

	//	Scenes
	drawScene1();
	drawScene2();
	drawScene3();
	drawScene4();
	drawScene5();

	//	Spout
	displayTex.loadScreenData(0, 0, w, h);
	spoutSender.send(displayTex);
}

void ofApp::drawScene1(){
	//	Background
	bg1.draw();
}

void ofApp::drawScene2(){
	//	Background
	bg2.draw();

	//	Heat
	heat2.draw();

	//	Bubbles
	bubbles2.draw();

	//	Wind A
	wind2a.draw();

	//	Panel
	panel2.draw();

	//	Image
	ofPushStyle();
	ofSetColor(255);
	sunImage.draw(w / 5, 0);
	ofPopStyle();

	//	Wind B
	wind2b.draw();

	//	Dots
	mDot2.draw();
}

void ofApp::drawScene3(){
	//	Background
	bg3.draw();

	//	Heat
	heat3.draw();

	//	Bubbles
	bubbles3.draw();

	//	Panel
	panel3.draw();

	//	Wind A
	wind3a.draw();

	//	Origami
	//origami3.draw();
}

void ofApp::drawScene4(){
	//	Background
	bg4.draw();
}

void ofApp::drawScene5(){
	//	Background
	bg5.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'h':
		heat2.reset();
		heat3.reset();
		break;
	case 'r':
		reloadShaders();
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::reloadShaders() {
	//	SCENE 1
	bg1.reloadShader();
	//	SCENE 2
	bg2.reloadShader();
	heat2.reloadShader();
	bubbles2.reloadShader();
	wind2a.reloadShader();
	wind2b.reloadShader();
	panel2.reloadShader();
	mDot2.reloadShader();
	//	SCENE 3
	bg3.reloadShader();
	heat3.reloadShader();
	bubbles3.reloadShader();
	wind3a.reloadShader();
	panel3.reloadShader();
	origami3.reloadShader();
	//	SCENE 4
	bg4.reloadShader();
	//	SCENE 5
	bg5.reloadShader();
}