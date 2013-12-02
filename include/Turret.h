#ifndef TURRET_H
#define TURRET_H

#include "cocos2d.h"
#include "Displayable.h"

using namespace cocos2d;

class Turret : public Displayable
{
	public:
		Turret();
		Turret(float x, float y, float rotation, const char * filename, Game * game, Layer * layer, float x_relative, float y_relative, float missile_speed, int damage, float cooldown);
		
		// --- METHODES ---
		//void fire(); //-> Lance un projectile
		
		// --- GET ---
		CCPoint get_relative_position();
		float get_missile_speed();
		int get_damage();
		float get_cooldown();
		
		// --- SET ---
		void set_relative_position(float x_relative, float y_relative);
		void set_missile_speed(float missile_speed);
		void set_damage(int damage);
		void set_cooldown(float cooldown);
	
	private:
		// --- Attributs ---
		CCPoint _relative_position;
		float   _missile_speed;
		int     _damage;
		float   _cooldown;
};

#endif
