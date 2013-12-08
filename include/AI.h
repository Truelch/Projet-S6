#ifndef AI_H
#define AI_H

#include <iostream>
#include <string>

#include "EventReceiver.h"
//#include "Scene.h"
//#include "Player.h"

/*
class AIAttackManager;
class AIDefenseManager;
class AIScoutManager;
class AICaptureManager;
class AIRetreatManager;
*/

//
#include "Container.h"

class Unit;
//

class Scene;
class Player;


using namespace std;

class AI : public EventReceiver {
	public:
		typedef enum {
			d_easy,
			d_medium,
			d_hard,
			d_custom,
		} Difficulty;
		
		typedef enum {
			ps_offensive,
			ps_defensive,
			ps_balanced,
			ps_random,
			ps_custom,
		} PlayStyle;
		
	private:
		// --- ATTRIBUTS ---
		Difficulty _difficulty;       //ne sert qu'à l'initialisation de l'AI. Toutes les déicisions et caractéristiques sont dès lors rentrées dans l'instance de l'AI.		

		PlayStyle  _play_style;		
		float      _coeff_ressource;  //coefficient de gain de ressources. Ex : facile : 0.5 ; normal : 1 ; difficile : 1.5
		float      _dt_time;          //temps min entre chaque action. Ex : facile : 2 sec ; normal : 0.5 ; difficile : 0	
		bool       _omniscience;      //true : l'AI sait tout ce qui se passe et ne fait pas de décisions aléatoires (pour le scout et assauts de début de partie par ex)		
		float      _percent_life_min; //pourcentage minimal de la vie pour laquelle l'unité est autorisée à combattre
		
		/*
		AIAttackManager *  _ai_attack_manager;
		AIDefenseManager * _ai_defense_manager;
		AIScoutManager *   _ai_scout_manager;
		AICaptureManager * _ai_capture_manager;
		AIRetreatManager * _ai_retreat_manager;
		*/
		Container<Unit> _inactive_list;
		Container<Unit> _attack_list;
		Container<Unit> _defense_list;
		Container<Unit> _scout_list;
		Container<Unit> _capture_list;
		Container<Unit> _retreat_list;
		
		//
		Scene *    _scene;
		Player *   _player;

	public:
		AI(); //constructeur par défaut
		AI(Scene * scene, Difficulty difficulty); //remplit tous les paramètres en fonction du string d'entrée
		AI(Scene * scene, PlayStyle play_style, float coeff_ressource, float dt_time, bool omniscience); //version + souple permettant de tout remplir à la main dans le cadre d'une AI paramétrable en détails
								 //ou alors appeler le constructeur défaut et remplir avec des set ? Non, en fait c'est une mauvaise idée.		
		
		// --- GET ---
		Difficulty get_difficulty(); //ne devrait pas être trop utile		
		PlayStyle  get_play_style();
		float      get_coeff_ressource();
		float      get_dt_time();
		bool       get_omniscience();
		float      get_percent_life_min();
		
		/*
		AIAttackManager *  get_ai_attack_manager();
		AIDefenseManager * get_ai_defense_manager();
		AIScoutManager *   get_ai_scout_manager();
		AICaptureManager * get_ai_capture_manager();
		AIRetreatManager * get_ai_retreat_manager();		
		*/

		//Il faut qu'on puisse choisir l'attribut sur lequel on travail
		//Container<Unit> list correspond à l'une des listes : _inactive_list, _attack_list, etc.
		
		Unit * get_unit(int index, Container<Unit> * list); //{ return _unit_list.get_t(index); }
		void   remove_unit(Unit *, Container<Unit> * list);
		void   add_unit(Unit * unit, Container<Unit> * list);
		int    get_number_unit(Container<Unit> * list); //{ return _unit_list.get_number_t(); }

		//
		
		Scene *  get_scene();
		Player * get_player(); //Comme pour Unit. Mais ne devrait pas plutôt renvoyer une référence ?
		
		// --- SET ---
		void set_difficulty(Difficulty difficulty);	//ne devrait pas être utilisé. si c'est le cas, ce set devrait setter les autres attributs comme avec le constructeur ayant difficulty en entrée	
		void set_play_style(PlayStyle play_style);		
		void set_coeff_ressource(float coeff_ressource);
		void set_dt_time(float dt_time);
		void set_omniscience(bool omniscience);
		void set_percent_life_min(float percent_life_min);
		
		void set_scene(Scene * scene);
		void set_player(Player * player);
		
		
		// --- METHODES ---
		void ai_monitor();
		void affecting_order();
		void build_order();
		
		float compute_need_attack();
		float compute_need_defense();
		float compute_need_scout();
		float compute_need_capture();		
		
		void attack_management();
		void defense_management();
		void scout_management();
		void capture_management();
};

#endif
