#ifndef BUILDING_H
#define BUILDING_H

#include "cocos2d.h"
#include "Displayable.h"

using namespace cocos2d;

class Building : public Displayable
{
	public:
		Building();
		Building(float x, float y, float rotation, const char * filename, float x_rally_point, float y_rally_point);
		//Pensez à rajouter la liste d'unités pouvant être produites
		
		// --- ATTRIBUTS ---
		CCPoint _rally_point;
		
		// --- METHODES ---
		
		// --- GET ---
		CCPoint get_rally_point();
		
		// --- SET ---
		void set_rally_point(float x_rally_point, float y_rally_point);
};

#endif
