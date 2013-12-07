#ifndef UNIT_LAYER
#define UNIT_LAYER

#include <vector>
#include <iostream>
#include "Layer.h"
#include "Container.h"

class Unit;

class UnitLayer : public Layer {
	public:
		UnitLayer();
		UnitLayer(Game * game);
			
		Unit * get_unit(int index) { return _unit_list.get_t(index); }
		void   remove_unit(Unit *);
		void   add_unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float groundFixture, float density, const char * filename, std::string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time, Player * owner,float sight);
		int    get_number_unit() { return _unit_list.get_number_t(); }

	private:
		Container<Unit> _unit_list;
};

#endif
