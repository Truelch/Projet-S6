#ifndef BUILDING_H
#define BUILDING_H

#include "cocos2d.h"
#include "PhysicsDisplayable.h"

class MapTile;
class Game;
class TileLayer;
class Player;

class Building : public PhysicsDisplayable
{
	public:
		Building();
		Building(int x, int y, const char * filename, Game * game, Layer * layer, float x_rally_point, float y_rally_point);
		Building(MapTile * mapTile, const char * filename, Game * game, Layer  * layer, float x_rally_point, float y_rally_point);
		
		// --- GET ---
		CCPoint get_rally_point() { return _rally_point; }
		virtual Displayable::DisplayableType getType() { return Displayable::buildingType; }
		Player * get_player();
		
		// --- SET ---
		void set_rally_point(float x_rally_point, float y_rally_point)
		{
			_rally_point.x = x_rally_point;
			_rally_point.y = y_rally_point;
		};
		void set_rally_point(CCPoint rally_point) { _rally_point = rally_point; }
		void set_player(Player * player);
		
		// --- METHODES ---

	private:
		void init();

		CCPoint   _rally_point;
		MapTile * _map_tile;
		
		Player *  _player;
};

#endif
