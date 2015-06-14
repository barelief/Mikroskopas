#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	loadSettings();
}

//--------------------------------------------------------------
void ofApp::update()
{	
	player.update();
	
	if (!videoIsStopped)
	{

		if (idle.isTimerFinished() && !isFading)
		{
			fadeOut.reset();
			fadeOut.startTimer();
			isFading = true;
		}

		if (fadeOut.isTimerFinished())
			stopMovie(); 
	}


}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0);
	player.draw(videoPosition.x, videoPosition.y,1080,1080);

	// fade
	ofEnableAlphaBlending();
	int curtain = ofMap(fadeOut.getTimeLeft(), 1,0, 0, 255);
	ofSetColor(0,curtain);
	ofRect(0,0,ofGetWidth(), ofGetHeight());
	player.setVolume(fadeOut.getTimeLeft());

	// debug
	ofSetColor(255);
	debug();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch(key)
	{
	case OF_KEY_LEFT:
		videoPosition.x--;
		break;
	case OF_KEY_RIGHT:
		videoPosition.x++;
		break;
	case OF_KEY_UP:
		videoPosition.y--;
		break;
	case OF_KEY_DOWN:
		videoPosition.y++;
		break;
	case 'f':
		ofToggleFullscreen();
		break;
	}

	settings.setValue("x", videoPosition.x);
	ofLog(OF_LOG_NOTICE, "x position: %f", videoPosition.x);

	settings.setValue("y", videoPosition.y);
	ofLog(OF_LOG_NOTICE, "y position: %f", videoPosition.y);

	// save new settings to file 
	settings.saveFile("settings.xml");
	ofLog(OF_LOG_NOTICE, "saved to settings.txt");
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{ 
	vector< string > fileList = dragInfo.files;
	fileName = fileList[0];
	// loadVideoFile(fileName);
	player.loadMovie(fileName);

	ofLog(OF_LOG_NOTICE, "dragged files:");
	ofLog(OF_LOG_NOTICE, fileList[0]);

	// save video file name to xml so the next time it's opended automatically
	settings.setValue("file", fileName);
	settings.saveFile("settings.xml");
	cout << "--> Saved " << fileName << " as default video file" << endl;
}
