#pragma once

#include "ofMain.h"

class Background {
public:

	Background();
	Background(float xpos, float ypos, float width, float height);

	void setup();
	void setColors(ofFloatColor tl, ofFloatColor tr, ofFloatColor br, ofFloatColor bl);
	void setGradient(float start, float stop);
	void draw();

	void reloadShader();

private:

	//	Pos
	float x, y;

	//	Size
	float w, h;

	//	Colors
	ofFloatColor colorTL;
	ofFloatColor colorTR;
	ofFloatColor colorBR;
	ofFloatColor colorBL;

	//	Alpha gradient
	float gradientStart = 0;
	float gradientEnd = 0;

	//	Fbo
	ofFbo fbo;

	//	Shader
	ofShader shader;
};