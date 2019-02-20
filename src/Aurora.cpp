#include "Aurora.h"

Aurora::Aurora() :
	x(0),
	y(0),
	w(100),
	h(100),
	n(1) {
	setup();
}

Aurora::Aurora(float xpos, float ypos, float width, float height, float numAreas) :
	x(xpos),
	y(ypos),
	w(width),
	h(height),
	n(numAreas) {
	setup();
}

void Aurora::setup(){
	//	Allocate fbos & randomize postions
	fbos.clear();
	positions.clear();
	for (int i = 0; i < n; ++i) {
		float width = ofRandom(0.1 * w, 0.5 * w);
		float height = width;
		ofFbo fbo;
		fbo.allocate(width, height, GL_RGBA32F_ARB);
		fbos.push_back(fbo);
		float xpos = ofRandom(0, w - width);
		float ypos = ofRandom(0, h - height);
		positions.push_back(ofPoint(xpos, ypos));
	}

	//	Load shader
	shader.unload();
	shader.load("shaders/aurora");

	//	Default color
	colors.clear();
	colors.push_back( ofFloatColor(1, 1, 1, 1) );
	
	// Default gradient
	gradientStart = 0;
	gradientEnd = 0;

	//	Offsets
	offsets.clear();
	for (int i = 0; i < n; ++i) {
		offsets.push_back(ofRandom(0.0, 1.0));
	}

	//	Time factors
	timeFactors.clear();
	for (int i = 0; i < n; ++i) {
		timeFactors.push_back(ofRandom(0.25, 0.5));
	}

	//	Noise factors
	noiseFactors1.clear();
	for (int i = 0; i < n; ++i) {
		noiseFactors1.push_back(ofRandom(0.25, 0.5));
	}
	//
	noiseFactors2.clear();
	for (int i = 0; i < n; ++i) {
		noiseFactors2.push_back(ofRandom(0.0, TWO_PI));
	}
	//
	noiseFactors3.clear();
	for (int i = 0; i < n; ++i) {
		noiseFactors3.push_back(ofRandom(0.25, 0.5));
	}
	//
	noiseFactors4.clear();
	for (int i = 0; i < n; ++i) {
		noiseFactors4.push_back(ofRandom(0.0, TWO_PI));
	}
}

void Aurora::setColors(vector<ofFloatColor> colors){
	this->colors = colors;
}

void Aurora::setGradient(float start, float end){
	gradientStart = start;
	gradientEnd = end;
}

void Aurora::setScreenTex0(ofTexture tex){
	screenTex0 = tex;
}

void Aurora::setScreenTex1(ofTexture tex){
	screenTex1 = tex;
}

void Aurora::draw(){
	int idx = 0;
	float time = ofGetElapsedTimef();
	for (auto fbo : fbos) {
		//	Position update
		ofVec2f pos = positions.at(idx);
		float angle = ofNoise(pos.x + time * 0.05, pos.y + time * 0.01) * TWO_PI;
		ofVec2f dir = ofVec2f(cos(angle), sin(angle));
		pos += 100.0 * dir;

		//	Draw to fbo
		fbo.begin();
		ofClear(0, 0, 0, 0);

		//	Shader
		shader.begin();
		shader.setUniform2f("res", fbo.getWidth(), fbo.getHeight());
		shader.setUniform1f("time", time);
		shader.setUniform4f("color1", colors.at(0));
		shader.setUniform4f("color2", colors.at(1 % colors.size()));
		shader.setUniform1f("gradientStart", gradientStart);
		shader.setUniform1f("gradientEnd", gradientEnd);
		shader.setUniform2f("pos", pos);
		if(idx % 2 == 0) shader.setUniformTexture("screenTex", screenTex0, 3);
		else shader.setUniformTexture("screenTex", screenTex1, 3);
		ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
		shader.end();

		fbo.end();

		//	Draw
		fbo.draw(x + pos.x, y + pos.y);
		++idx;
	}
}

void Aurora::reloadShader()
{
	shader.unload();
	shader.load("shaders/aurora");
}

void Aurora::reset(){
	//	Allocate fbos & randomize postions
	fbos.clear();
	positions.clear();
	for (int i = 0; i < n; ++i) {
		float width = ofRandom(0.1 * w, 0.5 * w);
		float height = width;
		ofFbo fbo;
		fbo.allocate(width, height, GL_RGBA32F_ARB);
		fbos.push_back(fbo);
		float xpos = ofRandom(0, w - width);
		float ypos = ofRandom(0, h - height);
		positions.push_back(ofPoint(xpos, ypos));
	}
}
