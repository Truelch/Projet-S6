#include "Unit.h"

/*
typedef enum {
	cond_integer_comparison, //besoin de 2 entiers
	cond_float_comparison,   //besoin de 2 floats
	cond_boolean_comparison  //besoin de 2 booléens
} Condition;
*/	
	
//Cette classe associe une unité à une condition dans le build order de l'AI

class AIUnitCond
{
	public:
		//AIUnitCond();
		AIUnitCond(Unit* unit/*, Condition cond*/);
}

//Comment implémenter la condition pour la rendre polyvalente ?
//Un container à conditions ?
//Chaque condition correspond à un énumération renvoyant vers une vérification donnée (nbr unité x > alpha)
//container associant une valeur (entière, flottante, booléenne,...) à cette condition
