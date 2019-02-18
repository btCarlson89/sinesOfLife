#pragma once

#include "ofMain.h"

class Wind {
public:
	Wind();
	Wind(float xpos, float ypos, float width, float height, float numLines, float minOffset, float maxOffset);

	void setup();
	void setColors(vector<ofFloatColor> colors);
	void setGradient(float start, float end);

	void writeColorsToTex();
	void writeOffsetsToTex();
	void writeTimeFactorsToTex();
	void writeNoiseToTex();

	void draw();

	void reloadShader();

private:
	//	Settings
	int n;
	float x, y;
	float w, h;
	float offsetMin, offsetMax;
	
	//	Noise settings
	vector<float> noiseFactors1;
	vector<float> noiseFactors2;
	vector<float> noiseFactors3;
	vector<float> noiseFactors4;
	ofTexture noiseTex;

	//	Color
	vector<ofFloatColor> colors;
	ofTexture colorTex;

	//	Alpha Gradient
	float gradientStart;
	float gradientEnd;

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