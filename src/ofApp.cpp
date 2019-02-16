#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//	OF Settings
	ofSetFrameRate(60);
	ofSetWindowPosition(20, 20);
	ofSetWindowShape(3600, 950);

	//	Window
	w = ofGetWidth();
	h = ofGetHeight();

	//	Spout
	spoutSender.init("sinesOfLife");
	displayTex.allocate(w, h, GL_RGBA32F_ARB);

	//	Load settings
	ofXml xml;
	bool success = xml.load("settings.xml");
	auto settings = xml.getChild("Settings");
	w1 = settings.getChild("W1").getFloatValue();
	w2 = settings.getChild("W2").getFloatValue();
	w3 = settings.getChild("W3").getFloatValue();
	w4 = settings.getChild("W4").getFloatValue();
	w5 = settings.getChild("W5").getFloatValue();

	//	GUI Listeners
	w1TF.addListener(this, &ofApp::w1Update);
	w2TF.addListener(this, &ofApp::w2Update);
	w3TF.addListener(this, &ofApp::w3Update);
	w4TF.addListener(this, &ofApp::w4Update);
	w5TF.addListener(this, &ofApp::w5Update);

	//	GUI setup
	guiPanel.setup("Settings");
	guiPanel.add(w1TF.setup("W1", ofToString(w1), "10", "1000", 200, 20));
	guiPanel.add(w2TF.setup("W2", ofToString(w2), "10", "1000", 200, 20));
	guiPanel.add(w3TF.setup("W3", ofToString(w3), "10", "1000", 200, 20));
	guiPanel.add(w4TF.setup("W4", ofToString(w4), "10", "1000", 200, 20));
	guiPanel.add(w5TF.setup("W5", ofToString(w5), "10", "1000", 200, 20));
	guiPanel.loadFromFile("settings.xml");

	//	Scenes
	setupScene1();
	setupScene2();
	setupScene3();
	setupScene4();
	setupScene5();
}

//--------------------------------------------------------------
void ofApp::setupScene1(){
	//	Dimensions
	float x = 0;
	float y = 0;
	float width = w1;
	float height = h;

	//	Background
	bg1 = Background(x, y, width, height);
	ofColor bgColorTL(0, 0, 0);
	ofColor bgColorTR(253, 114, 83);
	ofColor bgColorBR(138, 88, 132);
	ofColor bgColorBL(0, 0, 0);
	bg1.setColors(bgColorTL, bgColorTR, bgColorBR, bgColorBL);
	bg1.setGradient(0.9, 1.0);
}

//--------------------------------------------------------------
void ofApp::setupScene2(){
	//	Dimensions
	float x = w1;
	float y = 0;
	float width = w2;
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

//--------------------------------------------------------------
void ofApp::setupScene3(){
	//	Dimensions
	float x = w1 + w2;
	float y = 0;
	float width = w3;
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
	float panelH = h / 3 + 100;
	panel3 = Panel(x, h - panelH, width, panelH, 0, 0, 0);

	//	Wind
	wind3a = Wind(x, y, width, height, 32, 0.6, 0.65);
	colors.push_back(ofColor(137, 59, 76));
	colors.push_back(ofColor(207, 90, 110));
	colors.push_back(ofColor(87, 56, 73));
	colors.push_back(ofColor(255, 255, 255));
	wind3a.setColors(colors);
	colors.clear();

	//	Origami;
	origamiImage.load("images/origami.png");

	//	Blood
	float bW = 265.0;
	float bH = h * 0.8;
	blood3 = Blood(x + w3 - bW, y + 275, bW, bH, 32, 0.0, 0.005);
	colors.push_back(ofColor(137, 59, 76));
	colors.push_back(ofColor(207, 90, 110));
	colors.push_back(ofColor(207, 90, 110));
	colors.push_back(ofColor(207, 90, 110));
	colors.push_back(ofColor(87, 56, 73));
	colors.push_back(ofColor(255, 255, 255));
	blood3.setColors(colors);
	colors.clear();

	//	Skull Image
	skullImage.load("images/skulls.png");

	//	Hex layer
	int numRows = 15;
	int numCols = 20;
	hex3 = OctLayer(x, y, width, height, 40, numCols, numRows);
	colors.push_back(ofColor(8, 13, 15));
	colors.push_back(ofColor(32, 43, 47));
	colors.push_back(ofColor(48, 59, 63));
	colors.push_back(ofColor(146, 77, 55));
	hex3.setColors(colors);
	colors.clear();
	vector<float> rowChances;
	rowChances.push_back(0.0);	//	1
	rowChances.push_back(0.0);	//	2
	rowChances.push_back(0.0);	//	3
	rowChances.push_back(0.0);	//	4
	rowChances.push_back(0.0);	//	5
	rowChances.push_back(0.0);	//	6
	rowChances.push_back(0.0);	//	7
	rowChances.push_back(0.0);	//	8
	rowChances.push_back(0.5);	//	9
	rowChances.push_back(0.75);	//	10
	rowChances.push_back(0.95);	//	11
	rowChances.push_back(0.75);	//	12
	rowChances.push_back(0.5);	//	13
	rowChances.push_back(0.15);	//	14
	rowChances.push_back(0.0);	//	15
	vector<float> colChances;
	colChances.push_back(0.15);	//	1
	colChances.push_back(0.15);	//	2
	colChances.push_back(0.25);	//	3
	colChances.push_back(0.5);	//	4
	colChances.push_back(0.65);	//	5
	colChances.push_back(0.95);	//	6
	colChances.push_back(0.85);	//	7
	colChances.push_back(0.65);	//	8
	colChances.push_back(0.5);	//	9
	colChances.push_back(0.45);	//	10
	colChances.push_back(0.5);	//	11
	colChances.push_back(0.65);	//	12
	colChances.push_back(0.85);	//	13
	colChances.push_back(0.95);	//	14
	colChances.push_back(0.65);	//	15
	colChances.push_back(0.5);	//	16
	colChances.push_back(0.25);	//	17
	colChances.push_back(0.15);	//	18
	colChances.push_back(0.15);	//	19
	colChances.push_back(0.15);	//	20
	hex3.setChances(colChances, rowChances);
}

//--------------------------------------------------------------
void ofApp::setupScene4(){
	//	Dimensions
	float x = w1 + w2+ w3;
	float y = 0;
	float width = w4;
	float height = h;

	//	Background
	bg4 = Background(x, y, width, height);
	ofColor bgColorTL(103, 145, 144);
	ofColor bgColorTR(53, 53, 63);
	ofColor bgColorBR(203, 199, 200);
	ofColor bgColorBL(152, 192, 192);
	bg4.setColors(bgColorTL, bgColorTR, bgColorBR, bgColorBL);
}

//--------------------------------------------------------------
void ofApp::setupScene5(){
	//	Dimensions
	float x = w1 + w2 + w3 + w4;
	float y = 0;
	float width = w5;
	float height = h;

	//	Background
	bg5 = Background(x, y, width, height);
	ofColor bgColorTL(53, 53, 63);
	ofColor bgColorTR(0, 0, 0);
	ofColor bgColorBR(0, 0, 0);
	ofColor bgColorBL(203, 199, 200);
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
	ofBackground(0);

	//	Scenes
	drawScene1();
	drawScene2();
	drawScene3();
	drawScene4();
	drawScene5();

	//	Spout
	displayTex.loadScreenData(0, 0, w, h);
	spoutSender.send(displayTex);

	//	GUI
	if (showGUI) guiPanel.draw();
}

//--------------------------------------------------------------
void ofApp::drawScene1(){
	//	Background
	bg1.draw();
}

//--------------------------------------------------------------
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
	sunImage.draw(w1, 0);
	ofPopStyle();

	//	Wind B
	wind2b.draw();

	//	Dots
	mDot2.draw();
}

//--------------------------------------------------------------
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
	//	Skull Image
	ofPushStyle();
	ofSetColor(255);
	origamiImage.draw(w1 + w2, h * 0.45);
	ofPopStyle();

	//	Blood
	blood3.draw();
	
	//	Skull Image
	ofPushStyle();
	ofSetColor(255);
	skullImage.draw(w1 + w2 + w3 - skullImage.getWidth(), h - skullImage.getHeight() - 50);
	ofPopStyle();

	//	Hex layer
	hex3.draw();
}

//--------------------------------------------------------------
void ofApp::drawScene4(){
	//	Background
	bg4.draw();
}

//--------------------------------------------------------------
void ofApp::drawScene5(){
	//	Background
	bg5.draw();
}

//--------------------------------------------------------------
void ofApp::reset(){
	//	Scenes
	setupScene1();
	setupScene2();
	setupScene3();
	setupScene4();
	setupScene5();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'g':
		showGUI = !showGUI;
		break;
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
	blood3.reloadShader();
	hex3.reloadShader();
	//	SCENE 4
	bg4.reloadShader();
	//	SCENE 5
	bg5.reloadShader();
}

//--------------------------------------------------------------
void ofApp::w1Update(string& w1){
	this->w1 = ofToFloat(w1);
	reset();
}

void ofApp::w2Update(string& w2){
	this->w2 = ofToFloat(w2);
	reset();
}

void ofApp::w3Update(string& w3){
	this->w3 = ofToFloat(w3);
	reset();
}

void ofApp::w4Update(string& w4){
	this->w4 = ofToFloat(w4);
	reset();
}

void ofApp::w5Update(string& w5){
	this->w5 = ofToFloat(w5);
	reset();
}