#include "Turret.h"
#include <math.h>



//using namespace std;

#include "Unit.h"
#include "Player.h"
#include "Missile.h"
#include "DisplayLayer.h"
#include "UnitLayer.h"
#include "MissileLayer.h"

#include <iostream>

Turret::Turret(): CCSprite() 
{
	//
}

Turret::Turret(float rotation, const char * filename, Game * game, Layer * layer, float x_relative, float y_relative, float missile_speed, const char * missile_filename, int damage, float cooldown, float range_max, Unit * shooter_unit): CCSprite(), _rotation(rotation), _relative_position(CCPoint(x_relative,y_relative)), _missile_speed(missile_speed), _missile_filename(missile_filename), _damage(damage), _cooldown(cooldown),_range_max(range_max)
{
	initWithFile(filename);
	change_unit(shooter_unit,_shooter_unit);
	_relative_position.x+=shooter_unit->getSprite()->getTextureRect().size.height/2.0;
	_relative_position.y+=shooter_unit->getSprite()->getTextureRect().size.width/2.0;
	setPosition(_relative_position);
	
	//set_target_unit(NULL); //Il n'y a pas de cible au début. On met NULL pour éviter les valeurs aléatoires dans le pointeur.
	
	//les _shooter_unit deviennent des get_unit(_shooter_unit) (et pareil pour _targer_unit)
	//Position de la tourelle dans le repère global
	CCPoint turret_position = getPosition().rotateByAngle(CCPoint(0,0),get_unit(_shooter_unit)->getSprite()->getRotation()) + get_unit(_shooter_unit)->getSprite()->getPosition(); 
	//CCPoint turret_position = pointTurret.rotateByAngle(CCPoint(0,0),angleUnit)+pointUnit;
	
	//Algo pour orienter la tourelle comme il faut
	if (get_unit(_target_unit))
	{
		float delta_x    = get_unit(_target_unit)->getSprite()->getPositionX() - turret_position.x; //Différence d'abscisse entre l'unité et la tourelle
		float delta_y    = get_unit(_target_unit)->getSprite()->getPositionY() - turret_position.y; //turret_position étant la position de la tourelle en coordonnées cocos2dx
		float distance   = get_unit(_target_unit)->getSprite()->getPosition().getDistance(getPosition()); //Distance entre l'unité et la tourelle
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

float Turret::get_damage()
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

/*Unit * Turret::get_shooter_unit()
{
	return _shooter_unit;
}*/

/*Unit * Turret::get_target_unit()
{
	return _target_unit;
}*/

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

void Turret::set_damage(float damage)
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

/*void Turret::set_shooter_unit(Unit * shooter_unit)
{
	_shooter_unit = shooter_unit;
}*/

/*void Turret::set_target_unit(Unit * target_unit)
{
	_target_unit = target_unit;
}*/

// --- METHODES ---

void Turret::check_attack()
{
	int i = 0;
	float distance/* = 0*/;
	float min_distance = _range_max +10.0; //=> infini
	int index = -1; //Pas d'index => pas de cible
	CCPoint turret_position = getPosition().rotateByAngle(CCPoint(0,0),get_unit(_shooter_unit)->getSprite()->getRotation()) + get_unit(_shooter_unit)->getSprite()->getPosition();

	if(!get_unit(_target_unit) /*|| (distance > _range_max && get_unit(_shooter_unit)->get_ai_stat()->get_hold_position()==True)*/)
	{			
		for(i = 0 ; i < get_unit(_shooter_unit)->getPlayer()->get_game()->get_display_layer()->get_unit_layer()->get_number_unit() ; i++)
		{
			if(get_unit(_shooter_unit)->getPlayer()->get_game()->get_display_layer()->get_unit_layer()->get_unit(i)->getPlayer() != get_unit(_shooter_unit)->getPlayer()) //Propriétaire de l'unité vérifiée != propriétaire du missile
			{
				distance = turret_position.getDistance(get_unit(_shooter_unit)->getPlayer()->get_game()->get_display_layer()->get_unit_layer()->get_unit(i)->getSprite()->getPosition());	
				if (distance <= _range_max && distance < min_distance)
				{
					min_distance = distance;
					index = i;
				}
				if(index!=-1)
				{
					change_unit(get_unit(_shooter_unit)->getPlayer()->get_game()->get_display_layer()->get_unit_layer()->get_unit(index),_target_unit);
				}
			}
		}
	}
	
	if(get_unit(_target_unit)) //Il y a une cible
	{
		rotate_to_target();
		float distance = turret_position.getDistance(get_unit(_target_unit)->getSprite()->getPosition());
		
		if(distance <= _range_max) //A portée
		{
			fire();
		}
		
		else if (distance > _range_max) //Hors de portée : il n'y a plus de cible et on vérifie si y en a à portée
		{
			remove_unit(_target_unit); //On vide le pointeur de cible	
		}
		
		else
		{
			//std::cout << "check_attack3" << std::endl;
			//std::cout << "WTF (Turret.cpp)" << std::endl;
		}
	}	

}

void Turret::fire()
{
	//std::cout << "fire()" << endl;
	if(_current_cooldown >= _cooldown)
	{
		//std::cout << "PAN !!!" << endl;
		_current_cooldown = 0;
		//Instancier un projectile
		float x          = get_unit(_shooter_unit)->getSprite()->getPositionX() + _relative_position.x - get_unit(_shooter_unit)->getSprite()->getTextureRect().size.height/2.0; //Position de l'unité décallée de la position relative de la tourelle
		float y          = get_unit(_shooter_unit)->getSprite()->getPositionY() + _relative_position.y - get_unit(_shooter_unit)->getSprite()->getTextureRect().size.width/2.0;
		float rotation   = get_unit(_shooter_unit)->getSprite()->getRotation();
		float x_dest     = get_unit(_target_unit)->getSprite()->getPositionX();
		float y_dest     = get_unit(_target_unit)->getSprite()->getPositionY();
		float move_speed = _missile_speed;
		const char * filename  = _missile_filename;
		Game * game      = get_unit(_shooter_unit)->getPlayer()->get_game();
		Layer * layer    = get_unit(_shooter_unit)->getPlayer()->get_game()->get_display_layer()->get_missile_layer();
		float range_max  = _range_max;
		float damage       = _damage;
		Player * player  = get_unit(_shooter_unit)->getPlayer();
		get_unit(_shooter_unit)->getPlayer()->get_game()->get_display_layer()->get_missile_layer()->add_missile(x, y, rotation, x_dest, y_dest, move_speed, filename, game, layer, range_max, damage, player,get_unit(_shooter_unit));
		//Missile(x, y, rotation, x_dest, y_dest, move_speed, filename, game, layer, range_max, damage, player);
	}
}


void Turret::update(float dt) {
	_current_cooldown+=dt;
	check_attack();
}

void Turret::remove_unit(Container<Unit>& unit_list)
{
	if(unit_list.get_number_t()!=0) unit_list.remove_t(0);
}

void Turret::change_unit(Unit * unit, Container<Unit>& unit_list) {
	if(unit_list.get_number_t()!=0) unit_list.remove_t(0);
	unit_list.add_t(unit);
}

void Turret::rotate_to_target()
{
	if(get_unit(_target_unit)) //get_unit(_target_unit) <=> get_number_unit()==1 : Condition normalement vérifiée, mais ne sait jamais ...
	{
		CCPoint turret_position = getPosition().rotateByAngle(CCPoint(0,0),get_unit(_shooter_unit)->getSprite()->getRotation()) + get_unit(_shooter_unit)->getSprite()->getPosition();
		float distance = turret_position.getDistance(get_unit(_target_unit)->getSprite()->getPosition());
		float delta_x  = - (get_unit(_target_unit)->getSprite()->getPositionX() - turret_position.x)/distance;
		float delta_y  = - (get_unit(_target_unit)->getSprite()->getPositionY() - turret_position.y)/distance;
		if(delta_x != 0) //Pour éviter la division par zéro !
		{
			float angle;
			
			if (delta_x < 0)  angle = -1.* atan(delta_y/delta_x) * (180/M_PI) - 90;
			else angle = -1.* atan(delta_y/delta_x) * (180/M_PI) /*- 180*/+90;  //angle =0;
			/*
			if(get_unit(_target_unit)->getPlayer()->get_name()=="joueur2")
			{
				std::cout << "Angle (avant modif) : " << angle << std::endl;
				std::cout << "Angle (unité) : " << get_unit(_shooter_unit)->getSprite()->getRotation() << std::endl;
			}			
			*/
			angle += get_unit(_shooter_unit)->getSprite()->getRotation(); //Retirer l'angle de l'unité
			setRotation(angle); //Il faut appliquer la rotation au Sprite, qui est un attribut de Displayable
			
			
			/*if (delta_x < 0)  angle = -1.* atan(delta_y/delta_x) + M_PI;
			else angle = -1.* atan(delta_y/delta_x) + 3*M_PI;
			angle -= get_unit(_shooter_unit)->getSprite()->getRotation(); //Retirer l'angle de l'unité
			setRotation(angle); //Il faut appliquer la rotation au Sprite, qui est un attribut de Displayable*/
			/*
			angle = acos(delta_x) + M_PI/2;
			if(delta_y < 0)
			{
				if(delta_x > 0) 
				{
					angle = M_PI - angle;
				}
				else
				{
					angle = 3*M_PI - angle;
				}
				angle*=180/M_PI;
				if(get_unit(_target_unit)->getPlayer()->get_name()=="joueur2")
				{
					std::cout << "Angle (avant modif) : " << angle << std::endl;
					std::cout << "Angle (unité) : " << get_unit(_shooter_unit)->getSprite()->getRotation() << std::endl;
				}
				
				angle -= get_unit(_shooter_unit)->getSprite()->getRotation();
				if(get_unit(_target_unit)->getPlayer()->get_name()=="joueur2") std::cout << "Angle total : " << angle << std::endl;
				setRotation(angle);
			}*/
		}		
	}
}
