#include "AppDelegate.h"
#include "cocos2d.h"
#include "EGLView.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <time.h>

#include <GL/glfw.h>

#include "SimpleAudioEngine.h"

USING_NS_CC;

int main(int argc, char **argv)
{
	// create the application instance
	AppDelegate app;

	srand(time(NULL));

	std::vector<std::string> _list_background_music;

	_list_background_music.push_back("audio/Daft Punk - Tron Uprising.mp3");
	/*
	_list_background_music.push_back("audio/02 Bad Wings.mp3");
	_list_background_music.push_back("audio/03 How To Be Eaten By A Woman.mp3");
	_list_background_music.push_back("audio/04 A Dream Within A Dream.mp3");
	_list_background_music.push_back("audio/05 Fistful Of Silence.mp3");
	_list_background_music.push_back("audio/08 Drive It Like You Stole It.mp3");
	_list_background_music.push_back("audio/09 Fortune Days.mp3");
	*/

	unsigned int i;
	for(i=0; i<_list_background_music.size(); i++) {
		std::cout << "chargement " << _list_background_music[i] << std::endl;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(_list_background_music[i].c_str());
	}

	/*
	std::cout << std::endl << "press any key to continue" << std::endl;
	std::cin.ignore();
	*/

	EGLView* eglView = EGLView::sharedOpenGLView();
	eglView->setFrameSize(1024,768);

	cocos2d::CCApplication * app2 = CCApplication::sharedApplication();
	app2->run();

	return 0;
}
