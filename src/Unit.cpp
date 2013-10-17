#include "Unit.h"

Unit::Unit(): Moveable() {
	//
}

Unit::Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, const char * filename, string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, string armor_type, int prod_time): Moveable(x, y, x_dest, y_dest, rotation, move_speed, filename)
{
	set_name(name);
	set_hp(hp);
	set_hp_max(hp_max);
	set_hp_regen(hp_regen);
	set_power(power);
	set_power_max(power_max);
	set_power_regen(power_regen);
	set_armor(armor);
	set_armor_type(armor_type);
	set_prod_time(prod_time);
}

// --- GET ---

string Unit::get_name()
{
	return _name;
}

int Unit::get_hp()
{
	return _hp;
}

int Unit::get_hp_max()
{
	return _hp_max;
}

int Unit::get_hp_regen()
{
	return _hp_regen;
}

int Unit::get_power()
{
	return _power;
}

int Unit::get_power_max()
{
	return _power_max;
}

int Unit::get_power_regen()
{
	return _power_regen;
}

int Unit::get_armor()
{
	return _armor;
}

string Unit::get_type_armor()
{
	return _type_armor;
}

int Unit::get_prod_time()
{
	return _prod_time;
}


// --- SET ---

void Unit::set_name(string name)
{
	_name = name;
}

void Unit::set_hp(int hp)
{
	_hp = hp;
}

void Unit::set_hp_max(int hp_max)
{
	_hp_max = hp_max;
}

void Unit::set_hp_regen(int hp_regen)
{
	_hp_regen = hp_regen;
}

void Unit::set_power(int power)
{
	_power = power;
}

void Unit::set_power_max(int power_max)
{
	_power_max = power_max;
}

void Unit::set_power_regen(int power_regen)
{
	_power_regen = power_regen;
}

void Unit::set_armor(int armor)
{
	_armor = armor;
}

void Unit::set_armor_type(string type_armor)
{
	_type_armor = type_armor;
}

void Unit::set_prod_time(int prod_time)
{
	_prod_time = prod_time;
}
