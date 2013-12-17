#ifndef CURSOR
#define CURSOR

#include "cocos2d.h"

class Cursor : public CCSprite {
	public:
		Cursor(float x, float y, const char * filename, Game * game, Layer * layer);

		virtual Displayable::DisplayableType getType() { return Displayable::mapTileType; }
};

#endif
