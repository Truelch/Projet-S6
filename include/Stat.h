#ifndef STAT_H
#define STAT_H

#include "cocos2d.h"

#include <string>


using namespace std;

class Stat
{
	public:
		Stat();
		Stat(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, const char * filename, string name, float hp, float hp_max, float hp_regen, float power, float power_max, float power_regen, float armor, string armor_type, float prod_time, float sight);
		
		// --- METHODES ---

	
		// --- GET ---
		string get_name();
		float get_hp();
		float get_hp_max();
		float get_hp_regen();
		float get_power();
		float get_power_max();
		float get_power_regen();
		float get_armor();
		string get_type_armor();
		float get_prod_time();
		float get_sight();

		// --- SET ---
		void set_name(string name);
		void set_hp(float hp);
		void set_hp_max(float hp_max);
		void set_hp_regen(float hp_regen);
		void set_power(float power);
		void set_power_max(float power_max);
		void set_power_regen(float power_regen);
		void set_armor(float armor);
		void set_armor_type(string armor_type);
		void set_prod_time(float prod_time);
		void set_sight(float sight);
	
	private:		
		// --- ATTRIBUTS ---
		string   _name;
		float    _hp;
		float    _hp_max;
		float    _hp_regen;
		float    _power;
		float    _power_max;
		float    _power_regen;
		float    _armor;
		string   _type_armor;
		float    _prod_time;
		float    _sight;
		
};

#endif
