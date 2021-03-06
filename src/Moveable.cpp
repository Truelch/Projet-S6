#include "Moveable.h"
#include <math.h>
//=> pour les sqrt
#include <iostream>
#include "Box2D/Box2D.h"
#include "Game.h"
#include "DisplayLayer.h"
#include "EventHandler.h"
#include "TileLayer.h"
#include "Player.h"

#include "UnitLayer.h"

#include <math.h>

using namespace std;

Moveable::Moveable(): PhysicsDisplayable(), _vect_ligne_destination(b2Vec2(0,0)), _rest(false), _groundFixture(5.0f), _density(1.0f), _time_before_restore_position(-100), _mode_restore_position(false), _hold_position(false), _move_in_progress(false) {
}

Moveable::Moveable(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float hitboxRadius, float groundFixture, float density, const char * filename, Game * game, Layer * layer): PhysicsDisplayable(game,CCPhysicsSprite::create(filename), layer), _vect_ligne_destination(b2Vec2(0,0)), _rest(false), _groundFixture(groundFixture), _density(density), _hitboxRadius(hitboxRadius), _time_before_restore_position(-100), _mode_restore_position(false), _hold_position(false), _move_in_progress(false)
{
	b2Vec2 vecteur_path;
	bodyInit(x,y,rotation,hitboxRadius);
	set_move_speed(move_speed);	
	CCPoint destination = getSprite()->getPosition();
	int tile_x, tile_y;
	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(destination.x, destination.y, tile_x, tile_y);
	_list_destination.push_back({destination,vector<MapTile *>()});
	(_list_destination.end()-1)->map_tile_list.push_back(getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[tile_y][tile_x]);

	_tile_x=-1;
	_tile_y=-1;
	updateCoordonates();
	if(_tile_x<0 || _tile_x>=getGame()->get_display_layer()->get_map_width() || _tile_y<0 || _tile_y>=getGame()->get_display_layer()->get_map_height())
		std::cerr << "ERREUR : Moveable construit en dehors de la map" << std::endl;
	
	vecteur_path.Set(x_dest - getSprite()->getPositionX(), y_dest - getSprite()->getPositionY());
	if(vecteur_path.Length()<0.000001) {
		_rest=true;
	}
	else {
		set_destination(x_dest,y_dest);
	}

	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(x,y,tile_x,tile_y);
	if(!getGame()->get_main_player()->get_map_tile_info()[tile_y][tile_x].visible) {
		set_visible(false);
	}

	getSprite()->setRotation(rotation);
}

Moveable::~Moveable() {
	getGame()->getWorld()->DestroyBody(_body);
}

void Moveable::updateCoordonates() {
	int old_tile_x=_tile_x;
	int old_tile_y=_tile_y;
	CCPoint destination = _list_destination.end()->destination;
	CCPoint position = getSprite()->getPosition();
	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(position.x, position.y, _tile_x, _tile_y);

	if(old_tile_x!=_tile_x || old_tile_y!=_tile_y) {
		getGame()->getEventHandler()->on_moveable_change_map_tile(_tile_x, _tile_y, this);

		//si la nouvelle tile n'est pas dans le chemin prevu
		if(	std::find(_list_destination.begin()->map_tile_list.begin(), _list_destination.begin()->map_tile_list.end(), getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[_tile_y][_tile_x]) == _list_destination.begin()->map_tile_list.end() ) {
			set_destination(destination.x,destination.y);
		}

		if(!getGame()->get_main_player()->get_map_tile_info()[_tile_y][_tile_x].visible) {
			set_visible(false);
		}
		else set_visible(true);
	}
}

void Moveable::bodyInit(int x, int y, int rotation, float hitboxRadius) {
	b2BodyDef bodyDef;
	bodyDef.userData = this;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x/PTM_RATIO, y/PTM_RATIO);
	bodyDef.fixedRotation = true;

	_body = getGame()->getWorld()->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = hitboxRadius/PTM_RATIO;

	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;	
	fixtureDef.density = _density;
	_body->CreateFixture(&fixtureDef);	

	getPhysicsSprite()->setB2Body(_body);
	getPhysicsSprite()->setPTMRatio(PTM_RATIO);
	getPhysicsSprite()->setPosition( ccp(x,y) );
	getPhysicsSprite()->setRotation(rotation);
}

void Moveable::init_point_ligne_destination() {
	CCPoint destination = _list_destination.begin()->destination;
	CCPoint position = getSprite()->getPosition();
	_vect_ligne_destination.Set(destination.x-position.x,destination.y-position.y);
	_vect_ligne_destination=_vect_ligne_destination.Skew();
	if(b2Cross(_vect_ligne_destination,b2Vec2(destination.x-position.x,destination.y-position.y))<0) {
		_vect_ligne_destination*=-1;
	}
}

bool Moveable::test_current_destination_reched() {
	if(b2Vec2(_list_destination[0].destination.x - getSprite()->getPositionX(), _list_destination[0].destination.y - getSprite()->getPositionY()).Length() < _move_speed) {
		_vect_ligne_destination.SetZero();
		return true;
	}
	CCPoint destination = _list_destination.begin()->destination;
	CCPoint position = getSprite()->getPosition();
	if( _vect_ligne_destination.x!=0 || _vect_ligne_destination.y!=0 ) {
		if(b2Cross(_vect_ligne_destination,b2Vec2(destination.x-position.x,destination.y-position.y))<0) {
			_vect_ligne_destination.SetZero();
			return true;
		}
	}
	return false;
}

void Moveable::goToDestination() {
	b2Vec2 vecteur_path, vecteur_unitaire, vecteur_vitesse;
	float angle;

	vecteur_path.Set(_list_destination[0].destination.x - getSprite()->getPositionX(), _list_destination[0].destination.y - getSprite()->getPositionY());
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
		//std::cout << "Angle : " << angle << std::endl;
		getPhysicsSprite()->getB2Body()->SetTransform(getPhysicsSprite()->getB2Body()->GetPosition(), angle);
	}


	//if(vecteur_vitesse.Length() < vecteur_path.Length()) {
	if(!test_current_destination_reched()) {
		getPhysicsSprite()->getB2Body()->SetLinearVelocity(vecteur_vitesse);
	}
	else if(_list_destination.size()>1) {
		_list_destination.erase(_list_destination.begin());
		init_point_ligne_destination();
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
			vecteur_path.Set(_list_destination[0].destination.x - getSprite()->getPositionX(), _list_destination[0].destination.y - getSprite()->getPositionY());
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
	return (*(_list_destination.end()-1)).destination;
}

float Moveable::get_move_speed()
{
	return _move_speed;
}

float Moveable::get_hitboxRadius() {
	return _hitboxRadius;
}


// --- SET ---

bool Moveable::set_destination(float x_dest,float y_dest) {
	int tile1_x, tile1_y, tile2_x, tile2_y;
	CCPoint position = getSprite()->getPosition();
	CCPoint destination = CCPoint(x_dest,y_dest);
	std::vector<MapTile *> result;
	std::vector<MapTile *> list_tile_straight_path;
	std::vector<ListDestinationItem>::iterator it;
	CCPoint a,b;
	b2Vec2 vect;
	unsigned int i;
	bool achievable=true;

	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(position.x, position.y,tile1_x,tile1_y);
	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(destination.x,destination.y,tile2_x,tile2_y);

	result = getGame()->get_display_layer()->get_tile_layer()->path_finding(tile1_x,tile1_y,tile2_x,tile2_y);

	//si la destination n'est pas atteignable on essayer avec toutes les tiles en partant de la destination jusqu'a la position actuelle pour se rapprocher le plus possible de la destination
	if(result.size()==0) {
		achievable=false;
		list_tile_straight_path = getGame()->get_display_layer()->get_tile_layer()->line_through_tile(position,destination);
		do {
			tile2_x = (*(list_tile_straight_path.end()-1))->get_tile_x();
			tile2_y = (*(list_tile_straight_path.end()-1))->get_tile_y();
			result = getGame()->get_display_layer()->get_tile_layer()->path_finding(tile1_x,tile1_y,tile2_x,tile2_y);
			list_tile_straight_path.erase(list_tile_straight_path.end()-1);
		} while(result.size()==0);
		destination = getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[tile2_y][tile2_x]->getSprite()->getPosition();
	}

	_list_destination.clear();
	_list_destination.push_back({position,std::vector<MapTile *>()});
	for(i=1;i<result.size()-1;i++) {
		_list_destination.push_back({result[i]->getSprite()->getPosition(),std::vector<MapTile *>()});
	}
	_list_destination.push_back({destination,std::vector<MapTile *>()});
	
	if(_list_destination.size()>2) {
		it=_list_destination.begin()+2;
		while(it!=_list_destination.end()) {
			a=(*(it-2)).destination;
			b=(*it).destination;

			vect.Set(b.x-a.x,b.y-a.y);
			vect.Set(-vect.y,vect.x);
			vect.Normalize();
			vect*=_hitboxRadius;

			a.x+=vect.x;
			a.y+=vect.y;
			b.x+=vect.x;
			b.y+=vect.y;
			if(!getGame()->get_display_layer()->get_tile_layer()->test_line_traversable(a,b)) {
				it++;
				continue;
			}

			a=(*(it-2)).destination;
			b=(*it).destination;
			a.x-=vect.x;
			a.y-=vect.y;
			b.x-=vect.x;
			b.y-=vect.y;
			if(!getGame()->get_display_layer()->get_tile_layer()->test_line_traversable(a,b)) {
				it++;
				continue;
			}

			_list_destination.erase(it-1);
		}
	}
	
	for(it=_list_destination.begin()+1;it!=_list_destination.end();it++) {
		it->map_tile_list = getGame()->get_display_layer()->get_tile_layer()->line_through_tile((it-1)->destination,it->destination);
	}

	_list_destination.erase(_list_destination.begin());

	init_point_ligne_destination();

	_rest=false;
	_move_in_progress=true;
	_mode_restore_position=false;
	return achievable;
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

bool Moveable::test_point_in_moveable(CCPoint point) {
	return getSprite()->getPosition().getDistance(point)<_hitboxRadius;
}

void Moveable::on_player_range_tile(int x, int y, Player * player) {
	if(getGame()->get_main_player()==player && x==_tile_x && y==_tile_y) {
		set_visible(true);
	}
}

void Moveable::on_player_unrange_tile(int x, int y, Player * player) {
	if(getGame()->get_main_player()==player && x==_tile_x && y==_tile_y) {
		set_visible(false);
	}
	
}

void Moveable::set_visible(bool visible) {
	if(visible) {
		getSprite()->setScaleX(1);
		getSprite()->setScaleY(1.2);
	} else {
		getSprite()->setScaleX(0);
		getSprite()->setScaleY(0);
	}
}

bool Moveable::get_visible() {
	return getSprite()->getScaleX()!=0 && getSprite()->getScaleY()!=0;
}

