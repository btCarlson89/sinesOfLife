#include "Origami.h"

Origami::Origami() :
	x(0),
	y(0),
	w(100),
	h(100),
	n(1){
	setup();
}

Origami::Origami(float xpos, float ypos, float width, float height) :
	x(xpos),
	y(ypos),
	w(width),
	h(height),
	n(1){
	setup();
}

void Origami::setup(){
	//	Allocate fbo
	fbo.allocate(w, h, GL_RGBA32F_ARB);

	//	Load shader
	shader.unload();
	shader.load("shaders/origami");

	//	Default color
	colors.clear();
	colors.push_back(ofFloatColor(1, 1, 1, 1));
	writeColorsToTex();

	//	Default vertices
	p0s.clear();
	p1s.clear();
	p2s.clear();
	//	1st pnt
	p0s.push_back(ofPoint(0.5, 0.25));
	p1s.push_back(ofPoint(0.75, 0.75));
	p2s.push_back(ofPoint(0.25, 0.75));
	setVertices(p0s, p1s, p2s);
}

void Origami::setColors(vector<ofFloatColor> colors){
	this->colors = colors;
	writeColorsToTex();
}

void Origami::setVertices(vector<ofPoint> v0, vector<ofPoint> v1, vector<ofPoint> v2)
{
	if (v0.size() != v1.size() || v0.size() != v2.size()) return;
	n = v0.size();
	p0s = v0;
	p1s = v1;
	p2s = v2;
	writeVerticesToTex();
}

void Origami::writeColorsToTex(){
	float *colorData = new float[n * 4];
	vector<ofFloatColor> selectedColors;
	for (int i = 0; i < n; ++i) {
		if (i == 0) selectedColors.push_back(colors.at(ofRandom(colors.size())));
		else {
			ofFloatColor color = colors.at(ofRandom(colors.size()));
			while(color == selectedColors.at(i - 1)) color = colors.at(ofRandom(colors.size()));
			selectedColors.push_back(color);
		}
	}
	for (int i = 0; i < n; ++i) {
		ofFloatColor color = selectedColors.at(i);
		colorData[i * 4 + 0] = color.r;
		colorData[i * 4 + 1] = color.g;
		colorData[i * 4 + 2] = color.b;
		colorData[i * 4 + 3] = 1.0;
	}
	colorTex.clear();
	colorTex.allocate(n, 1, GL_RGBA);
	colorTex.loadData(colorData, n, 1, GL_RGBA);
	delete[] colorData;
}

void Origami::writeVerticesToTex(){
	//	P0
	float *p0data = new float[n * 4];
	for (int i = 0; i < n; ++i) {
		p0data[i * 4 + 0] = p0s.at(i).x;
		p0data[i * 4 + 1] = p0s.at(i).y;
		p0data[i * 4 + 2] = 0.0;
		p0data[i * 4 + 3] = 1.0;
	}
	p0Tex.clear();
	p0Tex.allocate(n, 1, GL_RGBA);
	p0Tex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	p0Tex.loadData(p0data, n, 1, GL_RGBA);
	
	//	P1
	float *p1data = new float[n * 4];
	for (int i = 0; i < n; ++i) {
		p1data[i * 4 + 0] = p1s.at(i).x;
		p1data[i * 4 + 1] = p1s.at(i).y;
		p1data[i * 4 + 2] = 0.0;
		p1data[i * 4 + 3] = 1.0;
	}
	p1Tex.clear();
	p1Tex.allocate(n, 1, GL_RGBA);
	p1Tex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	p1Tex.loadData(p1data, n, 1, GL_RGBA);
	
	//	P2
	float *p2data = new float[n * 4];
	for (int i = 0; i < n; ++i) {
		p2data[i * 4 + 0] = p2s.at(i).x;
		p2data[i * 4 + 1] = p2s.at(i).y;
		p2data[i * 4 + 2] = 0.0;
		p2data[i * 4 + 3] = 1.0;
	}
	p2Tex.clear();
	p2Tex.allocate(n, 1, GL_RGBA);
	p2Tex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	p2Tex.loadData(p2data, n, 1, GL_RGBA);
	
	//	Cleanup
	delete[] p0data;
	delete[] p1data;
	delete[] p2data;
}

void Origami::draw(){
	//	Draw to fbo
	fbo.begin();
	ofClear(0, 0, 0, 0);

	//	Shader
	shader.begin();
	shader.setUniform2f("res", w, h);
	shader.setUniform1i("N", n);
	shader.setUniformTexture("colors", colorTex, 0);
	shader.setUniformTexture("p0s", p0Tex, 1);
	shader.setUniformTexture("p1s", p1Tex, 2);
	shader.setUniformTexture("p2s", p2Tex, 3);
	ofDrawRectangle(0, 0, w, h);
	shader.end();

	fbo.end();

	//	Draw
	fbo.draw(x, y);
}

void Origami::reloadShader(){
	shader.unload();
	shader.load("shaders/origami");
}
