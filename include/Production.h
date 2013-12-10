#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "Unit.h" //class Unit; ?

//Cette classe sert à associer une unité et son temps de production. Elle sera dans un container de Building, qui sera traversé via l'update pour l'algo de production 

class Production
{
	public:
		Production(Unit * unit, float prod_time);
		//virtual ~Production(); //Sûrement nécessaire avec le pointeur d'Unité
		
		// --- GET ---
		Unit * get_unit();
		float  get_prod_time();
		float  get_current_prod_time();
		
		// --- SET ---
		void set_unit(Unit * unit);
		void set_prod_time(float prod_time);
		void set_current_prod_time(float current_prod_time);
		
		// --- METHODES ---
		void update(float dt);
		
	private:
		Unit * _unit;
		float  _prod_time;
		float  _current_prod_time;
};

#endif
