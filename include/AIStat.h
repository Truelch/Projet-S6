#ifndef AISTAT_H
#define AISTAT_H

#include "cocos2d.h"

#include <string>


using namespace std;

class AIStat
{
	public:
		AIStat();
		AIStat(float scout, float assault, float defend, float capture, int front_rank, int priority);
		
		// --- METHODES ---

	
		// --- GET ---
		float get_scout();
		float get_assault();
		float get_defend();
		float get_capture();
		int   get_front_rank();
		int   get_priority();

		// --- SET ---
		void set_scout(float scout);
		void set_assault(float assault);
		void set_defend(float defend);
		void set_capture(float capture);
		void set_front_rank(int front_rank);
		void set_priority(int priority);		
	
	private:		
		// --- ATTRIBUTS ---
		float _scout;      //facteur de l'unité pour sa capacité à scouter
		float _assault;    //facteur de l'unité pour sa capacité à attaquer
		float _defend;     //facteur de l'unité pour sa capacité à défendre
		float _capture;    //facteur de l'unité pour sa capacité à 
		int   _front_rank; //ordre dans lequel l'unité sera rangée en formation
		int   _priority;   //priorité d'attaque
		
};

#endif
