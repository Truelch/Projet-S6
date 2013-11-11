#ifndef UNIT_H
#define UNIT_H

#include "cocos2d.h"

#include <string>

#include "Moveable.h"
#include "Stat.h"

using namespace std;

class Unit : public Moveable
{
	public:
		Unit();
		Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, const char * filename, string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, string armor_type, int prod_time);
		
		// --- ATTRIBUTS ---
		Stat * _stat;
		
		// --- METHODES ---

	
		// --- GET ---
		Stat * get_stat();

		// --- SET ---
		
};

#endif
