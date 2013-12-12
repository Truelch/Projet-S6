#include "Turret.h"
#include <math.h>

//#include <iostream>

//using namespace std;

#include "Unit.h"
#include "Player.h"
#include "Missile.h"
#include "DisplayLayer.h"
#include "UnitLayer.h"
#include "MissileLayer.h"

Turret::Turret(): CCSprite() 
{
	//
}

Turret::Turret(float rotation, const char * filename, Game * game, Layer * layer, float x_relative, float y_relative, 
				float missile_speed, const char * missile_filename, int damage, float cooldown, float range_max, Unit * shooter_unit): 
				CCSprite(), 
				_rotation(rotation), _relative_position(CCPoint(x_relative,y_relative)), _missile_speed(missile_speed), _missile_filename(missile_filename), _cooldown(cooldown),
				_range_max(range_max), _shooter_unit(shooter_unit)
{
	initWithFile(filename);
	setPosition(_relative_position);
	
	set_target_unit(NULL); //Il n'y a pas de cible au début. On met NULL pour éviter les valeurs aléatoires dans le pointeur.
	
	CCPoint turret_position = getPosition().rotateByAngle(CCPoint(0,0),_shooter_unit->getSprite()->getRotation()) + _shooter_unit->getSprite()->getPosition(); //Position de la tourelle dans le repère global
	//CCPoint turret_position = pointTurret.rotateByAngle(CCPoint(0,0),angleUnit)+pointUnit;
	
	//Algo pour orienter la tourelle comme il faut
	if (_target_unit)
	{
		float delta_x    = _target_unit->getSprite()->getPositionX() - turret_position.x; //Différence d'abscisse entre l'unité et la tourelle
		float delta_y    = _target_unit->getSprite()->getPositionY() - turret_position.y; //turret_position étant la position de la tourelle en coordonnées cocos2dx
		float distance   = _target_unit->getSprite()->getPosition().getDistance(getPosition()); //Distance entre l'unité et la tourelle
		CCPoint vecteur_unitaire = CCPoint(delta_x/distance,delta_y/distance);
		float angle = acos(vecteur_unitaire.x)+M_PI/2;
		if(vecteur_unitaire.y<0) 
		{
			if(vecteur_unitaire.x>0) angle=M_PI-angle;
			else angle=3*M_PI-angle;
		}
		setRotation(angle);
	}
	else //Tourelle droite
	{
		setRotation(0);
	}
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

const char * Turret::get_missile_filename()
{
	return _missile_filename;
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

Unit * Turret::get_shooter_unit()
{
	return _shooter_unit;
}

Unit * Turret::get_target_unit()
{
	return _target_unit;
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

void Turret::set_missile_filename(const char * missile_filename)
{
	_missile_filename = missile_filename;
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

void Turret::set_shooter_unit(Unit * shooter_unit)
{
	_shooter_unit = shooter_unit;
}

void Turret::set_target_unit(Unit * target_unit)
{
	_target_unit = target_unit;
}

// --- METHODES ---

void Turret::check_attack()
{
	int i = 0;
	float distance = _range_max + 10.0; //hors de portée => valeur infinie
	float delta_x, delta_y;
	//Pour accéder aux container d'unités !	
	for(i = 0 ; i < _shooter_unit->getPlayer()->get_game()->get_display_layer()->get_unit_layer()->get_number_unit() ; i++) //Ici
	{
		if(!_target_unit) //Si le pointeur de cible n'est pas nul, on va regarder si on peut le faire tirer sur qqn
		{
			delta_x = _target_unit->getPlayer()->get_game()->get_display_layer()->get_unit_layer()->get_unit(i)->getSprite()->getPositionX() - getPositionX(); //Ici
			delta_y = _target_unit->getPlayer()->get_game()->get_display_layer()->get_unit_layer()->get_unit(i)->getSprite()->getPositionY() - getPositionY(); //Ici
		
			distance = sqrt(delta_x*delta_x + delta_y*delta_y);
			
			if(distance <= _range_max)
			{
				//
				_target_unit = _shooter_unit->getPlayer()->get_game()->get_display_layer()->get_unit_layer()->get_unit(i); //la cible devient
			}
		}
		if(_target_unit) //Il ya une cible
		{
			fire();
		}
	}
}

void Turret::fire()
{
	if(_current_cooldown >= _cooldown)
	{
		_current_cooldown = 0;
		//Instancier un projectile
		float x          = _shooter_unit->getSprite()->getPositionX() + _relative_position.x; //Position de l'unité décallé de la position relative de la tourelle
		float y          = _shooter_unit->getSprite()->getPositionX() + _relative_position.x;
		float rotation   = _shooter_unit->getSprite()->getRotation();
		float x_dest     = _target_unit->getSprite()->getPositionX();
		float y_dest     = _target_unit->getSprite()->getPositionY();
		float move_speed = _missile_speed;
		const char * filename  = _missile_filename;
		Game * game      = _shooter_unit->getPlayer()->get_game();
		Layer * layer    = _shooter_unit->getPlayer()->get_game()->get_display_layer()->get_missile_layer();
		float range_max  = _range_max;
		int damage       = _damage;
		Player * player  = _shooter_unit->getPlayer();
		_shooter_unit->getPlayer()->get_game()->get_display_layer()->get_missile_layer()->add_missile(x, y, rotation, x_dest, y_dest, move_speed, filename, game, layer, range_max, damage, player);
		//Missile(x, y, rotation, x_dest, y_dest, move_speed, filename, game, layer, range_max, damage, player);
	}
}

