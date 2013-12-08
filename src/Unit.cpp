
#include "Unit.h"

#include "Container.h"
#include "Stat.h"
#include "Player.h"
#include "Layer.h"
#include "Game.h"
#include "DisplayLayer.h"
#include "EventHandler.h"
#include "MapTile.h"
#include "TileLayer.h"
#include "Bar.h"

#include <algorithm>

Unit::Unit(): Moveable(), _player(NULL) 
{
	//
}

Unit::Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float groundFixture, float density, const char * filename, Game * game, Layer * layer, string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time, Player * player, float sight): Moveable(x, y, x_dest, y_dest, rotation, move_speed, 0.7f, groundFixture, density, filename, game, layer), _player(player), _selected(false), _bar_visible(false)
{
	_stat = new Stat();
	_stat->set_name(name);
	_stat->set_hp(hp);
	_stat->set_hp_max(hp_max);
	_stat->set_hp_regen(hp_regen);
	_stat->set_power(power);
	_stat->set_power_max(power_max);
	_stat->set_power_regen(power_regen);
	_stat->set_armor(armor);
	_stat->set_prod_time(prod_time);
	_stat->set_sight(sight);

	_bar = new Bar(game, layer, x, y+20, (float)hp/hp_max, 100, 10, ccc4(0,255,0,255), ccc4(255,0,0,255));
}

Unit::~Unit() {
	delete _bar;
	Container<Unit>::on_destroyed(this);
	getLayer()->removeChild(getPhysicsSprite());
	getGame()->getEventHandler()->on_unit_destroyed(this);
}

void Unit::updateCoordonates() {
	static int old_tile_x=-1, old_tile_y=-1;

	Moveable::updateCoordonates();

	if(old_tile_x!=get_tile_x() || old_tile_y!=get_tile_y()) {
		if(old_tile_x!=-1 && old_tile_y!=-1) {
			getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[old_tile_y][old_tile_x]->get_unit_container().remove_t(this);
		}
		getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[get_tile_y()][get_tile_x()]->get_unit_container().add_t(this);
		old_tile_x=get_tile_x();
		old_tile_y=get_tile_y();
	}

}

void Unit::update_range_map_tile_list() {
	vector<MapTile *>::iterator it;
	for( it=_range_map_tile_list.begin(); it!=_range_map_tile_list.end();  ) {
		if(map_tile_range(*it)) it++;
		else {
			getGame()->getEventHandler()->on_unit_unrange_tile((*it)->get_tile_x(),(*it)->get_tile_y(),this);
			_range_map_tile_list.erase(it);
		}
	}

	CCPoint position = getSprite()->getPosition();
	int tile_x, tile_y, i,j,k=0;
	MapTile * map_tile;
	bool end=false;
	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(position.x, position.y, tile_x, tile_y);

	while(!end) {
		end=true;
		for(i=tile_x-k;i<tile_x+k+1;i++) {
			for(j=tile_y-k;j<tile_y+k+1;j++) {
				if( ( i==tile_x-k || i==tile_x+k || j==tile_y-k || j==tile_y+k ) && i>=0 && i<getGame()->get_display_layer()->get_map_width() && j>=0 && j<getGame()->get_display_layer()->get_map_height() ) {
					map_tile = getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[j][i];
					if(map_tile_range(map_tile)) {
						end=false;
						if(std::find(_range_map_tile_list.begin(), _range_map_tile_list.end(), map_tile) == _range_map_tile_list.end()) {
							_range_map_tile_list.push_back(map_tile);
							getGame()->getEventHandler()->on_unit_range_tile(i,j,this);
						}
					}
				}
			}
		}
		k+=1;
	}
}

// --- GET ---

AIStat * Unit::get_ai_stat()
{
	return _ai_stat;
}

// --- METHODES ---
void Unit::on_displayable_contact(Displayable * displayableA, Displayable * displayableB) {
	Unit * unit = NULL;
	if(displayableA==this) {
		if(displayableB->getType()==Displayable::unitType) {
			unit = (Unit *)displayableB;
		}
	}
	else if(displayableB==this) {
		if(displayableA->getType()==Displayable::unitType) {
			unit = (Unit *)displayableA;
		}
	}
	if(unit) {
		if(unit->getPlayer()==_player) set_hold_position(false);
		else set_hold_position(true);
	}
	Moveable::on_displayable_contact(displayableA, displayableB);
}

void Unit::update(float dt) {
	Moveable::update(dt);

	_bar->getSprite()->setPositionX(getSprite()->getPositionX());
	_bar->getSprite()->setPositionY(getSprite()->getPositionY()+20);

	update_range_map_tile_list();
}

bool Unit::map_tile_range(MapTile * map_tile) {
	return getSprite()->getPosition().getDistance(map_tile->getSprite()->getPosition())<_stat->get_sight();
}

void Unit::check_attack()
{
	/*
	int i = 0;
	float distance = get_stat()->get_range_max(); //hors de portée => valeur infinie
	float delta_x, delta_y;
	//Pour accéder aux container d'unités !	
	for(i = 0 ; i < _player->get_scene()->get_display_layer()->get_unit_layer()->get_number_unit() ; i++) //Ici
	{
		i.check_attack();
	}
	*/
	vector<Turret *>::iterator it;
	for(it=_turret_list.begin(); it!=_turret_list.end();it++) 
	{
		(*it)->check_attack();
	}
}

string Unit::get_name()
{
	return _stat->get_name();
}

int Unit::get_hp()
{
	return _stat->get_hp();
}

int Unit::get_hp_max()
{
	return _stat->get_hp_max();
}

int Unit::get_hp_regen()
{
	return _stat->get_hp_regen();
}

int Unit::get_power()
{
	return _stat->get_power();
}

int Unit::get_power_max()
{
	return _stat->get_power_max();
}

int Unit::get_power_regen()
{
	return _stat->get_power_regen();
}

int Unit::get_armor()
{
	return _stat->get_armor();
}

string Unit::get_type_armor()
{
	return _stat->get_type_armor();
}

int Unit::get_prod_time()
{
	return _stat->get_prod_time();
}

float Unit::get_sight()
{
	return _stat->get_sight();
}

// --- SET ---

void Unit::set_name(string name)
{
	_stat->set_name(name);
}

void Unit::set_hp(int hp)
{
	_bar->setValue((float)_stat->get_hp()/_stat->get_hp_max());
	_stat->set_hp(hp);
}

void Unit::set_hp_max(int hp_max)
{
	_bar->setValue((float)_stat->get_hp()/_stat->get_hp_max());
	_stat->set_hp_max(hp_max);
}

void Unit::set_hp_regen(int hp_regen)
{
	_stat->set_hp_regen(hp_regen);
}

void Unit::set_power(int power)
{
	_stat->set_power(power);
}

void Unit::set_power_max(int power_max)
{
	_stat->set_power_max(power_max);
}

void Unit::set_power_regen(int power_regen)
{
	_stat->set_power_regen(power_regen);
}

void Unit::set_armor(int armor)
{
	_stat->set_armor(armor);
}

void Unit::set_armor_type(string type_armor)
{
	_stat->set_armor_type(type_armor);
}

void Unit::set_prod_time(int prod_time)
{
	_stat->set_prod_time(prod_time);
}

void Unit::set_sight(float sight)
{
	_stat->set_sight(sight);
}

void Unit::set_selected(bool selected) {
	_selected = selected;
	update_bar_visibility();
}

void Unit::set_bar_visible(bool bar_visible) {
	_bar_visible = bar_visible;
	update_bar_visibility();
}

void Unit::on_player_range_tile(int x, int y, Player * player) {
	Moveable::on_player_range_tile(x,y,player);
	update_bar_visibility();
}

void Unit::on_player_unrange_tile(int x, int y, Player * player) {
	Moveable::on_player_unrange_tile(x,y,player);
	update_bar_visibility();
}

void Unit::update_bar_visibility() {
	if(getSprite()->getScale()!=0 && ( _bar_visible || _selected ) ) _bar->set_visible(true);
	else _bar->set_visible(false);
}


