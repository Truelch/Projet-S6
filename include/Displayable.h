#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include "cocos2d.h"
#include "Scene.h"
#include "EventReceiver.h"

class Layer;

USING_NS_CC;

using namespace cocos2d;

class Displayable : public EventReceiver
{
	public:
		Displayable();
		Displayable(float x, float y, float rotation, const char * filename, Scene * scene, Layer * layer);
		Displayable(Scene * _scene, CCSprite * sprite, Layer * layer);
		virtual ~Displayable();

		Scene * getScene() { return _scene; }
		CCSprite * getSprite() { return _sprite; }
		Layer * getLayer() { return _layer; }

		void setScene(Scene * scene) { _scene = scene; }
		void setSprite(CCSprite * sprite) { _sprite = sprite; }
		void setLayer(Layer * layer) { _layer = layer; }
	private:
		CCSprite * _sprite;
		Scene * _scene;
		Layer * _layer;
};

#endif
