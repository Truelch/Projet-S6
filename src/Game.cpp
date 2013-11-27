#include "Game.h"
#include "AppMacros.h"
#include <iostream>

#include "Unit.h"
#include "Player.h"


USING_NS_CC;

using namespace std;

Game::Game(): Scene()
{
	std::cout << "Constructeur de Game" << std::endl;
	_display_layer = new DisplayLayer(this);
	_display_layer->setTouchEnabled(true);
	//_display_layer->setZOrder(1);
	addChild(_display_layer);

	_contactListener = new ContactListener(this);
	getWorld()->SetContactListener(_contactListener);

	Player * joueur1 = new Player(this, "joueur1", Player::blue, 1, 1);
	Player * joueur2 = new Player(this, "joueur2", Player::red, 2, 2);

	_display_layer->get_unit_layer()->add_unit(250,200,250,200,-90,5,5.0f,1.0f,"units/tank01.png", "tank",100,100,100,100,100,100,100,100, joueur1);
	_display_layer->get_unit_layer()->add_unit(400,200,400,200,-90,5,5.0f,1.0f,"units/tank01.png", "tank",100,100,100,100,100,100,100,100, joueur1);
	_display_layer->get_unit_layer()->add_unit(100,200,100,200,-90,5,5.0f,1.0f,"units/tank01.png", "tank",100,100,100,100,100,100,100,100, joueur2);

	/*
	MapTile * tile = new MapTile(200,200,"000.png",this);
	_display_layer->get_tile_layer()->addChild(tile->getSprite());

	Building * building = new Building(tile, "ram01.png", this, 0, 0);
	_display_layer->get_building_layer()->addChild(building->getSprite());
	*/

	_hud_layer = new Layer(this);
	//_hud_layer->setTouchEnabled(true);
	_hud_layer->setZOrder(2);
	addChild(_hud_layer);

	_hud = new Hud(256,180,"hud.png", this, _hud_layer);
	_hud_layer->addChild(_hud->getSprite(),0);

	this->schedule( schedule_selector( Game::update ), 1.0 / 50 );	
}

Game::~Game() {
	delete _contactListener;
	delete _display_layer;
	delete _hud_layer;
	delete _hud;
}

// --- GET ---

int Game::get_map_width()
{
	return _map_width;
}

int Game::get_map_height()
{
	return _map_height;
}

DisplayLayer * Game::get_display_layer()
{
	return _display_layer;
}

void Game::update(float dt)
{
	int i;
	for(i=0;i<_display_layer->get_unit_layer()->get_number_unit();i++)
	{
		_display_layer->get_unit_layer()->get_unit(i)->move(dt);
	}

	getWorld()->Step(dt, 8, 1);
}


void Game::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	CCPoint destination = ((CCTouch *)(*(touches->begin())))->getLocation();
	//le hud va de (27,0) a (452,100)
	if(_display_layer->get_unit_layer()->get_number_unit()>0) {
		_display_layer->get_unit_layer()->get_unit(0)->set_destination(destination.x,destination.y);
	}
}

void Game::ccTouchesMoved(CCSet* touches, CCEvent* event) {
	/*CCPoint p = ((CCTouch *)(*(touches->begin())))->getLocation();
	(*_displayables.begin())->setPosition(p);*/
}

void Game::ccTouchesEnded(CCSet* touches, CCEvent* event) {
}

void Game::ccTouchesCancelled(CCSet* touches, CCEvent* event) {
}


