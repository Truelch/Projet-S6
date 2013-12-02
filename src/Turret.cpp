#include "Turret.h"
//#include <math.h>
//=> pour les sqrt
//#include <iostream>

//#define PI 3.14159265

//using namespace std;

Turret::Turret(): Displayable() {
	//
}

Turret::Turret(float x, float y, float rotation, const char * filename, Game * game, Layer * layer , float x_relative, float y_relative, float missile_speed, int damage, float cooldown): Displayable(x,y,rotation,filename,game,layer)
{
	set_relative_position(x_relative,y_relative);
	set_missile_speed(missile_speed);
	set_damage(damage);
	set_cooldown(cooldown);
}

// --- METHODES ---

// --- GET ---

CCPoint Turret::get_relative_position()
{
	return _relative_position;
}

float Turret::get_missile_speed()
{
	return _missile_speed;
}

int Turret::get_damage()
{
	return _damage;
}

float Turret::get_cooldown()
{
	return _cooldown;
}


// --- SET ---

void Turret::set_relative_position(float x_relative,float y_relative)
{
	_relative_position.x = x_relative;
	_relative_position.y = y_relative;
}

void Turret::set_missile_speed(float missile_speed)
{
	_missile_speed = missile_speed;
}

void Turret::set_damage(int damage)
{
	_damage = damage;
}

void Turret::set_cooldown(float cooldown)
{
	_cooldown = cooldown;
}
