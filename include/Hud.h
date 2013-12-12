#ifndef HUD_H
#define HUD_H

#include "cocos2d.h"
#include "Displayable.h"

using namespace cocos2d;

class Game;

class Hud : public Displayable
{
	public:
		Hud();
		Hud(float x, float y, const char * filename, Game * game, Layer * layer);

		virtual Displayable::DisplayableType getType() { return Displayable::hudType; }
		
		// --- ATTRIBUTS ---
		//Lui ajouter un container de Boutons
		// => Définir ce qu'est un bouton !!
		
		// --- METHODES ---
		
		// --- GET ---
		
		// --- SET ---
		
};

#endif
