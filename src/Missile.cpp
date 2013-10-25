#include "Missile.h"


Missile::Missile(): Moveable() {
	//
}

Missile::Missile(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, const char * filename,
			float x_origin, float y_origin, float range_max, int damage): Moveable(x, y, x_dest, y_dest, rotation, move_speed, filename)
{
	set_x_origin(x_origin);
	set_y_origin(y_origin);
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

void Missile::set_range_max(float range_max)
{
	_range_max = range_max;
}

void Missile::set_damage(int damage)
{
	_damage = damage;
}
