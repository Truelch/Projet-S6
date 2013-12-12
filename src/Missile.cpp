#include "Missile.h"
#include "DisplayLayer.h"

#include <math.h>

#include "Player.h"
#include "UnitLayer.h"
#include "Unit.h"
#include "TileLayer.h"

#define PI 3.14159265

Missile::Missile(): Displayable() 
{
	//
}

Missile::Missile(float x, float y, float rotation, float x_dest, float y_dest, float move_speed, const char * filename, Game * game, Layer * layer, float range_max, int damage,
				Player * player): Displayable(x, y, rotation, filename, game, layer), 
				_origin(CCPoint(x,y)),_destination(CCPoint(x_dest,y_dest)), _move_speed(move_speed), _filename(filename), _range_max(range_max), _damage(damage), _player(player)
{
	//Création du vecteur unitaire de déplacement du Missile
	float delta_x  = _destination.x - getSprite()->getPositionX();
	float delta_y  = _destination.y - getSprite()->getPositionY();	
	float distance = _origin.getDistance(_destination);
	_movement.x    = delta_x/distance;
	_movement.y    = delta_y/distance;
}

Missile::~Missile()
{
	Container<Missile>::on_destroyed(this);
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

void Missile::update(float dt)
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
	
	
	if(delta_x != 0) //Pour éviter la division par zéro !
	{
		float angle;
		if (delta_x < 0)  angle = -1.* atan(delta_y/delta_x) * (180/PI) + 90;
		else angle = -1.* atan(delta_y/delta_x) * (180/PI) + 270;
		//float angle = asin(delta_y/hyp) * (180/PI);
		getSprite()->setRotation(angle); //Il faut appliquer la rotation au Sprite, qui est un attribut de Displayable
	}

	//On déplace le projectile
	getSprite()->setPosition(CCPoint(getSprite()->getPosition().x+vect_x*dt,getSprite()->getPosition().y+vect_y*dt)); //(dt/coeff);

	//Si la distance entre la position originale et la position actuelle du projectile est supérieure à la portée max => fait par check_collision()
		
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
	int i,j,k;
	//float delta_x, delta_y;
	float x = getSprite()->getPositionX(); //Coordonnées actuelles du Missile
	float y = getSprite()->getPositionY(); //
	int tile_x, tile_y; //Coordonnées du Tile sur lequel se trouve le missile (tile_x et pas x_tile pour correspondre à la boucle plus loin)
	_player->get_game()->get_display_layer()->coordonate_cocos2dx_to_tile(x, y, tile_x, tile_y);
	Container<Unit> unit_container;	
	float distance = _origin.getDistance(getSprite()->getPosition()); //Distance entre l'origine et sa position actuelle ; sera réutilisé pour la distance entre le missile et une unité donnée 
	if(distance >= _range_max) //Détruit le projectile s'il est allé trop loin
	{	
		//Destruction
		delete this;
		return; //Et hop on sort car on n'a plus rien à faire !
	}
	else //Sinon on regarde s'il se collisionne avec une unité
	{
		/*
		for(i = 0 ; i < _player->get_game()->get_display_layer()->get_unit_layer()->get_number_unit() ; i++)
		{
			//_player->get_game()->get_display_layer()->get_unit_layer()->get_unit(i);
			delta_x = _player->get_game()->get_display_layer()->get_unit_layer()->get_unit(i)->getSprite()->getPositionX() - getSprite()->getPositionX();
			delta_y = _player->get_game()->get_display_layer()->get_unit_layer()->get_unit(i)->getSprite()->getPositionY() - getSprite()->getPositionY();
		
			distance = sqrt(delta_x*delta_x + delta_y*delta_y); //Distance entre le projectile et l'unité i
			if(distance <= _player->get_game()->get_display_layer()->get_unit_layer()->get_unit(i)->get_hitboxRadius());
			{
				//Explosion !
				deal_dmg(_player->get_game()->get_display_layer()->get_unit_layer()->get_unit(i)); //L'unité i se prend le projectile !
				//Destruction
				delete this;
				return; //Pour être sur qu'il ne continue pas et éviter le segfault !
			}
		}
		*/
		
		//Ce for ne sera effectif que si aucune unité n'a été trouvée => on collisionne avec un décor ?
		/*for()
		{
			
		}*/
		
		//Ce bout de code provient à l'origine de Game => faire les bon getteurs
		for(i=tile_x-1;i<tile_x+2;i++) //Traverse tous les tiles proches
		{
			for(j=tile_y-1;j<tile_y+2;j++) 
			{
				if(j>=0 && j<(int)_player->get_game()->get_display_layer()->get_tile_layer()->get_map_tile_matrix().size() 
				&& i>=0 && i<(int)_player->get_game()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[0].size())
				{
					unit_container = _player->get_game()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[j][i]->get_unit_container();
					for(k=0;k<unit_container.get_number_t();k++) 
					{
						if(unit_container.get_t(k)->getPlayer() != _player) //Propriétaire de l'unité vérifiée != propriétaire du missile
						{
							distance = unit_container.get_t(k)->getSprite()->getPosition().getDistance(getSprite()->getPosition()); //Distance entre l'unité et le missile
							if(distance <= _player->get_game()->get_display_layer()->get_unit_layer()->get_unit(i)->get_hitboxRadius())//Vérification de la distance
							{
								//Explosion !
								deal_dmg(_player->get_game()->get_display_layer()->get_unit_layer()->get_unit(i)); //L'unité i se prend le projectile !
								//Destruction
								delete this;
								break;
							}
						}
					}
				}
			}
		}				
	}
}

void Missile::deal_dmg(Unit * unit)
{
	unit->set_hp(unit->get_hp()-_damage);
	//Détruire le projectile et vérifier si l'unité a encore des pv !
}
