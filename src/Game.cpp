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

	_display_layer->get_unit_layer()->addUnit(new Unit(100,160,400,150,-90,5,5.0f,"tank01.png", this, "tank",100,100,100,100,100,100,100,100));
	_display_layer->get_unit_layer()->addUnit(new Unit(400,140,100,150,-90,5,5.0f,"tank01.png", this, "tank",100,100,100,100,100,100,100,100));

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
	for(i=0;i<_display_layer->get_unit_layer()->getNumberUnit();i++)
	{
		_display_layer->get_unit_layer()->getUnit(i)->move(dt);
	}

	getWorld()->Step(dt, 8, 1);
}


void Game::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	/*
	CCPoint p = ((CCTouch *)(*(touches->begin())))->getLocation();
	(*_displayables.begin())->setPosition(p);
	*/
	CCPoint destination = ((CCTouch *)(*(touches->begin())))->getLocation();
	if(_display_layer->get_unit_layer()->getNumberUnit()>0)
	{
		_display_layer->get_unit_layer()->getUnit(0)->set_destination(destination.x,destination.y);
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


