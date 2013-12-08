#ifndef UNIT_H
#define UNIT_H

#include "cocos2d.h"

#include <string>
#include <vector>

#include "Moveable.h"
#include "AIStat.h"
#include "Stat.h"
#include "Turret.h"


class Player;
class Bar;

class Unit : public Moveable
{
	private:
		Player * _player;
		Stat *   _stat;
		AIStat * _ai_stat;
		Unit *   _target;
		vector<Turret *>  _turret_list; //Non partagabilité => pas de pointeurs mais attribut "direct"
		vector<MapTile *> _range_map_tile_list;

		Bar * _bar;
		bool _selected;
		bool _bar_visible;

		virtual void updateCoordonates();
		void update_range_map_tile_list();

	public:
		Unit();
		Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float groundFixture, float density, const char * filename, Game * game, Layer * layer, string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time, Player * owner, float sight);
		virtual ~Unit();

		// get stat
		string get_name();
		int get_hp();
		int get_hp_max();
		int get_hp_regen();
		int get_power();
		int get_power_max();
		int get_power_regen();
		int get_armor();
		string get_type_armor();
		int get_prod_time();
		float get_sight();

		// set stat
		void set_name(string name);
		void set_hp(int hp);
		void set_hp_max(int hp_max);
		void set_hp_regen(int hp_regen);
		void set_power(int power);
		void set_power_max(int power_max);
		void set_power_regen(int power_regen);
		void set_armor(int armor);
		void set_armor_type(string armor_type);
		void set_prod_time(int prod_time);
		void set_sight(float sight);

		// --- GET ---
		Player * getPlayer() { return _player; }
		AIStat * get_ai_stat();
		virtual Displayable::DisplayableType getType() { return Displayable::unitType; }
		const vector<MapTile *>& get_range_map_tile_list() { return _range_map_tile_list; }
		Bar * get_bar() { return _bar; }
		bool get_selected() { return _selected; }
		bool get_bar_visible() { return _bar_visible; }

		// --- SET ---
		void setPlayer(Player * player) { _player = player; }
		void set_selected(bool selected);
		void set_bar_visible(bool bar_visible);

		// --- METHODES ---
		virtual void update(float dt);
		virtual void on_displayable_contact(Displayable * displayableA, Displayable * displayableB);
		void on_player_range_tile(int x, int y, Player * player);
		void on_player_unrange_tile(int x, int y, Player * player);
		void update_bar_visibility();

		bool map_tile_range(MapTile * map_tile);
		void check_attack(); //Vérifie pour chaque tourelle (traverse le container de turret et appelle la méthode check_attack de chaque turret)
};

#endif
