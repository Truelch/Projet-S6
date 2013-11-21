#include "Missile.h"


Missile::Missile(): Displayable() {
	//
}

Missile::Missile(float x, float y, float rotation, float x_dest, float y_dest, float move_speed, const char * filename, Scene * scene, float range_max, int damage): Displayable(x, y, rotation, filename, scene)
{
	set_x_dest(x_dest);
	set_y_dest(y_dest);
	set_x_origin(x);
	set_y_origin(y);
	set_range_max(range_max);
	set_damage(damage);
}

// --- METHODES ---
/*
void Missile::deal_dmg(Unite* unit)
{
	unit->set_hp(unit->get_hp()-_damage);
}

*/

// --- GET ---

float Missile::get_x_origin()
{
	return _x_origin;
}

float Missile::get_y_origin()
{
	return _y_origin;
}

float Missile::get_x_dest()
{
	return _x_dest;
}

float Missile::get_y_dest()
{
	return _y_dest;
}

float Missile::get_range_max()
{
	return _range_max;
}

int Missile::get_damage()
{
	return _damage;
}

// --- SET ---

void Missile::set_x_origin(float x_origin)
{
	_x_origin = x_origin;
}

void Missile::set_y_origin(float y_origin)
{
	_y_origin = y_origin;
}

void Missile::set_x_dest(float x_dest)
{
	_x_dest = x_dest;
}

void Missile::set_y_dest(float y_dest)
{
	_y_dest = y_dest;
}

void Missile::set_range_max(float range_max)
{
	_range_max = range_max;
}

void Missile::set_damage(int damage)
{
	_damage = damage;
}
