#include "Moveable.h"
#include <math.h>
//=> pour les sqrt
#include <iostream>
#include "Box2D/Box2D.h"

#include <math.h>

#define PI 3.14159265

using namespace std;

Moveable::Moveable(): PhysicsDisplayable(), _targetReached(false), _groundFixture(5.0f) {
}

Moveable::Moveable(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float hitboxRadius, float groundFixture, const char * filename, Scene * scene): PhysicsDisplayable(scene,CCPhysicsSprite::create(filename)), _targetReached(false), _groundFixture(groundFixture)
{
	bodyInit(x,y,rotation,hitboxRadius);
	set_destination(x_dest,y_dest);
	set_move_speed(move_speed);	
}

void Moveable::bodyInit(int x, int y, int rotation, float hitboxRadius) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x/PTM_RATIO, y/PTM_RATIO);

	b2Body *body = getScene()->getWorld()->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(1.0f, 1.0f);//These are mid points for our 1m box
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = hitboxRadius;

	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;	
	body->CreateFixture(&fixtureDef);	

	getPhysicsSprite()->setB2Body(body);
	getPhysicsSprite()->setPTMRatio(PTM_RATIO);
	getPhysicsSprite()->setPosition( ccp(x,y) );
	getPhysicsSprite()->setRotation(rotation);
}

void Moveable::move(float dt)
{
	b2Vec2 vecteur_path, vecteur_unitaire, vecteur_vitesse;
	double angle;
	if(!_targetReached) {
		vecteur_path.Set(_destination.x - getSprite()->getPositionX(), _destination.y - getSprite()->getPositionY());
		vecteur_unitaire = vecteur_path;
		vecteur_unitaire.Normalize();
		vecteur_vitesse=_move_speed*vecteur_unitaire;

		if(vecteur_path.Length()>1) {
			angle = acos(vecteur_unitaire.x)+M_PI/2;
			if(vecteur_unitaire.y<0) {
				if(vecteur_unitaire.x>0) angle=M_PI-angle;
				else angle=3*M_PI-angle;
			}
			getPhysicsSprite()->getB2Body()->SetTransform(getPhysicsSprite()->getB2Body()->GetPosition(), angle);
		}

		if(vecteur_vitesse.Length() < vecteur_path.Length()) {
			getPhysicsSprite()->getB2Body()->SetLinearVelocity(vecteur_vitesse);
		}
		else if (vecteur_path.Length()>0.000001) {
			getPhysicsSprite()->getB2Body()->SetLinearVelocity(vecteur_path);
		}
		//else _targetReached=true;
	}
	else {
		vecteur_vitesse = getPhysicsSprite()->getB2Body()->GetLinearVelocity();
		if(vecteur_vitesse.Length()>dt*_groundFixture) {
			vecteur_unitaire = vecteur_vitesse;
			vecteur_unitaire.Normalize();
			vecteur_vitesse -= dt*_groundFixture*vecteur_unitaire;
			getPhysicsSprite()->getB2Body()->SetLinearVelocity(vecteur_vitesse);
		}
		else getPhysicsSprite()->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
	}

	/*
	//Coeff unité de temps
	//float coeff = 50;
	//dt = 1/50 en temps normal
	//Définition du vecteur unitaire de déplacement : contient 2 valeurs => CCPoint
	float delta_x = _destination.x - getSprite()->getPositionX();
	float delta_y = _destination.y - getSprite()->getPositionY();
	
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
		setPositionX(getSprite()->getPositionX() + vect_x*_move_speed);
		setPositionY(getSprite()->getPositionY() + vect_y*_move_speed);
		//_position.x += vect_x; //(dt/coeff);
		//_position.y += vect_y; //(dt/coeff);
	}
	else
	{
		//setPositionX(get_destination().x);	
		//setPositionY(get_destination().y);
	}
	*/
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
	_targetReached=false;
	_destination.x = x_dest;
	_destination.y = y_dest;
}

void Moveable::set_move_speed(float move_speed)
{
	_move_speed = move_speed;
}
