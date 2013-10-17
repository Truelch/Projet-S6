#ifndef UNIT_H
#define UNIT_H

#include "cocos2d.h"

#include <string>

#include "Moveable.h"

//using namespace cocos2d;
using namespace std;

class Unit : public Moveable
{
	public:
		Unit();
		Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, const char * filename, string n, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, string armor_type, int prod_time);
		
		// --- Attributs ---
		string _name;
		int _hp;
		int _hp_max;
		int _hp_regen;
		int _power;
		int _power_max;
		int _power_regen;
		int _armor;
		string _type_armor;
		int _prod_time;
	
		// --- GET ---
		string get_name();
		int get_hp();
		int get_hp_max();
		int get_hp_regen();
		int get_power();
		int get_power_max();
		int get_power_regen();
		int get_armor();
		string get_type_armor();
		int get_prod_time();

		// --- SET ---
		void set_name(string name);
		void set_hp(int hp);
		void set_hp_max(int hp_max);
		void set_hp_regen(int hp_regen);
		void set_power(int power);
		void set_power_max(int power_max);
		void set_power_regen(int power_regen);
		void set_armor(int armor);
		void set_armor_type(string armor_type);
		void set_prod_time(int prod_time);

		
};

#endif
