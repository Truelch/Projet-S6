#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "cocos2d.h"
#include "cocos-ext.h"

#include "PhysicsDisplayable.h"

using namespace cocos2d;

class Moveable : public PhysicsDisplayable
{
	private:
		// --- Attributs ---
		CCPoint _destination;
		float   _move_speed;

		bool _targetReached;
		float _groundFixture;
		
	public:
		Moveable();
		Moveable(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float hitboxRadius, float groundFixture, const char * filename, Scene * scene);

		void bodyInit(int x,int y, int rotation, float hitboxRadius);
		
		// --- METHODES ---
		void move(float dt);
		
		// --- GET ---
		CCPoint get_destination();
		float   get_move_speed();
		
		// --- SET ---
		void set_destination(float x_dest, float y_dest);
		void set_move_speed(float move_speed);
		
};

#endif
