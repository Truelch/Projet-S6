#ifndef TILELAYER_H
#define TILELAYER_H

#include "cocos2d.h"

#include <string>
#include <vector>

#include "Layer.h"
#include "MapTile.h"

using namespace std;

//Pour le Tile Layer

typedef vector<vector<MapTile *> > MapTileMatrix;
typedef vector<vector<MapTile *> >::iterator MapTileMatrixIt;

typedef vector<vector<int> > IntMatrix;
typedef vector<vector<int> >::iterator IntMatrixIt;


class TileLayer : public Layer
{
	public:
		TileLayer();
		TileLayer(Scene * scene);
		// --- METHODES ---
		int init_file(string filename);
	
		// --- GET ---

	private:
		IntMatrix _int_matrix;		
		MapTileMatrix _map_tile_matrix;		

		unsigned int _width;
		unsigned int _height;
};

#endif
