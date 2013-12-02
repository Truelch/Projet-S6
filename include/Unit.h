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

		virtual void updateCoordonates();

	public:
		Unit();
		Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float groundFixture, float density, const char * filename, Game * game, Layer * layer, std::string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time, Player * owner);
		virtual ~Unit();
		
		// --- METHODES ---
		virtual void on_displayable_contact(Displayable * displayableA, Displayable * displayableB);
	
		// --- GET ---
		Stat * get_stat();
		Player * getPlayer() { return _player; }
		virtual Displayable::DisplayableType getType() { return Displayable::unitType; }

		// --- SET ---
		void setPlayer(Player * player) { _player = player; }

};

#endif
