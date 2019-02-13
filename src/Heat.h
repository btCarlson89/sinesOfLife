#pragma once

#include "ofMain.h"

class Heat {
public:
	Heat();
	Heat(float xpos, float ypos, float width, float height, float numLines);

	void setup();
	void setColors(vector<ofFloatColor> colors);
	
	void writeColorsToTex();
	void writeOffsetsToTex();
	void writeTimeFactorsToTex();
	void writeNoiseToTex();
	
	void draw();

	void reloadShader();
	void reset();

private:
	//	Settings
	int n;
	float x, y;
	float w, h;

	//	Noise settings
	vector<float> noiseFactors1;
	vector<float> noiseFactors2;
	vector<float> noiseFactors3;
	vector<float> noiseFactors4;
	ofTexture noiseTex;

	//	Timing
	float t;

	//	Color
	vector<ofFloatColor> colors;
	ofTexture colorTex;

	//	Offsets
	vector<float> offsets;
	ofTexture offsetTex;

	//	Timing
	vector<float> timeFactors;
	ofTexture timeTex;

	//	Fbo
	ofFbo fbo;

	//	Shader
	ofShader shader;
};