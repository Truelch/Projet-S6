#ifndef MAP_DISPLAYABLE_H
#define MAP_DISPLAYABLE_H

#include "cocos2d.h"
#include "Displayable.h"

// LA CLASSE TILE EXISTE DEJA DANS COCOS2D 

using namespace cocos2d;

class MapDisplayable : public Displayable
{
	public:
		MapDisplayable();
		MapDisplayable(float x, float y, const char * filename, Game * game, Layer * layer);
		
		// --- Attributs ---

		
		// --- METHODES ---
		
		
		// --- GET ---

		
		// --- SET ---

		
};

#endif
