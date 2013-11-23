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
	
	if(difficulty==easy)
	{
		set_coeff_ressource(0.5);
		set_dt_time(2.0);
	}

	else if(difficulty==medium)
	{
		set_coeff_ressource(1.0);
		set_dt_time(0.5);
	}
	
	else if(difficulty==hard)
	{
		set_coeff_ressource(2.0);
		set_dt_time(0.0);
	}	
}


// --- GET ---

float AI::get_coeff_ressource()
{
	return _coeff_ressource;
}

float AI::get_dt_time()
{
	return _dt_time;
}

AI::Difficulty AI::get_difficulty()
{
	return _difficulty;
}

// --- SET ---

void AI::set_coeff_ressource(float coeff_ressource)
{
	_coeff_ressource = coeff_ressource;
	
}

void AI::set_dt_time(float dt_time)
{
	_dt_time = dt_time;
	//set_difficulty = custom; //Comme on modifie des paramètres de l'AI pendant la partie, elle est customisée. Faire attention à ne pas l'utiliser quand elle est crée, sinon
}

void AI::set_difficulty(AI::Difficulty difficulty)
{
	_difficulty = difficulty;
}

// --- METHODES ---
