#pragma once

#include "ofMain.h"

class OctLayer {
public:

	OctLayer();
	OctLayer(float xpos, float ypos, float width, float height, float radius, int colCount, int rowCount);

	void setup();
	void setColors(vector<ofFloatColor> colors);
	void setChances(vector<float> colChances, vector<float> rowChances);
	void setPositions();
	void writePositionsToTex();
	void draw();

	void reloadShader();

private:

	//	Settings
	float x, y;
	float w, h;
	int n;
	float r;

	//	Grid parameters
	int numCols, numRows;
	float gridW, gridH;
	vector<float> colChance, rowChance;

	//	Colors
	vector<ofFloatColor> colors;

	//	Positions
	vector<ofPoint> positions;
	vector<float> radii;
	ofTexture posTex;

	//	Fbo
	ofFbo fbo;

	//	Shader
	ofShader shader;
};
