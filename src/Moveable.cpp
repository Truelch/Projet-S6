#include "Moveable.h"

Moveable::Moveable(): Displayable() {
	//
}

Moveable::Moveable(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, const char * filename): Displayable(x,y,rotation,filename) {
	set_destination(x_dest,y_dest);
}


// --- GET ---

CCPoint Moveable::destination()
{
	return _destination;
}

float Moveable::move_speed()
{
	return _move_speed;
}


// --- SET ---

void Moveable::set_destination(float x_dest,float y_dest)
{
	_destination.x = x_dest;
	_destination.y = y_dest;
}

void Moveable::set_move_speed(float move_speed)
{
	_move_speed = move_speed;
}
