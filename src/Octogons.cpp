#include "Octogons.h"

OctLayer::OctLayer() :
	x(0),
	y(0),
	w(100),
	h(100),
	r(100),
	numRows(3),
	numCols(3) {
	setup();
}

OctLayer::OctLayer(float xpos, float ypos, float width, float height, float radius, int colCount, int rowCount) :
	x(xpos),
	y(ypos),
	w(width),
	h(height),
	r(radius),
	numCols(colCount),
	numRows(rowCount) {
	setup();
}

void OctLayer::setup() {
	//	Allocate fbo
	fbo.allocate(w, h, GL_RGBA32F_ARB);
	//	Default colors
	colors.clear();
	colors.push_back(ofFloatColor(1, 1, 1, 1));
	//	Setup rows and columns
	gridW = w / numCols;
	gridH = h / numRows;
	//	Default row chance
	rowChance.clear();
	for (int i = 0; i < numRows; ++i) {
		//	Basically, closer to center better the odds
		float chance = 1.0 - (abs(0.5 * numRows - i) / (0.5 * numRows));
		rowChance.push_back(chance);
	}
	//	Default col chance
	colChance.clear();
	for (int i = 0; i < numCols; ++i) {
		//	Basically, closer to center better the odds
		float chance = 1.0 - (abs(0.5 * numCols - i) / (0.5 * numCols));
		colChance.push_back(chance);
	}
	//	Positions
	setPositions();
	//	Load shader
	shader.load("shaders/octogon");
}

void OctLayer::setColors(vector<ofFloatColor> colors) {
	this->colors = colors;
}

void OctLayer::setChances(vector<float> colChances, vector<float> rowChances) {
	colChance = colChances;
	rowChance = rowChances;
	//	Set remaining chances to zero if the vectors aren't long enough
	if (rowChance.size() < numRows) {
		for (int i = rowChance.size(); i < numRows; ++i) {
			rowChance.push_back(0);
		}
	}
	if (colChance.size() < numCols) {
		for (int i = colChance.size(); i < numCols; ++i) {
			colChance.push_back(0);
		}
	}
	//	Reset positions
	setPositions();
}

void OctLayer::setPositions() {
	positions.clear();
	radii.clear();
	for (int i = 0; i < numCols; ++i) {
		for (int j = 0; j < numRows; ++j) {
			float chance = colChance.at(i) * rowChance.at(j);
			float radius = r;
			if (ofRandom(1) < chance) {
				radius = ((radius * chance) + (radius * chance) + radius) / 3.0;
				float xOffset = gridW * i;
				float yOffset = gridH * j;
				if (i % 2 != 0) yOffset -= r;
				positions.push_back(ofPoint(xOffset, yOffset, 0));
				radii.push_back(radius);
			}
		}
	}
	writePositionsToTex();
}

void OctLayer::writePositionsToTex() {
	float *posData = new float[positions.size() * 4];
	for (int i = 0; i < positions.size(); ++i) {
		float xpos = positions.at(i).x;
		float ypos = positions.at(i).y;
		float radius = radii.at(i);
		posData[i * 4 + 0] = xpos / w;
		posData[i * 4 + 1] = ypos / h;
		posData[i * 4 + 2] = radius / w;
		posData[i * 4 + 3] = 0;
	}
	posTex.clear();
	posTex.allocate(positions.size(), 1, GL_RGBA);
	posTex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	posTex.loadData(posData, positions.size(), 1, GL_RGBA);
	delete[] posData;
}

void OctLayer::updateRMS(float rms){
	this->rms = rms;
}

void OctLayer::draw() {
	//	Draw to fbo
	fbo.begin();
	ofClear(0, 0, 0, 0);
	//	Shader
	shader.begin();
	shader.setUniform1i("numDots", positions.size());
	shader.setUniform1f("time", ofGetElapsedTimef() * 0.5);
	shader.setUniform1f("rms", 0.0);
	shader.setUniform2f("res", w, h);
	shader.setUniform4f("color1", colors.at(0));
	shader.setUniform4f("color2", colors.at(1 % colors.size()));
	shader.setUniform4f("color3", colors.at(2 % colors.size()));
	shader.setUniform4f("color4", colors.at(3 % colors.size()));
	shader.setUniformTexture("posTex", posTex, 0);
	ofDrawRectangle(0, 0, w, h);
	shader.end();
	fbo.end();
	//	Draw
	fbo.draw(x, y);
}

void OctLayer::reloadShader() {
	//	Load shader
	shader.unload();
	shader.load("shaders/octogon");
}
