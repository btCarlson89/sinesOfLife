#pragma once

#include "ofMain.h"

class Panel {
public:

	Panel();
	Panel(float xpos, float ypos, float width, float height, float xOff, float yOff, int direction);

	void setup();
	void setColor(ofFloatColor color);
	void setGradient(float start, float end);

	void draw();

	void reloadShader();

private:
	//	Geometry
	float x, y;
	float w, h;
	float xOffset, yOffset;
	float pad;

	//	0 = top, 1 = right, 2 = bottom, 3 = left
	int shadowDirection;

	//	Color
	ofFloatColor color;

	//	Alpha Gradient
	float gradientStart;
	float gradientEnd;

	//	Fbo
	ofFbo fbo;

	//	Shader
	ofShader shader;
};