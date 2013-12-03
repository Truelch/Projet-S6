#include "Moveable.h"
#include <math.h>
//=> pour les sqrt
#include <iostream>
#include "Box2D/Box2D.h"
#include "Game.h"

#include <math.h>

#define PI 3.14159265

using namespace std;

Moveable::Moveable(): PhysicsDisplayable(), _rest(false), _groundFixture(5.0f), _density(1.0f), _time_before_restore_position(-100), _mode_restore_position(false), _hold_position(false), _move_in_progress(false) {
}

Moveable::Moveable(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float hitboxRadius, float groundFixture, float density, const char * filename, Game * game, Layer * layer): PhysicsDisplayable(game,CCPhysicsSprite::create(filename), layer), _rest(false), _groundFixture(groundFixture), _density(density), _hitboxRadius(hitboxRadius), _time_before_restore_position(-100), _mode_restore_position(false), _hold_position(false), _move_in_progress(false)
{
	b2Vec2 vecteur_path;
	bodyInit(x,y,rotation,hitboxRadius);
	set_move_speed(move_speed);	
	_list_destination.push_back(getSprite()->getPosition());

	_tile_x=-1;
	_tile_y=-1;
	updateCoordonates();
	
	vecteur_path.Set(x_dest - getSprite()->getPositionX(), y_dest - getSprite()->getPositionY());
	if(vecteur_path.Length()<0.000001) {
		_rest=true;
	}
	else {
		set_destination(x_dest,y_dest);
	}
}

Moveable::~Moveable() {
}

void Moveable::updateCoordonates() {
	CCPoint position = getSprite()->getPosition();
	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(position.x, position.y, _tile_x, _tile_y);
}

void Moveable::bodyInit(int x, int y, int rotation, float hitboxRadius) {
	b2BodyDef bodyDef;
	bodyDef.userData = this;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x/PTM_RATIO, y/PTM_RATIO);
	bodyDef.fixedRotation = true;

	b2Body *body = getGame()->getWorld()->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = hitboxRadius;

	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;	
	fixtureDef.density = _density;
	body->CreateFixture(&fixtureDef);	

	getPhysicsSprite()->setB2Body(body);
	getPhysicsSprite()->setPTMRatio(PTM_RATIO);
	getPhysicsSprite()->setPosition( ccp(x,y) );
	getPhysicsSprite()->setRotation(rotation);
}

void Moveable::goToDestination() {
	b2Vec2 vecteur_path, vecteur_unitaire, vecteur_vitesse;
	float angle;

	vecteur_path.Set(_list_destination[0].x - getSprite()->getPositionX(), _list_destination[0].y - getSprite()->getPositionY());
	vecteur_unitaire = vecteur_path;
	vecteur_unitaire.Normalize();
	vecteur_vitesse=_move_speed*vecteur_unitaire;

	//set angle
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
	else if(_list_destination.size()>1) {
		_list_destination.erase(_list_destination.begin());
		goToDestination();
	}
	else { 
		getPhysicsSprite()->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
		if(_move_in_progress) {
			getGame()->getEventHandler()->on_moveable_destination_reched(this);
		}
		_move_in_progress=false;
		_rest=true;
		_mode_restore_position=false;
	}
}

void Moveable::applyFixture(float dt) {
	b2Vec2 vecteur_path, vecteur_unitaire, vecteur_vitesse;
	vecteur_vitesse = getPhysicsSprite()->getB2Body()->GetLinearVelocity();
	if(vecteur_vitesse.Length()>dt*_groundFixture) {
		vecteur_unitaire = vecteur_vitesse;
		vecteur_unitaire.Normalize();
		vecteur_vitesse -= dt*_groundFixture*vecteur_unitaire;
		getPhysicsSprite()->getB2Body()->SetLinearVelocity(vecteur_vitesse);
	}
	else getPhysicsSprite()->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
}

void Moveable::update(float dt)
{
	b2Vec2 vecteur_path, vecteur_vitesse;
	if(_time_before_restore_position!=-100) {
		_time_before_restore_position-=dt;
		if(_time_before_restore_position<=0) {
			_time_before_restore_position=-100;
			_mode_restore_position=true;
			_rest=false;
		}
	}

	if(_hold_position) goToDestination();
	else {
		if(_mode_restore_position) {
			vecteur_path.Set(_list_destination[0].x - getSprite()->getPositionX(), _list_destination[0].y - getSprite()->getPositionY());
			vecteur_vitesse = getPhysicsSprite()->getB2Body()->GetLinearVelocity();
			//si on est proche de la destination on reprend la main
			if(vecteur_path.Length()<=vecteur_vitesse.Length()) {
				_mode_restore_position=false;
				_rest=false;
			}
		}
		if(_mode_restore_position || !_rest) goToDestination();
		else getPhysicsSprite()->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
	}

	updateCoordonates();

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

void Moveable::on_displayable_contact(Displayable * displayableA, Displayable * displayableB) {
	Moveable * moveable = NULL;
	if(displayableA==this) {
		if(displayableB->getType()==Displayable::moveableType || displayableB->getType()==Displayable::unitType) {
			moveable = (Moveable *)displayableB;
		}
	}
	else if(displayableB==this) {
		if(displayableA->getType()==Displayable::moveableType || displayableA->getType()==Displayable::unitType) {
			moveable = (Moveable *)displayableA;
		}
	}
	if(moveable && !_hold_position) {
		if(_rest && moveable->_mode_restore_position) {
			b2Vec2 vecteur_unitaire(getSprite()->getPositionX()-moveable->getSprite()->getPositionX(), getSprite()->getPositionY()-moveable->getSprite()->getPositionY());
			vecteur_unitaire.Normalize();
			vecteur_unitaire*=getPhysicsSprite()->getB2Body()->GetFixtureList()->GetShape()->m_radius*50;

			set_destination(getSprite()->getPositionX()+vecteur_unitaire.x,getSprite()->getPositionY()+vecteur_unitaire.y);
		}
		else _time_before_restore_position=0.1;
	}
}

// --- GET ---

CCPoint Moveable::get_destination()
{
	return *(_list_destination.end()-1);
}

float Moveable::get_move_speed()
{
	return _move_speed;
}


// --- SET ---

bool Moveable::set_destination(float x_dest,float y_dest)
{
	int tile1_x, tile1_y, tile2_x, tile2_y;
	CCPoint position = getSprite()->getPosition();
	vector<MapTile *> result;
	unsigned int i;

	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(position.x, position.y,tile1_x,tile1_y);
	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(x_dest, y_dest,tile2_x,tile2_y);

	result = getGame()->get_display_layer()->get_tile_layer()->path_finding(tile1_x,tile1_y,tile2_x,tile2_y);

	if(result.size()==0) return false;
	
	_list_destination.clear();
	for(i=1;i<result.size()-1;i++) {
		_list_destination.push_back(result[i]->getSprite()->getPosition());
	}
	_list_destination.push_back(CCPoint(x_dest,y_dest));

	_rest=false;
	_move_in_progress=true;
	_mode_restore_position=false;
	return true;
}

void Moveable::set_move_speed(float move_speed)
{
	_move_speed = move_speed;
}

void Moveable::set_hold_position(bool hold_position) {
	if(hold_position) {
		_mode_restore_position=false;
		_hold_position=true;
	}
	else _hold_position=false;
}
