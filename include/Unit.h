#ifndef UNIT_H
#define UNIT_H

#include "cocos2d.h"

#include <string>

#include "Moveable.h"

class Player;
class Stat;

class Unit : public Moveable
{
	private:
		Player * _player;
		Stat * _stat;

	public:
		Unit();
		Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float groundFixture, float density, const char * filename, Game * game, Layer * layer, std::string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time, Player * owner);
		virtual ~Unit();
		
		// --- METHODES ---
		virtual void on_physics_displayable_contact(PhysicsDisplayable * physicsDisplayableA, PhysicsDisplayable * physicsDisplayableB);
	
		// --- GET ---
		Stat * get_stat();
		Player * getPlayer() { return _player; }

		// --- SET ---
		void setPlayer(Player * player) { _player = player; }

};

#endif
