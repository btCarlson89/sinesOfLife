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
	float panelH = h / 4 + 100;
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
	origami3 = Origami(x, y, width, height);
	vector<ofPoint> p0s, p1s, p2s;
	int numClusters = 3;
	for (int i = 0; i < numClusters; ++i) {
		float x0 = ofRandom(1.0);
		float y0 = ofRandom(1.0);
		ofPoint p0 = ofPoint(x0, y0);
		vector<ofPoint> vertices;
		int numTriangles = ofRandom(3, 9);
		float dTheta0 = TWO_PI / float(numTriangles);
		float theta = 0.0;
		for (int j = 0; j < numTriangles; ++j) {
			float dTheta = ofRandom(0.95 * dTheta0, 1.05 * dTheta0);
			theta += dTheta;
			float r = ofRandom(0.1, 0.15);
			float x = r * cos(theta);
			float y = r * sin(theta);
			vertices.push_back(ofPoint(x0 + x, y0 + y));
		}
		for (int j = 0; j < numTriangles; ++j) {
			p0s.push_back(p0);
			p1s.push_back(vertices.at(j));
			p2s.push_back(vertices.at((j + 1) % numTriangles));
		}
	}
	origami3.setVertices(p0s, p1s, p2s);
	colors.push_back(ofColor(8, 13, 15));
	colors.push_back(ofColor(0, 49, 62));
	colors.push_back(ofColor(0, 98, 125));
	colors.push_back(ofColor(0, 195, 249));
	origami3.setColors(colors);
	colors.clear();
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
	ofColor bgColorTL(4, 81, 107);
	ofColor bgColorTR(52, 143, 100);
	ofColor bgColorBR(6, 44, 61);
	ofColor bgColorBL(5, 12, 18);
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
	ofColor bgColorTL(255, 127, 127);
	ofColor bgColorTR(0, 0, 0);
	ofColor bgColorBR(0, 0, 0);
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
	origami3.draw();
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
	origami3.reloadShader();
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