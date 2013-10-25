#ifndef HUD_H
#define HUD_H

#include "cocos2d.h"
#include "Displayable.h"

using namespace cocos2d;

class Hud : public Displayable
{
	public:
		Hud();
		Hud(float x, float y, float rotation, const char * filename);
		
		// --- ATTRIBUTS ---
		//Lui ajouter un container de Boutons
		// => Définir ce qu'est un bouton !!
		
		// --- METHODES ---
		
		// --- GET ---
		
		// --- SET ---
		
};

#endif
