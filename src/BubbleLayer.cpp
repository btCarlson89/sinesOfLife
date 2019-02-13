#include "BubbleLayer.h"



BubbleLayer::BubbleLayer() :
	x(0),
	y(0),
	w(100),
	h(100),
	n(1) {
	setup();
}

BubbleLayer::BubbleLayer(float xpos, float ypos, float width, float height, float numBubbles) :
	x(xpos),
	y(ypos),
	w(width),
	h(height),
	n(numBubbles) {
	setup();
}

void BubbleLayer::setup() {
	//	Allocate fbo
	fbo.allocate(w, h, GL_RGBA32F_ARB);
	//	Load shader
	shader.load("shaders/bubbles");
	//	Default color
	color = ofFloatColor(1, 1, 1, 1);
}

void BubbleLayer::setColor(ofFloatColor color) {
	this->color = color;
}

void BubbleLayer::draw() {
	//	Draw to fbo
	fbo.begin();
	ofClear(0, 0, 0, 0);
	//	Shader
	shader.begin();
	shader.setUniform4f("color", color);
	shader.setUniform2f("res", w, h);
	shader.setUniform1f("time", ofGetElapsedTimef() * 0.5);
	ofDrawRectangle(0, 0, w, h);
	shader.end();
	fbo.end();
	//	Draw
	fbo.draw(x, y);
}

void BubbleLayer::reloadShader() {
	shader.unload();
	shader.load("shaders/bubbles");
}
