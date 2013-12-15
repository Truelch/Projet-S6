#include "Stat.h"


Stat::Stat() {
	//
}

Stat::Stat(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, const char * filename, string name, float hp, float hp_max, float hp_regen, float power, float power_max, float power_regen, float armor, string armor_type, float prod_time, float sight)
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
	set_sight(sight);
}

// --- METHODES ---

// --- GET ---

string Stat::get_name()
{
	return _name;
}

float Stat::get_hp()
{
	return _hp;
}

float Stat::get_hp_max()
{
	return _hp_max;
}

float Stat::get_hp_regen()
{
	return _hp_regen;
}

float Stat::get_power()
{
	return _power;
}

float Stat::get_power_max()
{
	return _power_max;
}

float Stat::get_power_regen()
{
	return _power_regen;
}

float Stat::get_armor()
{
	return _armor;
}

string Stat::get_type_armor()
{
	return _type_armor;
}

float Stat::get_prod_time()
{
	return _prod_time;
}

float Stat::get_sight()
{
	return _sight;
}


// --- SET ---

void Stat::set_name(string name)
{
	_name = name;
}

void Stat::set_hp(float hp)
{
	_hp = hp;
}

void Stat::set_hp_max(float hp_max)
{
	_hp_max = hp_max;
}

void Stat::set_hp_regen(float hp_regen)
{
	_hp_regen = hp_regen;
}

void Stat::set_power(float power)
{
	_power = power;
}

void Stat::set_power_max(float power_max)
{
	_power_max = power_max;
}

void Stat::set_power_regen(float power_regen)
{
	_power_regen = power_regen;
}

void Stat::set_armor(float armor)
{
	_armor = armor;
}

void Stat::set_armor_type(string type_armor)
{
	_type_armor = type_armor;
}

void Stat::set_prod_time(float prod_time)
{
	_prod_time = prod_time;
}

void Stat::set_sight(float sight)
{
	_sight = sight;
}
