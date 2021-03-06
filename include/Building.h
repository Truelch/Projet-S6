#ifndef BUILDING_H
#define BUILDING_H

#include "cocos2d.h"
#include "PhysicsDisplayable.h"
#include <string>
#include <vector>
#include "Turret.h"
#include "Production.h"

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
		Building(int x, int y, const char * filename, Game * game, Layer * layer, float x_rally_point, float y_rally_point, std::string name, Player * player, float sight);
		Building(MapTile * mapTile, const char * filename, Game * game, Layer  * layer, float x_rally_point, float y_rally_point, std::string name, Player * player, float sight);
		
		// --- GET ---
		CCPoint                              get_rally_point()     { return _rally_point; }
		virtual Displayable::DisplayableType getType()             { return Displayable::buildingType; }
		Player *                             get_player();
		std::string                          get_name()            { return _name; }
		int                                  get_supply()          { return _supply; }
		std::vector<Turret *>&               get_turret_list()     { return _turret_list; }
		std::vector<Production *>            get_production_list() { return _production_list; }
		float get_sight() { return _sight; }
		MapTile * get_map_tile() { return _map_tile; }
		const std::vector<MapTile *>& get_range_map_tile_list() { return _range_map_tile_list; }
		
		void set_rally_point(float x_rally_point, float y_rally_point)
		{
			_rally_point.x = x_rally_point;
			_rally_point.y = y_rally_point;
		};
		void        set_rally_point(CCPoint rally_point) { _rally_point = rally_point; }
		void        set_player(Player * player);
		void        set_supply(int supply);
		void set_sight(float sight) { _sight = sight; }
		void        set_name(std::string name); //Ne devrait pas être utilisé
		//Créé toutes les méthodes pour manipuler le container à Tourelles et celui à Productions => Quoique
		
		// --- METHODES ---
		virtual void update(float dt);
		
		void check_attack();

		bool map_tile_range(MapTile * map_tile);
		
	private:
		void init();

		CCPoint   _rally_point;
		MapTile * _map_tile;
		
		Player *  _player;
		
		//Ajouts
		std::string               _name;
		int                       _supply;
		std::vector<Turret *>     _turret_list;
		std::vector<Production *> _production_list;

		float _sight;

		std::vector<MapTile *> _range_map_tile_list;

		void update_range_map_tile_list();
};

#endif
