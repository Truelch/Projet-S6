#ifndef TILELAYER_H
#define TILELAYER_H

#include "cocos2d.h"

#include <string>
#include <vector>

#include "Layer.h"
#include "MapTile.h"

using namespace std;

class TileLayer : public Layer
{
	public:
		TileLayer();
		TileLayer(Game * game);
		// --- METHODES ---
		
		// --- GET ---
		std::vector<std::vector<MapTile *> >& get_map_tile_matrix();
		
	private:
		std::vector<std::vector<MapTile *> > _map_tile_matrix;
};

#endif
