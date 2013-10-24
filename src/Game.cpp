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

	_displayables.push_back(new Displayable(150,150,-90,"01.png"));
	layer->addChild(*(_displayables.end()-1),0); //this->addChild(_displayables[_displayables.size()-1]),0);


	this->schedule( schedule_selector( Game::update ), 1.0 / 50 );
	layer->setTouchEnabled(true);
}



void Game::update(CCTime dt)
{
	vector <Displayable *>::iterator it;
	const CCPoint* pos=NULL; //cf doc
	for(it=_displayables.begin();it!=_displayables.end();it++)
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

}


void Game::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	CCPoint p = ((CCTouch *)(*(touches->begin())))->getLocation();
	(*_displayables.begin())->setPosition(p);
}

void Game::ccTouchesMoved(CCSet* touches, CCEvent* event) {
	CCPoint p = ((CCTouch *)(*(touches->begin())))->getLocation();
	(*_displayables.begin())->setPosition(p);
}

void Game::ccTouchesEnded(CCSet* touches, CCEvent* event) {
}

void Game::ccTouchesCancelled(CCSet* touches, CCEvent* event) {
}


