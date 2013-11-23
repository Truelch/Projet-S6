#ifndef DISPLAYLAYER_H
#define DISPLAYLAYER_H

#include "cocos2d.h"
#include "CCArmature/external_tool/GLES-Render.h"

#include <string>

#include "Layer.h"
#include "TileLayer.h"
#include "LayerRGBA.h"
#include "UnitLayer.h"
#include "DoodadLayer.h"
#include "BuildingLayer.h"
#include "MapTile.h"
#include "MissileLayer.h"


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
		LayerRGBA *     get_black_layer();
		TileLayer *     get_background_layer();
		LayerRGBA *     get_opacity_layer();
		TileLayer *     get_tile_layer();
		DoodadLayer *   get_doodad_layer();
		BuildingLayer * get_building_layer();
		UnitLayer *     get_unit_layer();
		MissileLayer *  get_missile_layer();
		
		// --- SET ---
		
		// --- METHODES ---
		void init2();
		int init_file(string filename);
		
	private:
		LayerRGBA * _black_layer;      //z = 0
		TileLayer * _background_layer; //z = 1
		LayerRGBA * _opacity_layer;    //z = 2
		TileLayer * _tile_layer;       //z = 3
		DoodadLayer *     _doodad_layer;     //z = 4
		BuildingLayer *		_building_layer;   //z = 5
		UnitLayer * _unit_layer;       //z = 6
		MissileLayer *     _missile_layer;    //z = 7
		
		IntMatrix _int_matrix;
		MapTileMatrix _map_tile_matrix; //=> _tile_layer
		MapTileMatrix _background_map_tile_matrix; //=> _background_layer	

		unsigned int _map_width;
		unsigned int _map_height;
		
		unsigned int _tile_size;
		
		
		cocos2d::extension::GLESDebugDraw* m_debugDraw;
		
};

#endif
