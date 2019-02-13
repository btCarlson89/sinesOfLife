#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.setGLVersion(4, 1);
	settings.setSize(3000, 1000);
	//settings.multiMonitorFullScreen = true;
	//settings.windowMode = OF_FULLSCREEN;
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
