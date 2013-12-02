#include "Turret.h"
//#include <math.h>
//=> pour les sqrt
//#include <iostream>

//#define PI 3.14159265

//using namespace std;

#include "Unit.h"
#include "Player.h"

Turret::Turret(): Displayable() {
	//
}

Turret::Turret(float x, float y, float rotation, const char * filename, Scene * scene, Layer * layer, 
				float x_relative, float y_relative, float missile_speed, int damage, float cooldown, float range_max, Unit * unit): Displayable(x,y,rotation,filename,scene,layer), _unit(unit)
{
	set_relative_position(x_relative,y_relative);
	set_missile_speed(missile_speed);
	set_damage(damage);
	set_cooldown(cooldown);
	set_range_max(range_max);
}

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

float Turret::get_range_max()
{
	return _range_max;
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

void Turret::set_range_max(float range_max)
{
	_range_max = range_max;
}

// --- METHODES ---

void Turret::check_attack()
{
	/*
	int i = 0;
	float distance = _range_max + 10.0; //hors de portée => valeur infinie
	float delta_x, delta_y;
	//Pour accéder aux container d'unités !	
	for(i = 0 ; i < _unit->getPlayer()->get_scene()->get_display_layer()->get_unit_layer()->get_number_unit() ; i++) //Ici
	{
		delta_x = _unit->getPlayer()->get_scene()->get_display_layer()->get_unit_layer()->get_unit(i)->getSprite()->getPositionX() - getSprite()->getPositionX(); //Ici
		delta_y = _unit->getPlayer()->get_scene()->get_display_layer()->get_unit_layer()->get_unit(i)->getSprite()->getPositionY() - getSprite()->getPositionY(); //Ici
	
		distance = sqrt(delta_x*delta_x + delta_y*delta_y);
		
		if(distance >= _range_max)
		{
			deal_dmg(_unit->getPlayer()->get_scene()->get_display_layer()->get_unit_layer()->get_unit(i)); //L'unité i se prend le projectile ! Et ici
		}
	}
	*/
}

