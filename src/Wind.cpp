#include "Wind.h"

Wind::Wind() :
	x(0),
	y(0),
	w(100),
	h(100),
	n(1),
	offsetMin(-0.5),
	offsetMax(0.5) {
	setup();
}

Wind::Wind(float xpos, float ypos, float width, float height, float numLines, float minOffset, float maxOffset) :
	x(xpos),
	y(ypos),
	w(width),
	h(height),
	n(numLines),
	offsetMin(minOffset),
	offsetMax(maxOffset) {
	setup();
}

void Wind::setup() {
	//	Allocate fbo
	fbo.allocate(w, h, GL_RGBA32F_ARB);

	//	Load shader
	shader.load("shaders/wind");

	//	Default color
	colors.clear();
	colors.push_back(ofFloatColor(1, 1, 1, 1));
	writeColorsToTex();

	//	Default gradient
	gradientStart = 0.0;
	gradientEnd = 0.0;

	//	Offsets
	offsets.clear();
	for (int i = 0; i < n; ++i) {
		offsets.push_back(ofRandom(offsetMin, offsetMax));
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
		noiseFactors1.push_back(ofRandom(0.05, 0.2));
	}
	//
	noiseFactors2.clear();
	for (int i = 0; i < n; ++i) {
		noiseFactors2.push_back(ofRandom(0.5, 20.0));
	}
	//
	noiseFactors3.clear();
	for (int i = 0; i < n; ++i) {
		noiseFactors3.push_back(ofRandom(0.05, 0.4));
	}
	//
	noiseFactors4.clear();
	for (int i = 0; i < n; ++i) {
		noiseFactors4.push_back(ofRandom(0.0, 20.0));
	}
	writeNoiseToTex();
}

void Wind::setColors(vector<ofFloatColor> colors) {
	this->colors = colors;
	writeColorsToTex();
}

void Wind::setGradient(float start, float end){
	gradientStart = start;
	gradientEnd = end;
}

void Wind::writeColorsToTex(){
	float *colorData = new float[n * 4];
	for (int i = 0; i < n; ++i) {
		ofFloatColor color = colors.at(ofRandom(colors.size()));
		colorData[i * 4 + 0] = color.r;
		colorData[i * 4 + 1] = color.g;
		colorData[i * 4 + 2] = color.b;
		colorData[i * 4 + 3] = ofRandom(0.99, 1.0);
	}
	colorTex.clear();
	colorTex.allocate(n, 1, GL_RGBA);
	colorTex.loadData(colorData, n, 1, GL_RGBA);
	delete[] colorData;
}

void Wind::writeOffsetsToTex(){
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
	delete offsetData;
}

void Wind::writeTimeFactorsToTex(){
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

void Wind::writeNoiseToTex(){
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

void Wind::draw() {
	//	Draw to fbo
	fbo.begin();
	ofClear(0, 0, 0, 0);

	//	Shader
	shader.begin();
	shader.setUniform2f("res", w, h);
	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform1i("N", n);
	shader.setUniform1f("gradientStart", gradientStart);
	shader.setUniform1f("gradientEnd", gradientEnd);
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

void Wind::reloadShader()
{
	shader.unload();
	shader.load("shaders/wind");
}