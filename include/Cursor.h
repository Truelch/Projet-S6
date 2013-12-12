#ifndef CURSOR
#define CURSOR

#include "Displayable.h"

class Cursor : public Displayable {
	public:
		Cursor(float x, float y, const char * filename, Game * game, Layer * layer);

		virtual Displayable::DisplayableType getType() { return Displayable::mapTileType; }
};

#endif
