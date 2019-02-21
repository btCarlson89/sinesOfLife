#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//	OF Settings
	ofSetFrameRate(60);
	ofSetWindowPosition(0, 30);
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
	w5 = w - w4 - w3 - w2 - w1;

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

	//	Audio
	setupAudio();

	//	Scenes
	setupScene1();
	setupScene2();
	setupScene3();
	setupScene4();
	setupScene5();
	setupScene6();
}

//--------------------------------------------------------------
void ofApp::setupAudio(){
	//	Load sound file
	ofFileDialogResult result = ofSystemLoadDialog();
	if (result.bSuccess) {
		soundPlayer.load(result.getPath());
	}

	//	Specify audio settings
	ofSoundStreamSettings soundSettings;
	soundSettings.numInputChannels = 0;
	soundSettings.numOutputChannels = 2;
	soundSettings.sampleRate = soundPlayer.getSoundFile().getSampleRate();
	soundSettings.bufferSize = 1024;
	soundSettings.numBuffers = 1;

	//	Setup soundstream
	soundstream.setup(soundSettings);

	//	Connect to audio outputs
	soundPlayer.connectTo(soundOutput);
	soundstream.setOutput(soundOutput);

	//	Play sound
	soundPlayer.play();
	soundPlayer.setLoop(true);

	//	Parameters
	rms = 0.0f;
	smoothRMS = 0.0f;
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
	heat2.setGradient(1.0, 0.9);
	colors.clear();

	//	Bubbles
	bubbles2 = BubbleLayer(x, y, width, height, 32);
	bubbles2.setColor(ofColor(255, 145, 82));
	bubbles2.setGradient(1.0, 0.9);

	//	Wind
	wind2a = Wind(x, y, width + 100, height, 32, -0.35, -0.3);
	colors.push_back(ofColor(255, 180, 94));
	colors.push_back(ofColor(255, 145, 82));
	colors.push_back(ofColor(254, 123, 69));
	colors.push_back(ofColor(253, 114, 83));
	wind2a.setColors(colors);
	wind2a.setGradient(0.0, 0.3);
	colors.clear();

	wind2b = Wind(x - 200, y, width + 450, height, 32, 0.8, 0.85);
	colors.push_back(ofColor(38, 25, 40));
	colors.push_back(ofColor(59, 41, 63));
	colors.push_back(ofColor(138, 88, 132));
	colors.push_back(ofColor(186, 107, 134));
	wind2b.setColors(colors);
	wind2b.setGradient(0.0, 0.3);
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
	ofColor bgColorTL(255, 145, 82);
	ofColor bgColorTR(18, 41, 50);
	ofColor bgColorBR(0, 191, 248);
	ofColor bgColorBL(210, 104, 142);
	bg3.setColors(bgColorTL, bgColorTR, bgColorBR, bgColorBL);
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
	ofColor bgColorTL(18, 41, 50);
	ofColor bgColorTR(179, 97, 98);
	ofColor bgColorBR(0, 191, 248);
	ofColor bgColorBL(0, 191, 248);
	bg4.setColors(bgColorTL, bgColorTR, bgColorBR, bgColorBL);

	//	Heat
	heat4 = Heat(x, y, width, height, 16);
	vector<ofFloatColor> colors;
	colors.push_back(ofColor(207, 90, 110));
	heat4.setColors(colors);
	heat4.setGradient(0.0, 0.1);
	colors.clear();

	//	Bubbles
	bubbles4 = BubbleLayer(x, y, width, height, 32);
	bubbles4.setColor(ofColor(207, 90, 110));
	bubbles4.setGradient(0.0, 0.1);

	//	Panel
	float panelH = h / 3 + 100;
	panel4 = Panel(x, h - panelH, width, panelH, 0, 0, 0);
	panel4.setGradient(0.0, 0.1);

	//	Wind
	wind4a = Wind(x - 50, y, width + 250, height, 32, 0.6, 0.65);
	colors.push_back(ofColor(137, 59, 76));
	colors.push_back(ofColor(207, 90, 110));
	colors.push_back(ofColor(87, 56, 73));
	colors.push_back(ofColor(255, 255, 255));
	wind4a.setColors(colors);
	wind4a.setGradient(0.0, 0.2);
	colors.clear();

	//	Origami;
	origamiImage.load("images/origami.png");

	//	Wind B
	wind4b = Wind(x - 300, y, width + 400, height, 48, 0.15, 0.25);
	colors.push_back(ofColor(16, 27, 31));
	colors.push_back(ofColor(0, 48, 61));
	colors.push_back(ofColor(0, 97, 124));
	colors.push_back(ofColor(0, 97, 124));
	colors.push_back(ofColor(0, 97, 124));
	colors.push_back(ofColor(0, 195, 248));
	wind4b.setColors(colors);
	wind4b.setGradient(0.0, 0.3);
	colors.clear();

	//	Blood
	float bW = 265.0;
	float bH = h * 0.8;
	blood4 = Blood(x + w4 - bW, y + 275, bW, bH, 32, 0.0, 0.005);
	colors.push_back(ofColor(137, 59, 76));
	colors.push_back(ofColor(207, 90, 110));
	colors.push_back(ofColor(207, 90, 110));
	colors.push_back(ofColor(207, 90, 110));
	colors.push_back(ofColor(87, 56, 73));
	colors.push_back(ofColor(255, 255, 255));
	blood4.setColors(colors);
	blood4.setGradient(1.0, 0.8);
	colors.clear();

	//	Skull Image
	skullImage.load("images/skulls.png");

	//	Oct layer A
	int numRows = 15;
	int numCols = 20;
	oct4a = OctLayer(x - 100, y, width + 200, height, 40, numCols, numRows);
	colors.push_back(ofColor(8, 13, 15));
	colors.push_back(ofColor(32, 43, 47));
	colors.push_back(ofColor(48, 59, 63));
	colors.push_back(ofColor(146, 77, 55));
	oct4a.setColors(colors);
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
	rowChances.push_back(0.0);	//	12
	rowChances.push_back(0.0);	//	13
	rowChances.push_back(0.0);	//	14
	rowChances.push_back(0.0);	//	15
	vector<float> colChances;
	colChances.push_back(0.0);	//	1
	colChances.push_back(0.25);	//	2
	colChances.push_back(0.5);	//	3
	colChances.push_back(0.75);	//	4
	colChances.push_back(0.85);	//	5
	colChances.push_back(1.00);	//	6
	colChances.push_back(0.95);	//	7
	colChances.push_back(0.85);	//	8
	colChances.push_back(0.75);	//	9
	colChances.push_back(0.45);	//	10
	colChances.push_back(0.5);	//	11
	colChances.push_back(0.65);	//	12
	colChances.push_back(0.55);	//	13
	colChances.push_back(0.5);	//	14
	colChances.push_back(0.25);	//	15
	colChances.push_back(0.1);	//	16
	colChances.push_back(0.0);	//	17
	colChances.push_back(0.0);	//	18
	colChances.push_back(0.0);	//	19
	colChances.push_back(0.0);	//	20
	oct4a.setChances(colChances, rowChances);

	//	Oct layer B
	numRows = 15;
	numCols = 20;
	oct4b = OctLayer(x - 100, y, width + 200, height, 40, numCols, numRows);
	colors.push_back(ofColor(8, 13, 15));
	colors.push_back(ofColor(32, 43, 47));
	colors.push_back(ofColor(48, 59, 63));
	colors.push_back(ofColor(16, 27, 31));
	oct4b.setColors(colors);
	colors.clear();
	rowChances.clear();
	rowChances.push_back(0.0);	//	1
	rowChances.push_back(0.0);	//	2
	rowChances.push_back(0.0);	//	3
	rowChances.push_back(0.0);	//	4
	rowChances.push_back(0.0);	//	5
	rowChances.push_back(0.0);	//	6
	rowChances.push_back(0.0);	//	7
	rowChances.push_back(0.5);	//	8
	rowChances.push_back(0.75);	//	9
	rowChances.push_back(0.95);	//	10
	rowChances.push_back(0.75);	//	11
	rowChances.push_back(0.75);	//	12
	rowChances.push_back(0.5);	//	13
	rowChances.push_back(0.25);	//	14
	rowChances.push_back(0.15);	//	15
	colChances.clear();
	colChances.push_back(0.0);	//	1
	colChances.push_back(0.25);	//	2
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
	colChances.push_back(0.25);	//	16
	colChances.push_back(0.1);	//	17
	colChances.push_back(0.0);	//	18
	colChances.push_back(0.0);	//	19
	colChances.push_back(0.0);	//	20
	oct4b.setChances(colChances, rowChances);

	//	Oct layer C
	numRows = 15;
	numCols = 20;
	oct4c = OctLayer(x + 50, y, width + 100, height, 40, numCols, numRows);
	colors.push_back(ofColor(161, 141, 110));
	colors.push_back(ofColor(137, 59, 76));
	colors.push_back(ofColor(207, 90, 110));
	colors.push_back(ofColor(87, 56, 73));
	oct4c.setColors(colors);
	colors.clear();
	rowChances.clear();
	rowChances.push_back(0.0);	//	1
	rowChances.push_back(0.15);	//	2
	rowChances.push_back(0.25);	//	3
	rowChances.push_back(0.5);	//	4
	rowChances.push_back(0.75);	//	5
	rowChances.push_back(0.95);	//	6
	rowChances.push_back(0.05);	//	7
	rowChances.push_back(0.0);	//	8
	rowChances.push_back(0.0);	//	9
	rowChances.push_back(0.0);	//	10
	rowChances.push_back(0.0);	//	11
	rowChances.push_back(0.0);	//	12
	rowChances.push_back(0.0);	//	13
	rowChances.push_back(0.0);	//	14
	rowChances.push_back(0.0);	//	15
	colChances.clear();
	colChances.push_back(0);	//	1
	colChances.push_back(0);	//	2
	colChances.push_back(0);	//	3
	colChances.push_back(0);	//	4
	colChances.push_back(0);	//	5
	colChances.push_back(0);	//	6
	colChances.push_back(0);	//	7
	colChances.push_back(0);	//	8
	colChances.push_back(0);	//	9
	colChances.push_back(0.45);	//	10
	colChances.push_back(0.5);	//	11
	colChances.push_back(0.65);	//	12
	colChances.push_back(0.85);	//	13
	colChances.push_back(0.95);	//	14
	colChances.push_back(0.75);	//	15
	colChances.push_back(0.5);	//	16
	colChances.push_back(0.25);	//	17
	colChances.push_back(0.0);	//	18
	colChances.push_back(0.0);	//	19
	colChances.push_back(0.0);	//	20
	oct4c.setChances(colChances, rowChances);
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
	ofColor bgColorTL(179, 97, 98);
	ofColor bgColorTR(0, 0, 0);
	ofColor bgColorBR(0, 0, 0);
	ofColor bgColorBL(0, 191, 248);
	bg5.setColors(bgColorTL, bgColorTR, bgColorBR, bgColorBL);
}

//--------------------------------------------------------------
void ofApp::setupScene6(){
	//	Dimensions
	float x = w1 + w2 - 150;
	float y = 0;
	float width = w3 + 300;
	float height = width;

	//	Aurora
	aurora6 = Aurora(x, y, width, height, 8);
	vector<ofFloatColor> colors;
	colors.push_back(ofColor(253, 114, 83));
	colors.push_back(ofColor(0, 191, 248));
	aurora6.setColors(colors);
	aurora6.setGradient(0.0, 0.1);
	colors.clear();

	//	Screen textures
	tex0.allocate(w2, h, GL_RGBA32F_ARB);
	tex1.allocate(w4, h, GL_RGBA32F_ARB);
}

//--------------------------------------------------------------
void ofApp::update(){
	//	Window
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	//ofSetWindowTitle(ofToString(rms));

	//	Audio
	//vector<float> audioBuffer = soundOutput.getBuffer().getBuffer();
	//processAudio(&audioBuffer[0], 1024, 2);
	rms = max(ofMap(soundOutput.getBuffer().getRMSAmplitude(), 0.0, 0.5, 0.25, 1.0), rms * 0.99f);
	smoothRMS = 0.5 * (rms + smoothRMS);

	//	Scenes
	updateScene2();
	updateScene4();
	updateScene6();
}

//--------------------------------------------------------------
void ofApp::updateScene1(){
}

//--------------------------------------------------------------
void ofApp::updateScene2() {
	//	Wind
	wind2a.updateRMS(smoothRMS);
	wind2b.updateRMS(smoothRMS);
}

//--------------------------------------------------------------
void ofApp::updateScene3() {
}

//--------------------------------------------------------------
void ofApp::updateScene4() {
	//	Wind
	wind4a.updateRMS(smoothRMS);
	wind4b.updateRMS(smoothRMS);
}

//--------------------------------------------------------------
void ofApp::updateScene5() {
}

//--------------------------------------------------------------
void ofApp::updateScene6() {
	//	Aurora
	aurora6.updateRMS(smoothRMS);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//	BG
	ofBackground(0);

	//	Scenes
	drawScene1();
	drawScene3();
	drawScene5();

	drawScene2();
	drawScene4();

	drawScene6();

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
	// Background
	bg3.draw();
}

//--------------------------------------------------------------
void ofApp::drawScene4(){
	//	Background
	bg4.draw();

	//	Heat
	heat4.draw();

	//	Bubbles
	bubbles4.draw();

	//	Panel
	panel4.draw();

	//	Wind A
	wind4a.draw();

	//	Origami
	ofPushStyle();
	ofSetColor(255);
	origamiImage.draw(w1 + w2 + w3 - 50, h * 0.4);
	ofPopStyle();

	//	Oct layer B
	oct4b.draw();

	//	Wind B
	wind4b.draw();

	//	Blood
	blood4.draw();

	//	Skull Image
	ofPushStyle();
	ofSetColor(255);
	skullImage.draw(w1 + w2 + w3 + w4 - skullImage.getWidth(), h - skullImage.getHeight() - 50);
	ofPopStyle();

	//	Oct layer A
	oct4a.draw();

	//	Oct layer C
	oct4c.draw();
}

//--------------------------------------------------------------
void ofApp::drawScene5(){
	//	Background
	bg5.draw();
}

void ofApp::drawScene6(){
	//	Screen textures
	tex0.loadScreenData(w1, 0, w2, h);
	tex1.loadScreenData(w1 + w2 + w3, 0, w4, h);

	//	Aurora
	aurora6.setScreenTex0(tex0);
	aurora6.setScreenTex1(tex1);
	aurora6.draw();
}

//--------------------------------------------------------------
void ofApp::reset(){
	//	Scenes
	setupScene1();
	setupScene2();
	setupScene3();
	setupScene4();
	setupScene5();
	setupScene6();
}

//--------------------------------------------------------------
void ofApp::exit(){
	soundstream.close();
}

//--------------------------------------------------------------
void ofApp::processAudio(float * input, int bufferSize, int nChannels){
	//convert float array to vector
	vector<float>buffer;
	buffer.assign(&input[0], &input[bufferSize]);

	gist.processAudio(buffer, bufferSize, nChannels, 44100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'a':
		aurora6.reset();
		break;
	case 'g':
		showGUI = !showGUI;
		break;
	case 'h':
		heat2.reset();
		heat4.reset();
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
	//	SCENE 4
	bg4.reloadShader();
	heat4.reloadShader();
	bubbles4.reloadShader();
	wind4a.reloadShader();
	panel4.reloadShader();
	wind4b.reloadShader();
	blood4.reloadShader();
	oct4a.reloadShader();
	oct4b.reloadShader();
	//	SCENE 5
	bg5.reloadShader();
	//	SCENE 6
	aurora6.reloadShader();
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