#ifndef AISTAT_H
#define AISTAT_H

#include "cocos2d.h"

#include <string>

class Unit;


using namespace std;

class AIStat
{
	public:
		typedef enum {
			s_inactive,
			s_attack,
			s_defense,
			s_scout,
			s_capture,
			s_retreat,
		} State;	
	
	private:		
		// --- ATTRIBUTS ---
		float _scout;      //facteur de l'unité pour sa capacité à scouter
		float _attack;     //facteur de l'unité pour sa capacité à attaquer
		float _defense;    //facteur de l'unité pour sa capacité à défendre
		float _capture;    //facteur de l'unité pour sa capacité à 
		int   _front_rank; //ordre dans lequel l'unité sera rangée en formation
		int   _priority;   //priorité d'attaque

		State  _state;
		Unit * _unit;
	
	public:
		AIStat();
		AIStat(float scout, float assault, float defend, float capture, int front_rank, int priority);
	
		// --- GET ---
		float get_scout();
		float get_attack();
		float get_defense();
		float get_capture();
		int   get_front_rank();
		int   get_priority();
		
		State  get_state();
		Unit * get_unit();
		

		// --- SET ---
		void set_scout(float scout);
		void set_attack(float attack);
		void set_defense(float defense);
		void set_capture(float capture);
		void set_front_rank(int front_rank);
		void set_priority(int priority);	
		
		void set_state(State state);	
		//void set_unit(Unit * unit) //Ne devrait pas exister
		
		
		// --- METHODES ---
		void retreat();
		
};

#endif
