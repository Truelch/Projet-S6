#include "Game.h"
#include "AppMacros.h"
#include <iostream>

#include "Layer.h"


USING_NS_CC;

using namespace std;

Game::Game(): CCScene()
{
	_main_layer = new Layer(this);
	_main_layer->setTouchEnabled(true);
	_main_layer->setZOrder(1);
	addChild(_main_layer);

	_moveables.push_back(new Moveable(200,200,300,300,-90,3.5,"01.png"));/* !! */
	_main_layer->addChild(*(_moveables.end()-1),0); //this->addChild(_displayables[_displayables.size()-1]),0);

	_hud_layer = new Layer(this);
	_hud_layer->setTouchEnabled(true);
	_hud_layer->setZOrder(2);
	addChild(_hud_layer);

	_hud = new Hud(256,180,"hud.png");
	_hud_layer->addChild(_hud,0);

	
	this->schedule( schedule_selector( Game::update ), 1.0 / 50 );
}



void Game::update(CCTime dt)
{
	vector <Moveable *>::iterator it;
	//const CCPoint* pos=NULL; //cf doc
	/*for(it=_displayables.begin();it!=_displayables.end();it++)
	{
		if(pos) delete pos;
		pos = new CCPoint((*it)->getPosition());
		if(pos->x < 500)
		{
			(*it)->setPositionX(((*it)->getPosition().x)+1);
		}
		else
		{
			(*it)->setPositionX(150);
		}
	}
	if(pos) delete pos;
	*/
	for(it=_moveables.begin();it!=_moveables.end();it++)
		{
			(*it)->move(/*float dt*/);
		}

}


void Game::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	/*
	CCPoint p = ((CCTouch *)(*(touches->begin())))->getLocation();
	(*_displayables.begin())->setPosition(p);
	*/
	vector <Moveable *>::iterator it;
	CCPoint destination = ((CCTouch *)(*(touches->begin())))->getLocation();
	for(it=_moveables.begin();it!=_moveables.end();it++)
	{
		(*it)->set_destination(destination.x,destination.y);
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


