#pragma once

#include "ofMain.h"

class Aurora {
public:
	Aurora();
	Aurora(float xpos, float ypos, float width, float height, float numAreas);

	void setup();
	void setColors(vector<ofFloatColor> colors);
	void setGradient(float start, float end);

	void setScreenTex0(ofTexture tex);
	void setScreenTex1(ofTexture tex);
	
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

	//	Alpha Gradient
	float gradientStart;
	float gradientEnd;

	//	Offsets
	vector<float> offsets;
	ofTexture offsetTex;

	//	Screen textures
	ofTexture screenTex0;
	ofTexture screenTex1;

	//	Timing
	vector<float> timeFactors;
	ofTexture timeTex;

	//	Fbo
	vector<ofFbo> fbos;
	vector<ofPoint> positions;

	//	Shader
	ofShader shader;
};