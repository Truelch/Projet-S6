#ifndef MISSILE_H
#define MISSILE_H

#include "cocos2d.h"

#include <string>

#include "Moveable.h"

using namespace std;

class Missile : public Displayable
{
	public:
		Missile();
		Missile(float x, float y, float rotation, float x_dest, float y_dest, float move_speed, const char * filename, Game * game, Layer * layer, float range_max, int damage);
		
		// --- METHODES ---

	
		// --- GET ---
		float get_x_origin();
		float get_y_origin();
		float get_x_dest();
		float get_y_dest();
		float get_range_max();
		int   get_damage();

		// --- SET ---
		void set_x_origin(float x_origin); //Il ne faudrait pas l'utiliser
		void set_y_origin(float y_origin); //Il ne faudrait pas l'utiliser
		void set_x_dest(float x_dest); //Il ne faudrait pas l'utiliser
		void set_y_dest(float y_dest); //Il ne faudrait pas l'utiliser
		void set_range_max(float range_max);
		void set_damage(int damage);

	private:
		// --- ATTRIBUTS ---
		float _x_origin;
		float _y_origin;
		float _x_dest;
		float _y_dest;
		float _range_max;
		int   _damage;
		
		
};

#endif
