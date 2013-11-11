#include "Unit.h"


Unit::Unit(): Moveable() {
	//
}

Unit::Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, const char * filename, string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, string armor_type, int prod_time): Moveable(x, y, x_dest, y_dest, rotation, move_speed, filename)
{
	_stat = new Stat();
	_stat->set_name(name);
	_stat->set_hp(hp);
	_stat->set_hp_max(hp_max);
	_stat->set_hp_regen(hp_regen);
	_stat->set_power(power);
	_stat->set_power_max(power_max);
	_stat->set_power_regen(power_regen);
	_stat->set_armor(armor);
	_stat->set_armor_type(armor_type);
	_stat->set_prod_time(prod_time);
}

// --- METHODES ---

// --- GET ---

Stat * Unit::get_stat()
{
	return _stat;
}
