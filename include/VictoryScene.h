#ifndef VICTORY_SCENE
#define VICTORY_SCENE

#include "Scene.h"

class VictoryScene : public Scene {
	private:
		cocos2d::CCSprite * _victory_image;
		cocos2d::CCLayer * _layer;

	public:
		VictoryScene(const char * filename);
		~VictoryScene();

		virtual void key_press(int key);
};

#endif
