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
#include "UnitLayer.h"
#include "ContactListener.h"
#include "Building.h"
#include "Missile.h"
#include "HudLayer.h"
#include "HudItem.h"

#include "TileLayer.h"
#include "BuildingLayer.h"
#include "MissileLayer.h"
#include "SelectionZone.h"
#include "Cursor.h"
#include "EventHandler.h"

USING_NS_CC;

using namespace std;

Game::Game(): Scene(), _scroll_left_mouse(false), _scroll_right_mouse(false), _scroll_up_mouse(false), _scroll_down_mouse(false), _scroll_left_key(false), _scroll_right_key(false), _scroll_up_key(false), _scroll_down_key(false), _mouse_button_left_down(false), _key_left_alt(false), _key_right_alt(false), _selection_zone_enable(false), _mouse_x(0), _mouse_y(0), _old_x(0), _old_y(0), _mouse_initiate(false), _hud_item_mouse(NULL)
{
	int i =0;
	std::cout << "Constructeur de Game" << std::endl;
	_display_layer = new DisplayLayer(this);
	if(_display_layer->init_file(CCFileUtils::sharedFileUtils()->getSearchPaths()[0]+"../map/map1")==EXIT_FAILURE) {
		std::cerr << "ERREUR : fichier map invalide" << std::endl;
	}
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
	//Amis
	int a = 3;
	for(i=0;i<a;i++)
	{
		_display_layer->coordonate_tile_to_cocos2dx(2*i+5,10,x,y);
		_display_layer->get_unit_layer()->add_unit(x,y,x,y,0,5,5.0f,1.0f,"units/model_tank_00.png", "tank",100,100,1.0,100,100,1.0,6.0,100, _player_list[0],600);
		_display_layer->get_unit_layer()->get_unit(i)->add_turret(0,"units/turret_tank_00.png", this, _display_layer->get_missile_layer(), /*-3.0, 8.0,*/0.0,0.0,
					50.0,"missiles/01.png", 12, 1.3, 250.0,_display_layer->get_unit_layer()->get_unit(i));
	}
	
	//Ennemis
	for(i=0;i<a;i++)
	{
		_display_layer->coordonate_tile_to_cocos2dx(2*i+5,20,x,y);
		_display_layer->get_unit_layer()->add_unit(x,y,x,y,-90,5,5.0f,1.0f,"units/model_tank_01.png", "tank",100,100,1.0,100,100,1.0,6.0,100, _player_list[1],600);
		_display_layer->get_unit_layer()->get_unit(i+a)->add_turret(0,"units/turret_tank_01.png", this, _display_layer->get_missile_layer(), 0, 0, 
					50.0,"missiles/02.png", 12, 1.3, 250.0,_display_layer->get_unit_layer()->get_unit(i+a));
	}
	/*
	_display_layer->get_unit_layer()->add_unit(400,200,400,200,-90,5,5.0f,1.0f,"units/tank01.png", "tank",100,100,100,100,100,100,100,100, _player_list[0],200);
	_display_layer->get_unit_layer()->add_unit(100,200,100,200,-90,5,5.0f,1.0f,"units/tank01.png", "tank",100,100,100,100,100,100,100,100, _player_list[1],100);
	*/
	
	/*
	float x2,y2;
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

	_hud_layer = new HudLayer(this,"hud.png");
	_hud_layer->setZOrder(2);
	addChild(_hud_layer);

	_hud_layer->add_hud_item(381,607,"widgets/stop.png",HudItem::stopButtonType);

	//_hud = new Hud(256,180,"hud.png", this, _hud_layer);
	
	_cursor_layer = new Layer(this);
	_cursor_layer->setZOrder(3);
	addChild(_cursor_layer);
	_cursor = new Cursor(0,0,"fleche.png",this,_cursor_layer);

	this->schedule( schedule_selector( Game::update ), 1.0 / 30 );	

	std::cout << CCFileUtils::sharedFileUtils()->getSearchPaths()[1] << std::endl;
}

Game::~Game() {
	delete _contactListener;
	delete _display_layer;
	delete _hud_layer;
	delete _cursor_layer;
	delete _cursor;
}

// --- SET ---

void Game::set_time_elapsed(float time_elapsed)
{
	_time_elapsed = time_elapsed;
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


// --- METHODES ---

void Game::update(float dt)
{
	int i;
	float x,y,z,n;
	CCSize size;
	float vitesse_scroling=(300.0/_display_layer->getScale())*dt;

	if(_scroll_left_mouse || _scroll_left_key) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		n=x-vitesse_scroling;
		check_out_of_map_whith_new_scrolling(n,y);
		_display_layer->getCamera()->setCenterXYZ(n,y,z);
		_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
		_display_layer->getCamera()->setEyeXYZ(n,y,z);
	}
	if(_scroll_right_mouse || _scroll_right_key) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		n=x+vitesse_scroling;
		check_out_of_map_whith_new_scrolling(n,y);
		_display_layer->getCamera()->setCenterXYZ(n,y,z);
		_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
		_display_layer->getCamera()->setEyeXYZ(n,y,z);
	}
	if(_scroll_up_mouse || _scroll_up_key) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		n=y+vitesse_scroling;
		check_out_of_map_whith_new_scrolling(x,n);
		_display_layer->getCamera()->setCenterXYZ(x,n,z);
		_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
		_display_layer->getCamera()->setEyeXYZ(x,n,z);
	}
	if(_scroll_down_mouse || _scroll_down_key) {
		_display_layer->getCamera()->getCenterXYZ(&x,&y,&z);
		n=y-vitesse_scroling;
		check_out_of_map_whith_new_scrolling(x,n);
		_display_layer->getCamera()->setCenterXYZ(x,n,z);
		_display_layer->getCamera()->getEyeXYZ(&x,&y,&z);
		_display_layer->getCamera()->setEyeXYZ(x,n,z);
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

void Game::get_center_of_screen(int& x, int& y) {
	CCSize frame_size = EGLView::sharedOpenGLView()->getFrameSize();
	x=(frame_size.width)/2;
	y=(frame_size.height)/2;
}

void Game::set_point_to_center_of_screen(CCPoint point) {
	int x,y;
	get_center_of_screen(x,y);
	set_map_point_to_opengl_point(point, x, y);
}

bool Game::check_out_of_map_whith_new_scrolling(float& offset_x, float& offset_y) {
	int opengl_x, opengl_y;
	float cocos_x, cocos_y;
	bool out_of_scrolling=false;

	get_center_of_screen(opengl_x, opengl_y);
	coordinateOpenglToCocos2dx(opengl_x, opengl_y, cocos_x, cocos_y);
	CCPoint point = convert_opengl_point_to_layer_point_with_new_offset(opengl_x, opengl_y, _display_layer, offset_x, offset_y);

	if(point.x<_display_layer->get_tile_layer()->get_min_x()) {
		offset_x=_display_layer->get_tile_layer()->get_min_x()-cocos_x;
		out_of_scrolling=true;
	}
	else if(point.x>_display_layer->get_tile_layer()->get_max_x()) {
		offset_x=_display_layer->get_tile_layer()->get_max_x()-cocos_x;
		out_of_scrolling=true;
	}
	if(point.y<_display_layer->get_tile_layer()->get_min_y()) {
		offset_y=_display_layer->get_tile_layer()->get_min_y()-cocos_y;
		out_of_scrolling=true;
	}
	else if(point.y>_display_layer->get_tile_layer()->get_max_y()) {
		offset_y=_display_layer->get_tile_layer()->get_max_y()-cocos_y;
		out_of_scrolling=true;
	}

	return out_of_scrolling;
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

	check_out_of_map_whith_new_scrolling(new_offset.x, new_offset.y);

	_display_layer->getCamera()->getCenterXYZ(&offset_x,&offset_y,&offset_z);
	_display_layer->getCamera()->setCenterXYZ(new_offset.x,new_offset.y,offset_z);
	_display_layer->getCamera()->getEyeXYZ(&offset_x,&offset_y,&offset_z);
	_display_layer->getCamera()->setEyeXYZ(new_offset.x,new_offset.y,offset_z);
}

CCPoint Game::convert_opengl_point_to_layer_point_with_new_offset(int opengl_x, int opengl_y, Layer * layer, float offset_x, float offset_y) {
	CCPoint map_point;
	float cocos_x, cocos_y;
	CCSize frameSize = EGLView::sharedOpenGLView()->getFrameSize();

	opengl_x=frameSize.width/2+((opengl_x-frameSize.width/2)/layer->getScaleX());
	opengl_y=frameSize.height/2+((opengl_y-frameSize.height/2)/layer->getScaleY());

	coordinateOpenglToCocos2dx(opengl_x,opengl_y,cocos_x,cocos_y);

	map_point.x = cocos_x+offset_x;
	map_point.y = cocos_y+offset_y;

	return map_point;
}

CCPoint Game::convert_opengl_point_to_layer_point(int opengl_x, int opengl_y, Layer * layer) {
	float offset_x,offset_y,offset_z;
	layer->getCamera()->getCenterXYZ(&offset_x,&offset_y,&offset_z);

	return convert_opengl_point_to_layer_point_with_new_offset(opengl_x, opengl_y, layer, offset_x, offset_y);
}

void Game::mouse_left_button_down() {
	int tile_x, tile_y, i,j,k;
	CCPoint point;
	Unit * unit_selected = NULL;
	Container<Unit> unit_container;
	bool unit_already_selected=false;
	CCSize size;
	CCPoint pos;

	_mouse_button_left_down=true;

	if(_mouse_y<520) {
		point = convert_opengl_point_to_layer_point(_mouse_x,_mouse_y,_display_layer);
		_display_layer->coordonate_cocos2dx_to_tile(point.x, point.y, tile_x, tile_y);

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
	else {
		point = convert_opengl_point_to_layer_point(_mouse_x,_mouse_y,_hud_layer);
		for(i=0;i<_hud_layer->get_number_hud_item();i++) {
			size = _hud_layer->get_hud_item(i)->getSprite()->getTextureRect().size;
			pos = _hud_layer->get_hud_item(i)->getSprite()->getPosition();
			if(_hud_layer->get_hud_item(i)->containsPoint(point)) {
				_hud_item_mouse=_hud_layer->get_hud_item(i);
				break;
			}
		}
	}
}

void Game::mouse_left_button_up() {
	_mouse_button_left_down=false;
	vector<Unit *> unit_selected;
	vector<Unit *>::iterator it;
	int i;
	CCPoint point;
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

	point = convert_opengl_point_to_layer_point(_mouse_x,_mouse_y,_hud_layer);
	if(_hud_item_mouse && _hud_item_mouse->containsPoint(point)) {
		getEventHandler()->on_hud_item_clicked(_hud_item_mouse);
	}
	_hud_item_mouse=NULL;
}

void Game::mouse_right_button_down() {
	CCPoint map_point;
	Container<Unit> unit_container;
	int i;

	//le hud va de (27,0) a (452,100) en coordonnee cocos
	
	if(_mouse_y<520) {

		map_point = convert_opengl_point_to_layer_point(_mouse_x,_mouse_y,_display_layer);

		for(i=0;i<_main_player->get_number_unit_selected();i++) {
			_main_player->get_unit_selected(i)->set_destination(map_point.x,map_point.y);
		}
	}
}

void Game::mouse_move( int x, int y) {
	CCSize frameSize = EGLView::sharedOpenGLView()->getFrameSize();
	if(_mouse_initiate) {
		_mouse_x+=x-_old_x;
		_mouse_y+=y-_old_y;
	}
	else {
		_mouse_x=x;
		_mouse_y=y;
		_mouse_initiate=true;
	}
	_old_x=x;
	_old_y=y;
	if(_mouse_x<0) _mouse_x=0;
	else if(_mouse_x>frameSize.width) _mouse_x=frameSize.width;
	if(_mouse_y<0) _mouse_y=0;
	else if(_mouse_y>frameSize.height) _mouse_y=frameSize.height;


	CCPoint point;
	if(_mouse_button_left_down) {
		point = convert_opengl_point_to_layer_point(_mouse_x,_mouse_y,_display_layer);
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

	point = convert_opengl_point_to_layer_point(_mouse_x,_mouse_y,_cursor_layer);
	point.x+=_cursor->getSprite()->getTextureRect().size.width/2.0;
	point.y-=_cursor->getSprite()->getTextureRect().size.height/2.0;
	_cursor->getSprite()->setPosition(point);

	if(_mouse_x<10) _scroll_left_mouse = true;
	else _scroll_left_mouse = false;

	if(_mouse_x>EGLView::sharedOpenGLView()->getViewPortRect().getMaxX()-74) _scroll_right_mouse = true;
	else _scroll_right_mouse = false;

	if(_mouse_y<10) _scroll_up_mouse = true;
	else _scroll_up_mouse = false;

	if(_mouse_y>EGLView::sharedOpenGLView()->getViewPortRect().getMaxY()-10) _scroll_down_mouse = true;
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
	else if(key=='Q') CCDirector::sharedDirector()->end();
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

void Game::mouse_wheel_up() {
	CCPoint map_point, screen_point;
	if(_display_layer->getScale()<1) {
		map_point = convert_opengl_point_to_layer_point(_mouse_x,_mouse_y,_display_layer);
		_display_layer->setScale(_display_layer->getScale()+0.05);
		set_map_point_to_opengl_point(map_point,_mouse_x,_mouse_y);
	}
}

void Game::mouse_wheel_down() {
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

