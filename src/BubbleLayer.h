#pragma once

#include "ofMain.h"

class BubbleLayer
{
public:
	BubbleLayer();
	BubbleLayer(float xpos, float ypos, float width, float height, float numBubbles);

	void setup();
	void setColor(ofFloatColor color);
	void setGradient(float start, float end);

	void draw();

	void reloadShader();

private:
	//	Settings
	int n;
	float x, y;
	float w, h;

	//	Timing
	float t;

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

