#include "Game.h"
#include "AppMacros.h"
#include <iostream>

#include "Layer.h"


USING_NS_CC;

using namespace std;

Game::Game(): CCScene()
{
	layer = new Layer(this);
	addChild(layer);

	_moveables.push_back(new Moveable(200,200,300,300,-90,3.5,"01.png"));/* !! */
	layer->addChild(*(_moveables.end()-1),0); //this->addChild(_displayables[_displayables.size()-1]),0);
	
	//_hud = new Hud(0, 210, 0, "hud.png")

	this->schedule( schedule_selector( Game::update ), 1.0 / 50 );
	layer->setTouchEnabled(true);
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


