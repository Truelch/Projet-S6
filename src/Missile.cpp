#include "Missile.h"

#include <math.h>

#define PI 3.14159265

Missile::Missile(): Displayable() {
	//
}

Missile::Missile(float x, float y, float rotation, float x_dest, float y_dest, float move_speed, const char * filename, Game * game, Layer * layer, float range_max, int damage,
				Player * player): Displayable(x, y, rotation, filename, game, layer)
{
	/*
	set_x_dest(x_dest);
	set_y_dest(y_dest);
	set_x_origin(x);
	set_y_origin(y);
	*/
	set_destination(x_dest,y_dest);
	set_origin(x,y); //Lorsque le missile est instancé, son origine vaut sa position
	set_range_max(range_max);
	set_damage(damage);
	//
	set_player(player);
}


// --- GET ---

CCPoint Missile::get_origin()
{
	return _origin;
}

CCPoint Missile::get_destination()
{
	return _destination;
}

float Missile::get_move_speed()
{
	return _move_speed;
}

float Missile::get_range_max()
{
	return _range_max;
}

int Missile::get_damage()
{
	return _damage;
}

Player * Missile::get_player()
{
	return _player;
}

// --- SET ---

void Missile::set_origin(float x_origin, float y_origin)
{
	_origin.x = x_origin;
	_origin.y = y_origin;
}

void Missile::set_position(float x_pos, float y_pos)
{
	_position.x = x_pos;
	_position.y = y_pos;
}

void Missile::set_destination(float x_dest, float y_dest)
{
	_destination.x = x_dest;
	_destination.y = y_dest;
}

void Missile::set_move_speed(float move_speed)
{
	_move_speed = move_speed;
}

void Missile::set_range_max(float range_max)
{
	_range_max = range_max;
}

void Missile::set_damage(int damage)
{
	_damage = damage;
}

void Missile::set_player(Player * player)
{
	_player = player;
}

// --- METHODES ---

void Missile::move(float dt)
{
	//Coeff unité de temps
	//float coeff = 50;
	//dt = 1/50 en temps normal
	//Définition du vecteur unitaire de déplacement : contient 2 valeurs => CCPoint
	float delta_x = _destination.x - getSprite()->getPositionX();
	float delta_y = _destination.y - getSprite()->getPositionY();
	
	float hyp     = sqrt(delta_x*delta_x + delta_y*delta_y);
	
	float vect_x  = delta_x / hyp;
	float vect_y  = delta_y / hyp;
	
	
	if(delta_x != 0)
	{
		float angle;
		if (delta_x < 0)  angle = -1.* atan(delta_y/delta_x) * (180/PI) + 90;
		else angle = -1.* atan(delta_y/delta_x) * (180/PI) + 270;
		//float angle = asin(delta_y/hyp) * (180/PI);
		getSprite()->setRotation(angle); //Il faut appliquer la rotation au Sprite, qui est un attribut de Displayable
	}
	
	//Vecteur unitaire
	//vector        = CCPoint(vect_x, vect_y);
	//L'unité se déplace d'un vecteur égal au vecteur unitaire * vitesse
	//speed_vector  = CCPoint(_move_speed * vect_x, _move_speed * _vect_y);

	//On déplace le projectile
	_position.x += vect_x; //(dt/coeff);
	_position.y += vect_y; //(dt/coeff);
	//Si la distance entre la position originale et la position actuelle du projectile est supérieure à la portée max
		
	//Après le déplacement, vérifier si le projectile n'est pas rentré dans une unité ennemie
	check_collision();
}

void Missile::check_range()
{
	/*
	int i = 0;
	float distance;
	float delta_x, delta_y;	
	*/
}

void Missile::check_collision()
{
	int i = 0;
	float distance;
	float delta_x, delta_y;
	//Pour accéder aux container d'unités !	
	for(i = 0 ; i < _player->get_scene()->get_display_layer()->get_unit_layer()->get_number_unit() ; i++) //Ici
	{
		//_player->get_scene()->get_display_layer()->get_unit_layer()->get_unit(i);
		delta_x = _player->get_scene()->get_display_layer()->get_unit_layer()->get_unit(i)->getSprite()->getPositionX() - getSprite()->getPositionX(); //Ici
		delta_y = _player->get_scene()->get_display_layer()->get_unit_layer()->get_unit(i)->getSprite()->getPositionY() - getSprite()->getPositionY(); //Ici
	
		distance = sqrt(delta_x*delta_x + delta_y*delta_y);
		
		if(distance >= _range_max)
		{
			deal_dmg(_player->get_scene()->get_display_layer()->get_unit_layer()->get_unit(i)); //L'unité i se prend le projectile ! Et ici
		}
	}
}

void Missile::deal_dmg(Unit * unit)
{
	unit->get_stat()->set_hp(unit->get_stat()->get_hp()-_damage);
	//Détruire le projectile et vérifier si l'unité a encore des pv !
}
