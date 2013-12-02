#ifndef MISSILE_H
#define MISSILE_H

#include "cocos2d.h"

#include <string>

#include "Moveable.h"
#include "Player.h"

using namespace std;

class Missile : public Displayable
{
	public:
		Missile();
		Missile(float x, float y, float rotation, float x_dest, float y_dest, float move_speed, const char * filename, Game * game, Layer * layer, float range_max, int damage, Player * player);
		
		// --- METHODES ---

	
		// --- GET ---
		CCPoint get_origin();
		CCPoint get_position();
		CCPoint get_destination();
		
		float   get_move_speed();
		float   get_range_max();
		int     get_damage();
		//
		Player * get_player();

		// --- SET ---
		void set_origin(float x_origin, float y_origin);  //Il ne faudrait pas l'utiliser
		void set_position(float x_pos, float y_pos); 
		void set_destination(float x_dest, float y_dest); //Il ne faudrait pas l'utiliser
		
		void set_move_speed(float move_speed);
		void set_range_max(float range_max);
		void set_damage(int damage);
		//
		void set_player(Player * player);
		
		// --- METHODES ---
		void move(float dt);
		void check_collision();
		void deal_dmg(Unit * unit);
		void check_range();
		
	private:
		// --- ATTRIBUTS ---
		CCPoint _origin;
		CCPoint _position;
		CCPoint _destination;
		float   _move_speed;
		float   _range_max;
		int     _damage;
		//
		Player * _player;
		
		
};

#endif
