#ifndef MAPTILE_H
#define MAPTILE_H

#include "cocos2d.h"
#include "Displayable.h"

// LA CLASSE TILE EXISTE DEJA DANS COCOS2D 

using namespace cocos2d;

class MapTile : public Displayable
{
	public:
		MapTile();
		MapTile(float x, float y, const char * filename, Scene * scene);
		
		// --- Attributs ---

		
		// --- METHODES ---
		
		
		// --- GET ---

		
		// --- SET ---

		
};

#endif
