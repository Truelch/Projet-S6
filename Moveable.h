#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "cocos2d.h"
#include "Displayable.h"

using namespace cocos2d;

class Moveable : public Displayable
{
	public:
		Moveable();
		Moveable(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, const char * filename);
		
		// --- Attributs ---
		CCPoint _destination;
		float _move_speed;
		
		// --- GET ---
		CCPoint destination();
		float move_speed();
		
		// --- SET ---
		void set_destination(float x_dest, float y_dest);
		void set_move_speed(float move_speed);
		
};

#endif
