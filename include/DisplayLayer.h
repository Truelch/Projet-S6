#ifndef DISPLAYLAYER_H
#define DISPLAYLAYER_H

#include "cocos2d.h"
#include "CCArmature/external_tool/GLES-Render.h"

#include <string>

#include "Layer.h"

class TileLayer;
class BackgroundLayer;
class LayerRGBA;
class UnitLayer;
class DoodadLayer;
class BuildingLayer;
class MapTile;
class MissileLayer;

//Pour le Tile Layer

typedef vector<vector<MapTile *> > MapTileMatrix;
typedef vector<vector<MapTile *> >::iterator MapTileMatrixIt;

typedef vector<vector<std::string> > StringMatrix;
typedef vector<vector<std::string> >::iterator StringMatrixIt;

using namespace std;

class DisplayLayer : public Layer
{
	public:
		DisplayLayer();
		DisplayLayer(Game * game);
		~DisplayLayer();

		virtual void draw();

	
		// --- GET ---
		LayerRGBA *       get_black_layer();
		BackgroundLayer * get_background_layer();
		LayerRGBA *       get_opacity_layer();
		TileLayer *       get_tile_layer();
		DoodadLayer *     get_doodad_layer();
		BuildingLayer *   get_building_layer();
		UnitLayer *       get_unit_layer();
		MissileLayer *    get_missile_layer();

		int get_tile_size_pixel() { return (int)_tile_size; }
		float get_tile_size_cocos();
		int get_map_width() { return (int)_map_width; }
		int get_map_height() { return (int)_map_height; }
		
		// --- SET ---
		
		// --- METHODES ---
		void init2();
		void coordonate_tile_to_cocos2dx(int x, int y, float& cocos_x, float& cocos_y);
		void coordonate_cocos2dx_to_tile(float cocos_x, float cocos_y, int& x, int& y);
		int init_file(std::string filename);
		
	private:
		LayerRGBA *        _black_layer;      //z = 0
		BackgroundLayer *  _background_layer; //z = 1
		LayerRGBA *        _opacity_layer;    //z = 2
		TileLayer *        _tile_layer;       //z = 3
		DoodadLayer *      _doodad_layer;     //z = 4
		BuildingLayer *	   _building_layer;   //z = 5
		UnitLayer *        _unit_layer;       //z = 6
		MissileLayer *     _missile_layer;    //z = 7
		
		//StringMatrix _string_matrix;
		//MapTileMatrix _map_tile_matrix;            //=> _tile_layer
		//MapTileMatrix _background_map_tile_matrix; //=> _background_layer	

		unsigned int _map_width;
		unsigned int _map_height;
		
		unsigned int _tile_size; //= 128px
};

#endif
