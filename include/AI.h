#ifndef AI_H
#define AI_H

#include <iostream>
#include <string>

#include "EventReceiver.h"

using namespace std;

class AI : public EventReceiver {
	public:
		typedef enum {
			easy,
			medium,
			hard,
			custom,
		} Difficulty;	
		
	private:
		// --- ATTRIBUTS ---
		float      _coeff_ressource; //coefficient de gain de ressources. Ex : facile : 0.5 ; normal : 1 ; difficile : 1.5
		float      _dt_time;         //temps min entre chaque action. Ex : facile : 2 sec ; normal : 0.5 ; difficile : 0	
		Difficulty _difficulty;	

	public:
		AI();                    //constructeur par défaut
		AI(Difficulty difficulty);   //remplit tous les paramètres en fonction du string d'entrée
		//AI(float coeff_ressource, float dt_time); //version + souple permettant de tout remplir à la main dans le cadre d'une AI paramétrable en détails
								 //ou alors appeler le constructeur défaut et remplir avec des set ? Non, en fait c'est une mauvaise idée.
			
		// --- METHODES ---
		
		// --- GET ---
		float      get_coeff_ressource();
		float      get_dt_time();
		Difficulty get_difficulty();
		
		// --- SET ---
		void set_coeff_ressource(float coeff_ressource);
		void set_dt_time(float dt_time);
		void set_difficulty(Difficulty difficulty);	

};

#endif
