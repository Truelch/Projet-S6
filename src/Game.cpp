#include "Game.h"
#include "AppMacros.h"
#include <iostream>
#include <algorithm>

#include "Unit.h"
#include "Player.h"
#include "EGLView.h"
#include "GL/glfw.h"
#include "DisplayLayer.h"
#include "Moveable.h"
#include "Hud.h"
#include "UnitLayer.h"
#include "ContactListener.h"
#include "Building.h"
#include "Missile.h"

#include "TileLayer.h"
#include "BuildingLayer.h"
#include "MissileLayer.h"
#include "SelectionZone.h"

USING_NS_CC;

using namespace std;

Game::Game(): Scene(), _scroll_left_mouse(false), _scroll_right_mouse(false), _scroll_up_mouse(false), _scroll_down_mouse(false), _scroll_left_key(false), _scroll_right_key(false), _scroll_up_key(false), _scroll_down_key(false), _mouse_button_left_down(false), _key_left_alt(false), _key_right_alt(false), _selection_zone_enable(false)
{
	std::cout << "Constructeur de Game" << std::endl;
	_display_layer = new DisplayLayer(this);
	if(_display_layer->init_file("map/map1")==EXIT_FAILURE) {
		std::cerr << "ERREUR : fichier map invalide" << std::endl;
	}
	_display_layer->setTouchEnabled(true);
	//_display_layer->setZOrder(1);
	_display_layer->setScale(0.2);
	addChild(_display_layer);

	_selectionZone = new SelectionZone(CCPoint(0,0), CCPoint(0,0), this, _display_layer->get_selection_zone_layer(), ccc4(0,255,255,68));

	_contactListener = new ContactListener(this);
	getWorld()->SetContactListener(_contactListener);

	_player_list.push_back( new Player(this, "joueur1", Player::blue, 1, 1) );
	_player_list.push_back( new Player(this, "joueur2", Player::red, 2, 2) );
	
	_main_player = _player_list[0];
	
	float x,y;
	_display_layer->coordonate_tile_to_cocos2dx(0,0,x,y);
	_display_layer->get_unit_layer()->add_unit(x,y,x,y,-90,5,5.0f,1.0f,"units/model_tank_00.png", "tank",100,100,100,100,100,100,100,100, _player_list[0],1000);
	_display_layer->get_unit_layer()->get_unit(0)->add_turret(0,"units/turret_tank_00.png", this, _display_layer->get_missile_layer(), 0, 0, 
				33.0,"missiles/01.png", 12, 1.3, 200.0,_display_layer->get_unit_layer()->get_unit(0));
	
	_display_layer->coordonate_tile_to_cocos2dx(10,0,x,y);
	_display_layer->get_unit_layer()->add_unit(x,y,x,y,-90,5,5.0f,1.0f,"units/model_tank_01.png", "tank",100,100,100,100,100,100,100,100, _player_list[1],1000);
	_display_layer->get_unit_layer()->get_unit(1)->add_turret(0,"units/turret_tank_01.png", this, _display_layer->get_missile_layer(), 0, 0, 
				33.0,"missiles/02.png", 12, 1.3, 200.0,_display_layer->get_unit_layer()->get_unit(1));
	/*
	_display_layer->get_unit_layer()->add_unit(400,200,400,200,-90,5,5.0f,1.0f,"units/tank01.png", "tank",100,100,100,100,100,100,100,100, _player_list[0],200);
	_display_layer->get_unit_layer()->add_unit(100,200,100,200,-90,5,5.0f,1.0f,"units/tank01.png", "tank",100,100,100,100,100,100,100,100, _player_list[1],100);
	*/
	
	//float x2,y2;
	/*
	_display_layer->coordonate_tile_to_cocos2dx(0,1,x2,y2);
	for(int i=0;i<5;i++) {
		for(int j=0;j<5;j++) {
			_display_layer->coordonate_tile_to_cocos2dx(5+i,j,x,y);
			_display_layer->get_unit_layer()->add_unit(x,y,x2,y2,-90,5,5.0f,1.0f,"units/tank01.png", "tank",100,100,100,100,100,100,100,100, _player_list[0],200);
		}
	}
	*/

	/*
	MapTile * tile = new MapTile(200,200,"000.png",this);
	_display_layer->get_tile_layer()->addChild(tile->getSprite());

	Building * building = new Building(tile, "ram01.png", this, 0, 0);
	_display_layer->get_building_layer()->addChild(building->getSprite());
	*/

	_display_layer->get_building_layer()->add_building(10,5,"buildings/ram01.png",this,_display_layer->get_building_layer(),0,0,"batiment1",_main_player,200);

	set_tile_to_center_of_screen(4,3);

	_hud_layer = new Layer(this);
	//_hud_layer->setTouchEnabled(true);
	_hud_layer->setZOrder(2);
	addChild(_hud_layer);

	_hud = new Hud(256,180,"hud.png", this, _hud_layer);

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
	int tile_x, tile_y;
	CCSize size;
	float vitesse_scroling=10.0/_display_layer->getScale();

	if(_scroll_left_mouse || _scroll_right_mouse || _scroll_up_mouse || _scroll_down_mouse || _scroll_left_key || _scroll_right_key || _scroll_up_key || _scroll_down_key) {
		size = CCDirector::sharedDirector()->getWinSize();
		_display_layer->coordonate_cocos2dx_to_tile(size.width/2.0+x,(size.height+100)/2.0+y,tile_x,tile_y);
	}
	if(_scroll_left_mouse || _scroll_left_key) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		x-=vitesse_scroling;
		_display_layer->coordonate_cocos2dx_to_tile(size.width/2.0+x,(size.height+100)/2.0+y,tile_x,tile_y);
		if(tile_x>=0) {
			_display_layer->getCamera()->setCenterXYZ(x,y,z);
			_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
			_display_layer->getCamera()->setEyeXYZ(x-vitesse_scroling,y,z);
		}

	}
	if(_scroll_right_mouse || _scroll_right_key) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		x+=vitesse_scroling;
		_display_layer->coordonate_cocos2dx_to_tile(size.width/2.0+x,(size.height+100)/2.0+y,tile_x,tile_y);
		if(tile_x<_display_layer->get_map_width()) {
			_display_layer->getCamera()->setCenterXYZ(x,y,z);
			_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
			_display_layer->getCamera()->setEyeXYZ(x+vitesse_scroling,y,z);
		}
	}
	if(_scroll_up_mouse || _scroll_up_key) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		y+=vitesse_scroling;
		_display_layer->coordonate_cocos2dx_to_tile(size.width/2.0+x,(size.height+100)/2.0+y,tile_x,tile_y);
		if(tile_y<_display_layer->get_map_height()) {
			_display_layer->getCamera()->setCenterXYZ(x,y,z);
			_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
			_display_layer->getCamera()->setEyeXYZ(x,y+vitesse_scroling,z);
		}
	}
	if(_scroll_down_mouse || _scroll_down_key) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		y-=vitesse_scroling;
		_display_layer->coordonate_cocos2dx_to_tile(size.width/2.0+x,(size.height+100)/2.0+y,tile_x,tile_y);
		if(tile_y>=0) {
			_display_layer->getCamera()->setCenterXYZ(x,y,z);
			_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
			_display_layer->getCamera()->setEyeXYZ(x,y-vitesse_scroling,z);
		}
	}

	for(i=0;i<_display_layer->get_unit_layer()->get_number_unit();i++)
	{
		_display_layer->get_unit_layer()->get_unit(i)->update(dt);
	}

	getWorld()->Step(dt, 8, 1);

	//Update de joueurs
	vector<Player *>::iterator it;
	
	for(it=_player_list.begin(); it!=_player_list.end();it++) 
	{
		(*it)->update(dt);
	}
	
	//Update d'unités
	for(i=0; i!=get_display_layer()->get_unit_layer()->get_number_unit();i++) 
	{
		get_display_layer()->get_unit_layer()->get_unit(i)->update(dt);
	}
	//Pas besoin de faire ça pour les unités
	/*for(i=0; i!=get_display_layer()->get_unit_layer()->get_number_unit();) 
	{
		if(!get_display_layer()->get_unit_layer()->get_unit(i)->update(dt)) i++;
	}*/	
	
	//Update de missiles
	for(i=0; i!=get_display_layer()->get_missile_layer()->get_number_missile();) 
	{
		if(!get_display_layer()->get_missile_layer()->get_missile(i)->update(dt)) i++;
	}
}

void Game::set_tile_to_center_of_screen(int tile_x, int tile_y) {
	float x,y;
	_display_layer->coordonate_tile_to_cocos2dx(tile_x,tile_y,x,y);
	set_point_to_center_of_screen(CCPoint(x,y));
}

void Game::set_point_to_center_of_screen(CCPoint point) {
	CCSize frame_size = EGLView::sharedOpenGLView()->getFrameSize();
	set_map_point_to_opengl_point(point, frame_size.width/2, frame_size.height/2);
}

void Game::set_map_point_to_opengl_point(CCPoint map_point, int opengl_x, int opengl_y) {
	float offset_x,offset_y,offset_z;
	float cocos_x,cocos_y;
	CCPoint screen_point;

	CCSize frameSize = EGLView::sharedOpenGLView()->getFrameSize();
	opengl_x=frameSize.width/2+((opengl_x-frameSize.width/2)/_display_layer->getScaleX());
	opengl_y=frameSize.height/2+((opengl_y-frameSize.height/2)/_display_layer->getScaleY());
	coordinateOpenglToCocos2dx(opengl_x, opengl_y, cocos_x, cocos_y);
	screen_point.x = cocos_x;
	screen_point.y = cocos_y;

	CCPoint new_offset(map_point.x-screen_point.x,map_point.y-screen_point.y);

	_display_layer->getCamera()->getCenterXYZ(&offset_x,&offset_y,&offset_z);
	_display_layer->getCamera()->setCenterXYZ(new_offset.x,new_offset.y,offset_z);
	_display_layer->getCamera()->getEyeXYZ(&offset_x,&offset_y,&offset_z);
	_display_layer->getCamera()->setEyeXYZ(new_offset.x,new_offset.y,offset_z);
}

CCPoint Game::convert_opengl_point_to_map_point(int opengl_x, int opengl_y) {
	CCPoint map_point;
	float offset_x,offset_y,offset_z;
	float cocos_x, cocos_y;
	CCSize frameSize = EGLView::sharedOpenGLView()->getFrameSize();

	opengl_x=frameSize.width/2+((opengl_x-frameSize.width/2)/_display_layer->getScaleX());
	opengl_y=frameSize.height/2+((opengl_y-frameSize.height/2)/_display_layer->getScaleY());

	_display_layer->getCamera()->getCenterXYZ(&offset_x,&offset_y,&offset_z);
	coordinateOpenglToCocos2dx(opengl_x,opengl_y,cocos_x,cocos_y);

	map_point.x = cocos_x+offset_x;
	map_point.y = cocos_y+offset_y;

	return map_point;
}

void Game::mouse_left_button_down( int x, int y ) {
	_mouse_button_left_down=true;

	int tile_x, tile_y, i,j,k;
	CCPoint point = convert_opengl_point_to_map_point(x,y);
	_display_layer->coordonate_cocos2dx_to_tile(point.x, point.y, tile_x, tile_y);
	Container<Unit> unit_container;
	Unit * unit_selected = NULL;
	bool unit_already_selected=false;

	for(i=tile_x-1;i<tile_x+2;i++) {
		for(j=tile_y-1;j<tile_y+2;j++) {
			if(j>=0 && j<(int)_display_layer->get_tile_layer()->get_map_tile_matrix().size() && i>=0 && i<(int)_display_layer->get_tile_layer()->get_map_tile_matrix()[0].size()) {
				unit_container = _display_layer->get_tile_layer()->get_map_tile_matrix()[j][i]->get_unit_container();

				for(k=0;k<unit_container.get_number_t();k++) {
					if(unit_container.get_t(k)->getPlayer()==_main_player && unit_container.get_t(k)->test_point_in_moveable(point)) {
						unit_selected = unit_container.get_t(k);
						break;
					}
				}
			}
		}
	}

	if(unit_selected) {
		for(i=0;i<_main_player->get_number_unit_selected();) {
			if(_main_player->get_unit_selected(i)!=unit_selected) {
				_main_player->remove_unit_selected(_main_player->get_unit_selected(i));
			}
			else {
				unit_already_selected=true;
				i++;
			}
		}

		if(!unit_already_selected) _main_player->add_unit_selected(unit_selected);
	}
}

void Game::mouse_left_button_up( int x, int y ) {
	_mouse_button_left_down=false;
	vector<Unit *> unit_selected;
	vector<Unit *>::iterator it;
	int i;
	if(_selection_zone_enable) {
		unit_selected = _selectionZone->get_list_unit();
		for(it=unit_selected.begin();it!=unit_selected.end();) {
			if((*it)->getPlayer()!=_main_player) unit_selected.erase(it);
			else it++;
		}

		if(unit_selected.size()>0) {
			for(i=0;i<_main_player->get_number_unit_selected();) {
				if( std::find(unit_selected.begin(), unit_selected.end(), _main_player->get_unit_selected(i)) == unit_selected.end() ) {
					_main_player->remove_unit_selected(_main_player->get_unit_selected(i));
				}
				else i++;
			}
			for(i=0;i<(int)unit_selected.size();i++) {
				if(!_main_player->test_unit_selected(unit_selected[i])) {
					_main_player->add_unit_selected(unit_selected[i]);
				}
			}
		}

		_selection_zone_enable=false;
		_selectionZone->setP1(CCPoint(0,0));
		_selectionZone->setP2(CCPoint(0,0));
		_selectionZone->update();
	}
}

void Game::mouse_right_button_down( int x, int y ) {
	CCPoint map_point;
	Container<Unit> unit_container;
	int i;

	//le hud va de (27,0) a (452,100) en coordonnee cocos
	
	if(y<520) {

		map_point = convert_opengl_point_to_map_point(x,y);

		for(i=0;i<_main_player->get_number_unit_selected();i++) {
			_main_player->get_unit_selected(i)->set_destination(map_point.x,map_point.y);
		}
	}
}

void Game::mouse_move( int x, int y) {
	CCPoint point;
	if(_mouse_button_left_down) {
		point = convert_opengl_point_to_map_point(x,y);
		if(_selection_zone_enable) {
			_selectionZone->setP2(point);
			_selectionZone->update();
		}
		else {
			_selection_zone_enable=true;
			_selectionZone->setP1(point);
			_selectionZone->setP2(point);
			_selectionZone->update();
		}
	}

	if(x<50) _scroll_left_mouse = true;
	else _scroll_left_mouse = false;

	if(x>EGLView::sharedOpenGLView()->getViewPortRect().getMaxX()-114) _scroll_right_mouse = true;
	else _scroll_right_mouse = false;

	if(y<50) _scroll_up_mouse = true;
	else _scroll_up_mouse = false;

	if(y>EGLView::sharedOpenGLView()->getViewPortRect().getMaxY()-50) _scroll_down_mouse = true;
	else _scroll_down_mouse = false;
}

void Game::key_press(int key) {
	if(key==GLFW_KEY_LEFT) _scroll_left_key=true;
	else if(key==GLFW_KEY_RIGHT) _scroll_right_key=true;
	else if(key==GLFW_KEY_UP) _scroll_up_key=true;
	else if(key==GLFW_KEY_DOWN) _scroll_down_key=true;
	else if(key=='D') {
		if(_display_layer->get_debug_mode()) _display_layer->set_debug_mode(false);
		else _display_layer->set_debug_mode(true);
	}
	else if(key==GLFW_KEY_ESC) {
		while(_main_player->get_number_unit_selected()!=0) {
			_main_player->remove_unit_selected(_main_player->get_unit_selected(0));
		}
	}
	else if(key==GLFW_KEY_LALT) {
		_key_left_alt=true;
		set_bar_visible(true);
	}
	else if(key==GLFW_KEY_RALT) {
		_key_right_alt=true;
		set_bar_visible(true);
	}
}

void Game::key_release(int key) {
	if(key==GLFW_KEY_LEFT) _scroll_left_key=false;
	else if(key==GLFW_KEY_RIGHT) _scroll_right_key=false;
	else if(key==GLFW_KEY_UP) _scroll_up_key=false;
	else if(key==GLFW_KEY_DOWN) _scroll_down_key=false;
	else if(key==GLFW_KEY_LALT) {
		_key_left_alt=false;
		if(!_key_right_alt) set_bar_visible(false);
	}
	else if(key==GLFW_KEY_RALT) {
		_key_right_alt=false;
		if(!_key_left_alt) set_bar_visible(false);
	}
}

void Game::mouse_wheel_up(int opengl_x, int opengl_y) {
	CCPoint map_point, screen_point;
	if(_display_layer->getScale()<1) {
		map_point = convert_opengl_point_to_map_point(opengl_x,opengl_y);
		_display_layer->setScale(_display_layer->getScale()+0.05);
		set_map_point_to_opengl_point(map_point,opengl_x,opengl_y);
	}
}

void Game::mouse_wheel_down(int opengl_x, int opengl_y) {
	if(_display_layer->getScale()>0.1)
		_display_layer->setScale(_display_layer->getScale()-0.05);
}

void Game::set_bar_visible(bool visible) {
	UnitLayer * unit_layer = _display_layer->get_unit_layer();
	int i;
	for(i=0;i<unit_layer->get_number_unit();i++) {
		unit_layer->get_unit(i)->set_bar_visible(visible);
	}
}

