#ifndef UNIT_H
#define UNIT_H

#include "cocos2d.h"

#include <string>
#include <vector>

#include "Moveable.h"
#include "AIStat.h"
#include "Stat.h"
#include "Turret.h"


class Player;

class Unit : public Moveable
{
	private:
		Player * _player;
		Stat *   _stat;
		AIStat * _ai_stat;
		Unit *   _target;
		vector<Turret *> turret_list; //Non partagabilité => pas de pointeurs mais attribut "direct"

		virtual void updateCoordonates();

	public:
		Unit();
		Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float groundFixture, float density, const char * filename,
			Game * game, Layer * layer, string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time, Player * owner);
		virtual ~Unit();

		virtual void on_displayable_contact(Displayable * displayableA, Displayable * displayableB);
	
		// --- GET ---
		Player * getPlayer() { return _player; }
		Stat *   get_stat();
		AIStat * get_ai_stat();

		virtual Displayable::DisplayableType getType() { return Displayable::unitType; }

		// --- SET ---
		void setPlayer(Player * player) { _player = player; }

		// --- METHODES ---
		void check_attack(); //Vérifie pour chaque tourelle (traverse le container de turret et appelle la méthode check_attack de chaque turret)
};

#endif
