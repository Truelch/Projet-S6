#include "Moveable.h"
#include <math.h>
//=> pour les sqrt
#include <iostream>

#define PI 3.14159265

using namespace std;

Moveable::Moveable(): Displayable() {
	//
}

Moveable::Moveable(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, const char * filename): Displayable(x,y,rotation,filename)
{
	set_destination(x_dest,y_dest);
	set_move_speed(move_speed);	
}

void Moveable::move(/*float dt*/)
{
	//Coeff unité de temps
	/*float coeff = 50;*/
	//dt = 1/50 en temps normal
	//Définition du vecteur unitaire de déplacement : contient 2 valeurs => CCPoint
	float delta_x = _destination.x - getPositionX();
	float delta_y = _destination.y - getPositionY();
	
	float hyp     = sqrt(delta_x*delta_x + delta_y*delta_y);
	
	float vect_x  = delta_x / hyp;
	float vect_y  = delta_y / hyp;
	
	
	if(delta_x != 0)
	{
		float angle;
		if (delta_x < 0)  angle = -1.* atan(delta_y/delta_x) * (180/PI) + 90;
		else angle = -1.* atan(delta_y/delta_x) * (180/PI) + 270;
		//float angle = asin(delta_y/hyp) * (180/PI);
		setRotation(angle);
	}
	
	//Vecteur unitaire
	//vector        = CCPoint(vect_x, vect_y);
	//L'unité se déplace d'un vecteur égal au vecteur unitaire * vitesse
	//speed_vector  = CCPoint(_move_speed * vect_x, _move_speed * _vect_y);
	if(hyp > _move_speed)
	{
		setPositionX(getPositionX() + vect_x*_move_speed);
		setPositionY(getPositionY() + vect_y*_move_speed);
		//_position.x += vect_x/**(dt/coeff)*/;
		//_position.y += vect_y/**(dt/coeff)*/;
	}
	else
	{
		/*setPositionX(get_destination().x);	
		setPositionY(get_destination().y);*/
	}
}


// --- GET ---

CCPoint Moveable::get_destination()
{
	return _destination;
}

float Moveable::get_move_speed()
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
