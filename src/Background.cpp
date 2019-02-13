#include "Background.h"

Background::Background() :
	x(0),
	y(0),
	w(100),
	h(100) {
	setup();
}

Background::Background(float xpos, float ypos, float width, float height) :
	x(xpos),
	y(ypos),
	w(width),
	h(height) {
	setup();
}

void Background::setup() {
	//	Allocate fbo
	fbo.allocate(w, h, GL_RGBA32F_ARB);
	//	Default colors
	colorTL = ofFloatColor(1, 0, 0, 1);
	colorTR = ofFloatColor(0, 1, 0, 1);
	colorBR = ofFloatColor(0, 0, 1, 1);
	colorBL = ofFloatColor(1, 1, 1, 1);
	//	Load shader
	shader.load("shaders/bg");
}

void Background::setColors(ofFloatColor tl, ofFloatColor tr, ofFloatColor br, ofFloatColor bl) {
	//	Assign colors
	colorTL = tl;
	colorTR = tr;
	colorBR = br;
	colorBL = bl;
}

void Background::draw() {
	//	Draw to fbo
	fbo.begin();
	//	Shader
	shader.begin();
	shader.setUniform2f("res", w, h);
	shader.setUniform4f("colorTL", colorTL);
	shader.setUniform4f("colorTR", colorTR);
	shader.setUniform4f("colorBL", colorBL);
	shader.setUniform4f("colorBR", colorBR);
	ofDrawRectangle(0, 0, w, h);
	shader.end();
	fbo.end();
	//	Draw
	fbo.draw(x, y);
}

void Background::reloadShader()
{
	shader.unload();
	shader.load("shaders/bg");
}
