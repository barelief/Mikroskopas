#pragma once

#include "ofMain.h"
#include "ofxSimpleSerial.h"
#include "ofxXmlSettings.h"
#include "ofxTimer.h"
#include "ofxScreenCurtain.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// serial
	ofxSimpleSerial	serial;
	string message;

	//video
	ofVideoPlayer player;
	string fileName;
	ofPoint videoPosition;
	ofxXmlSettings settings; 

	// curtain / fade
	// ofxScreenCurtain curtain;

	void stopMovie()
	{
		player.setPosition( 0 );
		player.setPaused(true);
		videoIsStopped = true;
		ofLog(OF_LOG_NOTICE, "PAUSED Movie");
	}

	void playMovie()
	{
		ofLog(OF_LOG_NOTICE, "STARTED Playing Movie");
		//player.setPosition(0);
		player.play();
		idle.startTimer();
		idle.reset();
		videoIsStopped = false;

		// fade
		fadeOut.reset();
		fadeOut.pauseTimer();
		isFading = false;
	}

	void loadSettings()
	{
		cout << "welcome to Microscope!\n";

		if( settings.loadFile("settings.xml") )
		{
			ofLog(OF_LOG_NOTICE,"settings.xml loaded!");
		} 
		else 
		{
			ofLog(OF_LOG_ERROR,"unable to load settings.xml check data/ folder");
		}

		if ( settings.getValue("fullscreen",1) == 1 )
			ofToggleFullscreen();

		setupVideo();
		setupSerial();
		setupTimer();
	}

	void setupVideo()
	{
		fileName = settings.getValue("file", "MICROWORLD.mp4");
		videoPosition.x = settings.getValue("x", 0);
		videoPosition.y = settings.getValue("y", 0);
		player.loadMovie(fileName);
		player.play();
		player.stop();
		player.setLoopState(OF_LOOP_NONE);
	}

	void setupSerial()
	{
		string port;
		int baud;
		port = settings.getValue("port", "COM3");
		baud = settings.getValue("baud", 9600);
		serial.setup(port, baud);
		serial.startContinuousRead();
		ofAddListener(serial.NEW_MESSAGE,this,&ofApp::onNewMessage);
		message = "";
	}

	ofxTimer idle, lock;
	ofxTimer fadeOut, fadeIn;
	bool videoIsStopped;
	bool isFading;

	void setupTimer()
	{
		int idleTime = settings.getValue("idle",7);
		idle.setup(1000 * idleTime,false);
		ofLog(OF_LOG_NOTICE, "Idle time: %f", idle.getTimeLeftInSeconds());
		videoIsStopped = false;
		//idle.reset();
		//idle.stopTimer();
		fadeOut.setup(2000, false);
		fadeOut.pauseTimer();
		isFading = false;
	}

	void debug()
	{
		ofDrawBitmapString("idle time left: " + 
			ofToString( idle.getTimeLeftInSeconds() )
			+ "\n" +
			"fadeOut: " + ofToString( fadeOut.getTimeLeft() ), 20,20);
	}

	void onNewMessage(string & message)
	{
		// if (message == "@")

		cout << "Yra žmogus prie daviklio: " << message << endl;

		if (idle.isTimerFinished())
		{
			playMovie();
		} 
		else 
		{
			idle.reset();
		}
	}

};
