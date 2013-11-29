#include "Game.h"
#include "AppMacros.h"
#include <iostream>

#include "Unit.h"
#include "Player.h"
#include "EGLView.h"


USING_NS_CC;

using namespace std;

Game::Game(): Scene(), _scroll_left(false), _scroll_right(false), _scroll_up(false), _scroll_down(false)
{
	std::cout << "Constructeur de Game" << std::endl;
	_display_layer = new DisplayLayer(this,"map/map1");
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
	float x,y,z;

	if(_scroll_left) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		_display_layer->getCamera()->setCenterXYZ(x-10,y,z);
		_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
		_display_layer->getCamera()->setEyeXYZ(x-10,y,z);
	}
	if(_scroll_right) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		_display_layer->getCamera()->setCenterXYZ(x+10,y,z);
		_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
		_display_layer->getCamera()->setEyeXYZ(x+10,y,z);
	}
	if(_scroll_up) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		_display_layer->getCamera()->setCenterXYZ(x,y+10,z);
		_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
		_display_layer->getCamera()->setEyeXYZ(x,y+10,z);
	}
	if(_scroll_down) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		_display_layer->getCamera()->setCenterXYZ(x,y-10,z);
		_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
		_display_layer->getCamera()->setEyeXYZ(x,y-10,z);
	}

	for(i=0;i<_display_layer->get_unit_layer()->get_number_unit();i++)
	{
		_display_layer->get_unit_layer()->get_unit(i)->move(dt);
	}

	getWorld()->Step(dt, 8, 1);
}

/*
void Game::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	CCPoint destination = ((CCTouch *)(*(touches->begin())))->getLocation();
	//le hud va de (27,0) a (452,100)
	if(_display_layer->get_unit_layer()->get_number_unit()>0) {
		_display_layer->get_unit_layer()->get_unit(0)->set_destination(destination.x,destination.y);
	}
}

void Game::ccTouchesMoved(CCSet* touches, CCEvent* event) {
	//CCPoint p = ((CCTouch *)(*(touches->begin())))->getLocation();
	//(*_displayables.begin())->setPosition(p);
}

void Game::ccTouchesEnded(CCSet* touches, CCEvent* event) {
}

void Game::ccTouchesCancelled(CCSet* touches, CCEvent* event) {
}
*/


void Game::mouse_left_button_down( int x, int y ) {
	float cocos_x, cocos_y;
	float offset_x,offset_y,offset_z;

	_display_layer->getCamera()->getCenterXYZ(&offset_x,&offset_y,&offset_z);
	x+=offset_x*2.4;
	y-=offset_y*2.4;

	coordinateOpenglToCocos2dx(x,y,cocos_x,cocos_y);
	if(_display_layer->get_unit_layer()->get_number_unit()>0) {
		_display_layer->get_unit_layer()->get_unit(0)->set_destination(cocos_x,cocos_y);
	}
}

void Game::mouse_move( int x, int y) {
	if(x<50) _scroll_left = true;
	else _scroll_left = false;

	if(x>EGLView::sharedOpenGLView()->getViewPortRect().getMaxX()-114) _scroll_right = true;
	else _scroll_right = false;

	if(y<50) _scroll_up = true;
	else _scroll_up = false;

	if(y>EGLView::sharedOpenGLView()->getViewPortRect().getMaxY()-50) _scroll_down = true;
	else _scroll_down = false;
}


