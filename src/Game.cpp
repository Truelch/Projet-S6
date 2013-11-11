#include "Game.h"
#include "AppMacros.h"
#include <iostream>

#include "Layer.h"


USING_NS_CC;

using namespace std;

Game::Game(): Scene()
{
	
	_display_layer = new DisplayLayer(this);
	_display_layer->setTouchEnabled(true);
	//_display_layer->setZOrder(1);
	addChild(_display_layer);

	/*
	_moveables.push_back(new Moveable(200,200,300,300,-90,3.5,"01.png"));  // !!
	_main_layer->addChild(*(_moveables.end()-1),0); //this->addChild(_displayables[_displayables.size()-1]),0);

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
DisplayLayer * Game::get_display_layer()
{
	return _display_layer;
}



void Game::update(CCTime dt)
{
	vector <Displayable *>::iterator it;

	//Unités
	
	for(it=get_display_layer()->get_unit_layer()->get_displayable_list().begin() ; it!=get_display_layer()->get_unit_layer()->get_displayable_list().end() ; it++)
		{
			((Moveable *)(*it))->move(/*float dt*/);
		}

}


void Game::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	/*
	CCPoint p = ((CCTouch *)(*(touches->begin())))->getLocation();
	(*_displayables.begin())->setPosition(p);
	*/
	/*vector <Moveable *>::iterator it;
	CCPoint destination = ((CCTouch *)(*(touches->begin())))->getLocation();
	for(it=_moveables.begin();it!=_moveables.end();it++)
	{
		(*it)->set_destination(destination.x,destination.y);
	}*/	
	
}

void Game::ccTouchesMoved(CCSet* touches, CCEvent* event) {
	/*CCPoint p = ((CCTouch *)(*(touches->begin())))->getLocation();
	(*_displayables.begin())->setPosition(p);*/
}

void Game::ccTouchesEnded(CCSet* touches, CCEvent* event) {
}

void Game::ccTouchesCancelled(CCSet* touches, CCEvent* event) {
}


