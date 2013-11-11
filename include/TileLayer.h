#ifndef TILELAYER_H
#define TILELAYER_H

#include "cocos2d.h"

#include <string>
#include <vector>

#include "Layer.h"
#include "MapTile.h"

using namespace std;

//Pour le Tile Layer

typedef vector<vector<MapTile *> > Matrix;
typedef vector<vector<MapTile *> >::iterator row;


class TileLayer : public Layer
{
	public:
		TileLayer();
		TileLayer(Scene * scene);
		// --- METHODES ---
		void init2();
	
		// --- GET ---
		Matrix * get_tile_matrix;

	private:
		Matrix * _tile_matrix;		
};

#endif
