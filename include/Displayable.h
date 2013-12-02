#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include "cocos2d.h"
#include "EventReceiver.h"

class Layer;
class Game;

USING_NS_CC;

using namespace cocos2d;

class Displayable : public EventReceiver
{
	public:
		typedef enum {
			displayableType,
			corpseType,
			hudType,
			mapDisplayableType,
			mapTileType,
			missileType,
			physicsDisplayableType,
			buildingType,
			moveableType,
			unitType,
			powerNodeType,
			turretType,
		} DisplayableType;

	public:
		Displayable();
		Displayable(float x, float y, float rotation, const char * filename, Game * game, Layer * layer);
		Displayable(Game * _game, CCSprite * sprite, Layer * layer);
		virtual ~Displayable();

		Game * getGame() { return _game; }
		CCSprite * getSprite() { return _sprite; }
		Layer * getLayer() { return _layer; }
		virtual DisplayableType getType() { return displayableType; }

		void setGame(Game * game) { _game = game; }
		void setSprite(CCSprite * sprite) { _sprite = sprite; }
		void setLayer(Layer * layer) { _layer = layer; }
	private:
		CCSprite * _sprite;
		Game * _game;
		Layer * _layer;
};

#endif
