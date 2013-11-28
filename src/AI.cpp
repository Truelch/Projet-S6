#include "AI.h"

AI::AI(): EventReceiver()
{
	//
	std::cout << "Constructeur d'AI" << std::endl;
}

AI::AI(Scene * scene, Difficulty difficulty): EventReceiver(scene->getEventHandler()), _scene(scene)
{
	//
	std::cout << "Constructeur d'AI" << std::endl;
	if(difficulty==d_easy)
	{
		set_play_style(ps_defensive);
		set_coeff_ressource(0.5);
		set_dt_time(2.0);
		set_omniscience(false);
	}

	else if(difficulty==d_medium)
	{
		set_play_style(ps_balanced);
		set_coeff_ressource(1.0);
		set_dt_time(0.5);
		set_omniscience(false);
	}
	
	else if(difficulty==d_hard)
	{
		//Cette AI cheat !
		set_play_style(ps_offensive);
		set_coeff_ressource(2.0);
		set_dt_time(0.0);
		set_omniscience(true);
	}	
}

AI::AI(Scene * scene, AI::PlayStyle play_style, float coeff_ressource, float dt_time, bool omniscience): EventReceiver(scene->getEventHandler()), _scene(scene)
{
	std::cout << "Constructeur d'AI" << std::endl;
	set_play_style(play_style);
	set_coeff_ressource(coeff_ressource);
	set_dt_time(dt_time);
	set_omniscience(omniscience);
}


// --- GET ---

AI::Difficulty AI::get_difficulty()
{
	return _difficulty;
}

AI::PlayStyle AI::get_play_style()
{
	return _play_style;
}

float AI::get_coeff_ressource()
{
	return _coeff_ressource;
}

float AI::get_dt_time()
{
	return _dt_time;
}

bool AI::get_omniscience()
{
	return _omniscience;
}

float AI::get_percent_life_min()
{
	return _percent_life_min;
}

// --- SET ---

void AI::set_difficulty(AI::Difficulty difficulty)
{
	_difficulty = difficulty;
}

void AI::set_play_style(AI::PlayStyle play_style)
{
	_play_style = play_style;
}


void AI::set_coeff_ressource(float coeff_ressource)
{
	_coeff_ressource = coeff_ressource;
	
}

void AI::set_dt_time(float dt_time)
{
	_dt_time = dt_time;
	//set_difficulty = custom; //Comme on modifie des paramètres de l'AI pendant la partie, elle est customisée. Faire attention à ne pas l'utiliser quand elle est crée, sinon
}

void AI::set_omniscience(bool omniscience)
{
	_omniscience = omniscience;
}

void AI::set_percent_life_min(float percent_life_min)
{
	_percent_life_min = percent_life_min;
}

// --- METHODES ---
void AI::AI_monitor()
{
	int i;
	float percent_of_life;
	//Boucle for traversant les unités du joueur
	for(i=0;i<player->get_number_unit();i++)
	{
		//Vérification si l'unité est en état de se battre
		percent_of_life = i->get_pv()/(float)i->get_pv_max();
		if (percent_of_life > _percent_life_min) //Unité en état de combattre
		{
			//Calcul de scout_value, def_value, att_value et capture_value (ce dernier vérifiant la distance de l'unité à un élément capurable ?
			//scout_value = i->get
		}
		
		else //pv trop faibles
		{
			//retreat(i); //set_destination(x_QG,y_QG); + impossible de lui redonner d'autres ordres
		}
	}
	
}

float need_scout()
{
	float need_scout;
	
	//
	
	return need_scout;
}

