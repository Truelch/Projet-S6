#include "AI.h"

AI::AI() 
{
	//
	std::cout << "Constructeur d'AI" << std::endl;
}

AI::AI(Difficulty difficulty)
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

AI::AI(AI::PlayStyle play_style, float coeff_ressource, float dt_time, bool omniscience)
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


// --- METHODES ---
