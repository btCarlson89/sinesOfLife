#include "Heat.h"

Heat::Heat() :
	x(0),
	y(0),
	w(100),
	h(100),
	n(1) {
	setup();
}

Heat::Heat(float xpos, float ypos, float width, float height, float numLines) :
	x(xpos),
	y(ypos),
	w(width),
	h(height),
	n(numLines) {
	setup();
}

void Heat::setup(){
	//	Allocate fbo
	fbo.allocate(w, h, GL_RGBA32F_ARB);

	//	Load shader
	shader.unload();
	shader.load("shaders/heat");

	//	Default color
	colors.clear();
	colors.push_back( ofFloatColor(1, 1, 1, 1) );
	writeColorsToTex();

	//	Offsets
	offsets.clear();
	for (int i = 0; i < n; ++i) {
		offsets.push_back(ofRandom(0.0, 1.0));
	}
	writeOffsetsToTex();

	//	Time factors
	timeFactors.clear();
	for (int i = 0; i < n; ++i) {
		timeFactors.push_back(ofRandom(0.25, 0.5));
	}
	writeTimeFactorsToTex();

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
	writeNoiseToTex();
}

void Heat::setColors(vector<ofFloatColor> colors){
	this->colors = colors;
	writeColorsToTex();
}

void Heat::writeColorsToTex(){
	float *colorData = new float[n * 4];
	for (int i = 0; i < n; ++i) {
		ofFloatColor color = colors.at(ofRandom(colors.size()));
		colorData[i * 4 + 0] = color.r;
		colorData[i * 4 + 1] = color.g;
		colorData[i * 4 + 2] = color.b;
		colorData[i * 4 + 3] = ofRandom(0.9, 0.95);
	}
	colorTex.clear();
	colorTex.allocate(n, 1, GL_RGBA);
	colorTex.loadData(colorData, n, 1, GL_RGBA);
	delete[] colorData;
}

void Heat::writeOffsetsToTex(){
	float *offsetData = new float[n * 4];
	for (int i = 0; i < n; ++i) {
		float offset = offsets.at(i);
		offsetData[i * 4 + 0] = offset;
		offsetData[i * 4 + 1] = 0;
		offsetData[i * 4 + 2] = 0;
		offsetData[i * 4 + 3] = 0;
	}
	offsetTex.clear();
	offsetTex.allocate(n, 1, GL_RGBA);
	offsetTex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	offsetTex.loadData(offsetData, n, 1, GL_RGBA);
	delete[] offsetData;
}

void Heat::writeTimeFactorsToTex(){
	float *timeData = new float[n * 4];
	for (int i = 0; i < n; ++i) {
		float timeFactor = timeFactors.at(i);
		timeData[i * 4 + 0] = timeFactor;
		timeData[i * 4 + 1] = 0;
		timeData[i * 4 + 2] = 0;
		timeData[i * 4 + 3] = 0;
	}
	timeTex.clear();
	timeTex.allocate(n, 1, GL_RGBA);
	timeTex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	timeTex.loadData(timeData, n, 1, GL_RGBA);

	delete[] timeData;
}

void Heat::writeNoiseToTex(){
	float *noiseData = new float[n * 4];
	for (int i = 0; i < n; ++i) {
		float nf1 = noiseFactors1.at(i);
		float nf2 = noiseFactors2.at(i);
		float nf3 = noiseFactors3.at(i);
		float nf4 = noiseFactors4.at(i);
		noiseData[i * 4 + 0] = nf1;
		noiseData[i * 4 + 1] = nf2;
		noiseData[i * 4 + 2] = nf3;
		noiseData[i * 4 + 3] = nf4;
	}
	noiseTex.clear();
	noiseTex.allocate(n, 1, GL_RGBA);
	noiseTex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	noiseTex.loadData(noiseData, n, 1, GL_RGBA);

	delete[] noiseData;
}

void Heat::draw(){
	//	Draw to fbo
	fbo.begin();
	ofClear(0, 0, 0, 0);

	//	Shader
	shader.begin();
	shader.setUniform2f("res", w, h);
	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform1i("N", n);
	shader.setUniformTexture("colors", colorTex, 0);
	shader.setUniformTexture("offsets", offsetTex, 1);
	shader.setUniformTexture("timeFactors", timeTex, 2);
	shader.setUniformTexture("noiseFactors", noiseTex, 3);
	ofDrawRectangle(0, 0, w, h);
	shader.end();

	fbo.end();

	//	Draw
	fbo.draw(x, y);
}

void Heat::reloadShader()
{
	shader.unload();
	shader.load("shaders/heat");
}

void Heat::reset(){
	//	Offsets
	offsets.clear();
	for (int i = 0; i < n; ++i) {
		offsets.push_back(ofRandom(0.0, 1.0));
	}
	writeOffsetsToTex();
}
