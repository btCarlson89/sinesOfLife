#include "Panel.h"

Panel::Panel() :
	x(0),
	y(0),
	w(100),
	h(100),
	xOffset(0),
	yOffset(0),
	shadowDirection(0){
	setup();
}



Panel::Panel(float xpos, float ypos, float width, float height, float xOff, float yOff, int direction) :
	x(xpos),
	y(ypos),
	w(width),
	h(height),
	xOffset(xOff),
	yOffset(yOff),
	shadowDirection(direction){
	setup();
}

void Panel::setup(){
	//	Allocate fbo
	fbo.allocate(w, h, GL_RGBA32F_ARB);
	//	Default colors
	color = ofFloatColor(1, 1, 1, 1);
	//	Default pad
	pad = 100;
	//	Load shader
	shader.load("shaders/panel");
}

void Panel::setColor(ofFloatColor color){
	this->color = color;
}

void Panel::setGradient(float start, float end){
	gradientStart = start;
	gradientEnd = end;
}

void Panel::draw(){
	//	Draw to fbo
	fbo.begin();
	//	Shader
	shader.begin();
	shader.setUniform1i("dir", shadowDirection);
	shader.setUniform1f("pad", pad);
	shader.setUniform2f("res", w, h);
	shader.setUniform2f("pos", xOffset, yOffset);
	shader.setUniform4f("color", color);
	shader.setUniform1f("gradientStart", gradientStart);
	shader.setUniform1f("gradientEnd", gradientEnd);
	ofDrawRectangle(0, 0, w, h);
	shader.end();
	fbo.end();
	//	Draw
	fbo.draw(x, y);
}

void Panel::reloadShader(){
	shader.unload();
	shader.load("shaders/panel");
}
