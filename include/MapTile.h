#ifndef MAP_TILE_H
#define MAP_TILE_H

#include "MapDisplayable.h"

class MapTile : public MapDisplayable {
	public:
		MapTile();
		MapTile(float x, float y, const char * filename, Scene * scene, Layer * layer, bool crossUp = true, bool crossDown = true, bool crossRight = true, bool crossLeft = true);

	private:
		bool _crossUp;
		bool _crossDown;
		bool _crossRight;
		bool _crossLeft;
};

#endif
