#ifndef CORPSE_H
#define CORPSE_H

#include "cocos2d.h"
//#include "Displayable.h"
#include "Displayable.h"

using namespace cocos2d;

class Corpse : public Displayable
{
	public:
		//Corpse();
		Corpse(float x, float y, const char * filename, Game * game, Layer * layer);

		virtual Displayable::DisplayableType getType() { return Displayable::corpseType; }
		
		// --- Attributs ---

		
		// --- METHODES ---
		
		
		// --- GET ---
		
		// --- SET ---

		
};

#endif
