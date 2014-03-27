#ifndef UNIT_LAYER_H
#define UNIT_LAYER_H

#include <vector>
#include <iostream>
#include <map>
#include "Layer.h"
#include "Container.h"

class Unit;

class UnitLayer : public Layer {
	public:
		UnitLayer();
		UnitLayer(Game * game);
			
		Unit * get_unit(int index) { return _unit_list.get_t(index); }
		void   remove_unit(Unit * unit);
		void   add_unit(std::string name, float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float hitboxRadius, float groundFixture, float density, const char * filename, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time,float sight, Player * owner);
		bool add_unit(std::string name, float x, float y, float x_dest, float y_dest, float rotation, std::string unit_type, Player * owner);
		int    get_number_unit() { return _unit_list.get_number_t(); }

		char init_unit_catalog(std::string filename);

	private:
		typedef struct {
			float rotation;
			char * filename;
			float x_relative;
			float y_relative;
			float missile_speed;
			char * missile_filename;
			int damage;
			float cooldown;
			float range_max;
		} TurretStat;
		typedef struct {
			float move_speed;
			float hitboxRadius;
			float groundFixture;
			float density;
			char * filename;
			int hp;
			int hp_max;
			int hp_regen;
			int power;
			int power_max;
			int power_regen;
			int armor;
			int prod_time;
			float sight;
			std::vector<TurretStat> turret_list;
		} UnitStat;

		Container<Unit> _unit_list;
		std::map<std::string,UnitStat> _unit_catalog;
};

#endif
