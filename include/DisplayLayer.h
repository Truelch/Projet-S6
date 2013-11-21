#ifndef DISPLAYLAYER_H
#define DISPLAYLAYER_H

#include "cocos2d.h"
#include "CCArmature/external_tool/GLES-Render.h"

#include <string>

#include "Layer.h"
#include "TileLayer.h"
#include "LayerRGBA.h"
#include "UnitLayer.h"

//Pour le Tile Layer

typedef vector<vector<MapTile *> > MapTileMatrix;
typedef vector<vector<MapTile *> >::iterator MapTileMatrixIt;

typedef vector<vector<int> > IntMatrix;
typedef vector<vector<int> >::iterator IntMatrixIt;

using namespace std;

class DisplayLayer : public Layer
{
	public:
		DisplayLayer();
		DisplayLayer(Scene * scene);

		virtual void draw();

	
		// --- GET ---
		LayerRGBA * get_black_layer();
		Layer *     get_background_layer();
		LayerRGBA * get_opacity_layer();
		TileLayer * get_tile_layer();
		Layer *     get_doodad_layer();
		UnitLayer *     get_unit_layer();
		Layer *     get_missile_layer();
		
		// --- SET ---
		
		// --- METHODES ---
		void init2();
		int init_file(string filename);
		
	private:
		LayerRGBA * _black_layer;      //z = 0
		Layer *     _background_layer; //z = 1
		LayerRGBA * _opacity_layer;    //z = 2
		TileLayer * _tile_layer;       //z = 3
		Layer *     _doodad_layer;     //z = 4
		UnitLayer *     _unit_layer;       //z = 5
		Layer *     _missile_layer;    //z = 6
		
		IntMatrix     _int_matrix;
		MapTileMatrix _map_tile_matrix;            //=> _tile_layer
		MapTileMatrix _background_map_tile_matrix; //=> _background_layer	

		MapTile * _mapTile;

		unsigned int  _map_width;
		unsigned int  _map_height;
		
		unsigned int _tile_size;
		
		cocos2d::extension::GLESDebugDraw* m_debugDraw;
		
};

#endif
