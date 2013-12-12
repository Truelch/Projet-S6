#include "Production.h"


Production::Production(Unit * unit, float prod_time): _unit(unit), _prod_time(prod_time), _current_prod_time(0)
{
	//
}

/*Production::~Production() 
{
	delete _unit; //Est-ce bien ce qu'il faut faire ?
}*/
		
				
// --- GET ---

Unit * Production::get_unit()
{
	return _unit;
}

float Production::get_prod_time()
{
	return _prod_time;
}

float Production::get_current_prod_time()
{
	return _current_prod_time;
}
		
// --- SET ---

void Production::set_unit(Unit * unit)
{
	_unit = unit;
}

void Production::set_prod_time(float prod_time)
{
	_prod_time = prod_time;
}

void Production::set_current_prod_time(float current_prod_time)
{
	_current_prod_time = current_prod_time;
}
		
// --- METHODES ---

void Production::update(float dt)
{
	//Incrémentation du temps de production actuel
	set_current_prod_time(_current_prod_time+dt);
	//Mettre à jour la barre de progression
	//Si le temps de production actuel est supérieur ou égal au temps de production, l'unité est crée !
	if (_current_prod_time >= _prod_time)
	{
		//Instanciation REELLE de l'unité
	}
}
