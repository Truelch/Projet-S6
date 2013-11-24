#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include "cocos2d.h"
#include "Scene.h"

USING_NS_CC;

using namespace cocos2d;

class Displayable
{
	public:
		Displayable();
		Displayable(CCSprite * sprite);
		Displayable(float x, float y, float rotation, const char * filename, Scene * _scene);
		Displayable(Scene * _scene, CCSprite * sprite);
		virtual ~Displayable();

		Scene * getScene() { return _scene; }
		CCSprite * getSprite() { return _sprite; }

		void setScene(Scene * scene) { _scene = scene; }
		void setSprite(CCSprite * sprite) { _sprite = sprite; }
	private:
		CCSprite * _sprite;
		Scene * _scene;
};

#endif
