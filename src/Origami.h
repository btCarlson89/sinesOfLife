#pragma once

#include "ofMain.h"

class Origami {
public:

	Origami();
	Origami(float xpos, float ypos, float width, float height);

	void setup();
	void setColors(vector<ofFloatColor> colors);
	void setVertices(vector<ofPoint> v0, vector<ofPoint> v1, vector<ofPoint> v2);

	void writeColorsToTex();
	void writeVerticesToTex();

	void draw();

	void reloadShader();

private:

	//	Settings
	int n;
	float x, y;
	float w, h;

	// Color
	vector<ofFloatColor> colors;
	ofTexture colorTex;

	//	Vertices
	vector<ofPoint> p0s;
	vector<ofPoint> p1s;
	vector<ofPoint> p2s;
	ofTexture p0Tex;
	ofTexture p1Tex;
	ofTexture p2Tex;

	//	Fbo
	ofFbo fbo;

	//	Shader
	ofShader shader;
};
