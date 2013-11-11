#include "Stat.h"


Stat::Stat() {
	//
}

Stat::Stat(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, const char * filename, string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, string armor_type, int prod_time)
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

// --- METHODES ---

// --- GET ---

string Stat::get_name()
{
	return _name;
}

int Stat::get_hp()
{
	return _hp;
}

int Stat::get_hp_max()
{
	return _hp_max;
}

int Stat::get_hp_regen()
{
	return _hp_regen;
}

int Stat::get_power()
{
	return _power;
}

int Stat::get_power_max()
{
	return _power_max;
}

int Stat::get_power_regen()
{
	return _power_regen;
}

int Stat::get_armor()
{
	return _armor;
}

string Stat::get_type_armor()
{
	return _type_armor;
}

int Stat::get_prod_time()
{
	return _prod_time;
}


// --- SET ---

void Stat::set_name(string name)
{
	_name = name;
}

void Stat::set_hp(int hp)
{
	_hp = hp;
}

void Stat::set_hp_max(int hp_max)
{
	_hp_max = hp_max;
}

void Stat::set_hp_regen(int hp_regen)
{
	_hp_regen = hp_regen;
}

void Stat::set_power(int power)
{
	_power = power;
}

void Stat::set_power_max(int power_max)
{
	_power_max = power_max;
}

void Stat::set_power_regen(int power_regen)
{
	_power_regen = power_regen;
}

void Stat::set_armor(int armor)
{
	_armor = armor;
}

void Stat::set_armor_type(string type_armor)
{
	_type_armor = type_armor;
}

void Stat::set_prod_time(int prod_time)
{
	_prod_time = prod_time;
}
