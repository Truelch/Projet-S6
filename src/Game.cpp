#include "Game.h"
#include "AppMacros.h"
#include <iostream>

#include "Unit.h"


USING_NS_CC;

using namespace std;

Game::Game(): Scene()
{
	std::cout << "Constructeur de Game" << std::endl;
	_display_layer = new DisplayLayer(this);
	_display_layer->setTouchEnabled(true);
	//_display_layer->setZOrder(1);
	addChild(_display_layer);

	_contactListener = new ContactListener();
	getWorld()->SetContactListener(_contactListener);

	Player * joueur1 = new Player("joueur1", Player::blue, 1, 1);
	Player * joueur2 = new Player("joueur2", Player::red, 2, 2);

	_display_layer->get_unit_layer()->add_unit(new Unit(250,150,250,150,-90,5,5.0f,1.0f,"tank01.png", this, "tank",100,100,100,100,100,100,100,100, joueur1));
	_display_layer->get_unit_layer()->add_unit(new Unit(400,150,250,150,-90,5,5.0f,1.0f,"tank01.png", this, "tank",100,100,100,100,100,100,100,100, joueur2));

	//_display_layer->get_unit_layer()->addUnit(new Unit(0,0,0,0,-90,5,5.0f,"tank01.png", this, "tank",100,100,100,100,100,100,100,100));

	/*
	_hud_layer = new Layer(this);
	_hud_layer->setTouchEnabled(true);
	_hud_layer->setZOrder(2);
	addChild(_hud_layer);

	_hud = new Hud(256,180,"hud.png");
	_hud_layer->addChild(_hud,0);
	*/

	this->schedule( schedule_selector( Game::update ), 1.0 / 50 );	
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
	/*
	CCPoint p = ((CCTouch *)(*(touches->begin())))->getLocation();
	(*_displayables.begin())->setPosition(p);
	*/
	CCPoint destination = ((CCTouch *)(*(touches->begin())))->getLocation();
	if(_display_layer->get_unit_layer()->get_number_unit()>0)
	{
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


