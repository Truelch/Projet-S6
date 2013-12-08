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

class FogOfWarLayer;

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
		void addDebugLine(CCPoint p1, CCPoint p2);
		void set_debug_mode(bool debug_mode);
		bool get_debug_mode() { return _debug_mode; }
	
		// --- GET ---
		LayerRGBA *        get_black_layer();
		BackgroundLayer *  get_background_layer();
		LayerRGBA *        get_opacity_layer();
		TileLayer *        get_tile_layer();
		DoodadLayer *      get_doodad_layer();
		BuildingLayer *    get_building_layer();
		UnitLayer *        get_unit_layer();
		MissileLayer *     get_missile_layer();
		FogOfWarLayer *    get_fog_of_war_layer();
		Layer *            get_selection_zone_layer();

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
		LayerRGBA *        _black_layer;          //z = 0
		BackgroundLayer *  _background_layer;     //z = 1
		LayerRGBA *        _opacity_layer;        //z = 2
		TileLayer *        _tile_layer;           //z = 3
		DoodadLayer *      _doodad_layer;         //z = 4
		BuildingLayer *	   _building_layer;       //z = 5
		UnitLayer *        _unit_layer;           //z = 6
		MissileLayer *     _missile_layer;        //z = 7
		FogOfWarLayer *    _fog_of_war_layer;     //z = 8
		Layer *            _selection_zone_layer; //z = 9
		
		//StringMatrix _string_matrix;
		//MapTileMatrix _map_tile_matrix;            //=> _tile_layer
		//MapTileMatrix _background_map_tile_matrix; //=> _background_layer	

		unsigned int _map_width;
		unsigned int _map_height;
		
		unsigned int _tile_size; //= 128px

		typedef struct {
			b2Vec2 p1;
			b2Vec2 p2;
		} Line;
		vector<Line> _debug_line;
		bool _debug_mode;
};

#endif
