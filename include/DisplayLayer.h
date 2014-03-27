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
		typedef enum {
			none,
			collision,
			gradient,
		} Joint;
		typedef struct {
			Joint        up;
			Joint        upRight;
			Joint        right;
			Joint        downRigh;
			Joint        down;
			Joint        downLeft;
			Joint        left;
			Joint        upLeft;
		} JointSet;
		typedef struct {
			std::string sprite;
			JointSet     jointSet;
			int          level;
			ccColor4B    colorMap;
		} TileID;

	public:
		DisplayLayer();
		DisplayLayer(Game * game);
		~DisplayLayer();

		virtual void draw();
		void addDebugLine(CCPoint p1, CCPoint p2);
		void clearDebugLine() { _debug_line.clear(); }
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

		std::map<std::string,TileID>& get_sprite_map() { return _sprite_map; }
		
		// --- SET ---
		
		// --- METHODES ---
		void init2();
		void coordonate_tile_to_cocos2dx(int x, int y, float& cocos_x, float& cocos_y);
		void coordonate_cocos2dx_to_tile(float cocos_x, float cocos_y, int& x, int& y);

		char init_file(std::string filename);
		
	private:
	
		class TileSetItem {
			public:
				TileSetItem(int i, int j): _i(i), _j(j), _sprite(""), _falsity(0) {}
				TileSetItem(int i, int j, std::string sprite, int falsity): _i(i), _j(j), _sprite(sprite), _falsity(falsity) {}
				bool operator<(const TileSetItem& t) const {
					if(_falsity!=t._falsity)
						return _falsity<t._falsity;
					if(_i!=t._i)
						return _i<t._i;
					return _j<t._j;
				}
				bool operator==(const TileSetItem& t) const {
					return _i==t._i && _j==t._j;
				}
				int _i,_j;
				std::string _sprite;
				int _falsity;
		};

		std::string search_sprite(JointSet jointSet, int level);
		void check_string_tile(const StringMatrix& string_matrix, unsigned int i, unsigned int j, std::string& new_sprite, int& falsity);
		void check_string_matrix(StringMatrix& string_matrix);
		char read_plain_text_file(string filename, StringMatrix& string_matrix);
		char read_tmx_file(string filename, StringMatrix& string_matrix);

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

		std::map<std::string,TileID> _sprite_map;
};

#endif
