#ifndef BUILDING_H
#define BUILDING_H

#include "cocos2d.h"
#include "PhysicsDisplayable.h"

#include <vector>

class MapTile;
class Game;
class TileLayer;
class Player;
class MapTile;

class Building : public PhysicsDisplayable
{
	public:
		Building();
		Building(int x, int y, const char * filename, Game * game, Layer * layer, float x_rally_point, float y_rally_point, Player * player, float sight);
		Building(MapTile * mapTile, const char * filename, Game * game, Layer  * layer, float x_rally_point, float y_rally_point, Player * player, float sight);
		
		// --- GET ---
		CCPoint get_rally_point() { return _rally_point; }
		virtual Displayable::DisplayableType getType() { return Displayable::buildingType; }
		Player * get_player();
		float get_sight() { return _sight; }
		MapTile * get_map_tile() { return _map_tile; }
		const std::vector<MapTile *>& get_range_map_tile_list() { return _range_map_tile_list; }
		
		// --- SET ---
		void set_rally_point(float x_rally_point, float y_rally_point)
		{
			_rally_point.x = x_rally_point;
			_rally_point.y = y_rally_point;
		};
		void set_rally_point(CCPoint rally_point) { _rally_point = rally_point; }
		void set_player(Player * player);
		void set_sight(float sight) { _sight = sight; }

		bool map_tile_range(MapTile * map_tile);
		
	private:
		void init();

		CCPoint   _rally_point;
		MapTile * _map_tile;
		
		Player *  _player;

		float _sight;

		std::vector<MapTile *> _range_map_tile_list;

		void update_range_map_tile_list();
};

#endif
