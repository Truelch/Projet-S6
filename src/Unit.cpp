
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

Unit::Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float groundFixture, float density, const char * filename, Game * game, Layer * layer, string name, 
			float hp, float hp_max, float hp_regen, float power, float power_max, float power_regen, float armor, float prod_time, Player * player, float sight/*,
			float rotation, const char * turret_filename, float x_relative, float y_relative, float missile_speed, const char */): 
			Moveable(x, y, x_dest, y_dest, rotation, move_speed, 22.4f, groundFixture, density, filename, game, layer), _player(player), _selected(false), _bar_visible(false)
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

	player->get_unit_container().add_t(this);
	_bar = new Bar(game, layer, x, y+20, (float)hp/hp_max, 100, 10, ccc4(0,255,0,255), ccc4(255,0,0,255));
	//Tourelle
	//_turret = new Turret(0, turret_filename, game, layer, x_relative, y_relative, missile_speed, missile_filename, damage, cooldown, range_max, this);
	//Comme il y a une liste de tourelle, ne pas les instancier ici

	_tile_x=-1;
	_tile_y=-1;
}

Unit::~Unit() {
	_player->set_losses(_player->get_losses()+1);
	//Ajouter kill pour le tueur
	delete _bar;
	Container<Unit>::on_destroyed(this);
	getLayer()->removeChild(getPhysicsSprite());
	getGame()->getEventHandler()->on_unit_destroyed(this);
}

void Unit::updateCoordonates() {
	Moveable::updateCoordonates();

	int old_tile_x=_tile_x;
	int old_tile_y=_tile_y;
	_tile_x=get_tile_x();
	_tile_y=get_tile_y();

	if(old_tile_x!=_tile_x || old_tile_y!=_tile_y) {
		if(old_tile_x!=-1 && old_tile_y!=-1) {
			getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[old_tile_y][old_tile_x]->get_unit_container().remove_t(this);
		}
		getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[_tile_y][_tile_x]->get_unit_container().add_t(this);
	}

}

// --- GET ---

AIStat * Unit::get_ai_stat()
{
	return _ai_stat;
}

string Unit::get_name()
{
	return _stat->get_name();
}

float Unit::get_hp()
{
	return _stat->get_hp();
}

float Unit::get_hp_max()
{
	return _stat->get_hp_max();
}

float Unit::get_hp_regen()
{
	return _stat->get_hp_regen();
}

float Unit::get_power()
{
	return _stat->get_power();
}

float Unit::get_power_max()
{
	return _stat->get_power_max();
}

float Unit::get_power_regen()
{
	return _stat->get_power_regen();
}

float Unit::get_armor()
{
	return _stat->get_armor();
}

/*
string Unit::get_type_armor()
{
	return _stat->get_type_armor();
}
*/

float Unit::get_prod_time()
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

void Unit::set_hp(float hp)
{
	//std::cout << "PV restants (avant modif) : " << _stat->get_hp() << ", nouvelle valeur de PV : " << hp << endl;
	if (hp <= 0)
	{
		delete this;
		return;
	}
	_bar->setValue((float)_stat->get_hp()/_stat->get_hp_max());
	_stat->set_hp(hp);
}

void Unit::set_hp_max(float hp_max)
{
	_bar->setValue((float)_stat->get_hp()/_stat->get_hp_max()); //Cast plus nécessaire maintenant non ?
	_stat->set_hp_max(hp_max);
}

void Unit::set_hp_regen(float hp_regen)
{
	_stat->set_hp_regen(hp_regen);
}

void Unit::set_power(float power)
{
	_stat->set_power(power);
}

void Unit::set_power_max(float power_max)
{
	_stat->set_power_max(power_max);
}

void Unit::set_power_regen(float power_regen)
{
	_stat->set_power_regen(power_regen);
}

void Unit::set_armor(float armor)
{
	_stat->set_armor(armor);
}

/*
void Unit::set_armor_type(string type_armor)
{
	_stat->set_armor_type(type_armor);
}
*/

void Unit::set_prod_time(float prod_time)
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


// --- METHODES ---


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

void Unit::on_displayable_contact(Displayable * displayableA, Displayable * displayableB)
{
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

void Unit::update(float dt) 
{
	Moveable::update(dt);

	_bar->getSprite()->setPositionX(getSprite()->getPositionX());
	_bar->getSprite()->setPositionY(getSprite()->getPositionY()+20);

	update_range_map_tile_list();
	//
	vector<Turret *>::iterator it;
	for(it=_turret_list.begin(); it!=_turret_list.end();it++) 
	{
		(*it)->update(dt);
	}
	//Régénération
	if(_stat->get_hp() < _stat->get_hp_max())
	{
<<<<<<< HEAD
=======
		//std::cout << "Régénération (hp = " << _stat->get_hp() << "/" << _stat->get_hp_max() << ") + " << dt*_stat->get_hp_regen() << std::endl;
>>>>>>> d0ff0e705070019832aa00dfa6b5226c7f9de1db
		if(_stat->get_hp()+dt*_stat->get_hp_regen() < _stat->get_hp_max())
		{
			set_hp(_stat->get_hp()+dt*_stat->get_hp_regen());
		}
		else
		{
			set_hp(_stat->get_hp_max());
		}
	}
}

bool Unit::map_tile_range(MapTile * map_tile)
{
	return getSprite()->getPosition().getDistance(map_tile->getSprite()->getPosition())<_stat->get_sight();
}

/*void Unit::check_attack()
{
	
	int i = 0;
	float distance = get_stat()->get_range_max(); //hors de portée => valeur infinie
	float delta_x, delta_y;
	//Pour accéder aux container d'unités !	
	for(i = 0 ; i < _player->get_scene()->get_display_layer()->get_unit_layer()->get_number_unit() ; i++) //Ici
	{
		i.check_attack();
	}
	
}*/

void Unit::add_turret(float rotation, const char * filename, Game * game, Layer * layer, float x_relative, float y_relative, float missile_speed, const char * missile_filename, int damage, float cooldown, float range_max, Unit * shooter_unit) 
{
	_turret_list.push_back(new Turret(rotation, filename, game, layer, x_relative, y_relative, missile_speed, missile_filename, damage, cooldown, range_max, shooter_unit));
	getSprite()->addChild(*(_turret_list.end()-1));
}
