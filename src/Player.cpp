#include "Player.h"

#include "DisplayLayer.h"
#include "EventHandler.h"
#include "FogOfWarDisplayable.h"
#include "FogOfWarLayer.h"
#include "TileLayer.h"
#include "Unit.h"
#include "Building.h"
#include "HudItem.h"

Player::Player(): EventReceiver(), _game(NULL)
{
	init();
	//Boucle pour trouver le QG
}

Player::Player(Game * game, string name, Color color, int player_number, int team_number):EventReceiver(game->getEventHandler()), _name(name), _color(color), _player_number(player_number), _team_number(team_number), _game(game)
{
	init();
	//Boucle pour trouver le QG
}

void Player::init() {
	unsigned int i,j;

	for(j=0; j<get_game()->get_display_layer()->get_tile_layer()->get_map_tile_matrix().size();j++) {
		_map_tile_info.push_back(std::vector<TileInfo>());
		for(i=0; i<get_game()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[j].size();i++) {
			_map_tile_info[j].push_back({false,false,Container<Unit>()});
		}
	}
}

// --- GET ---

string Player::get_name()
{
	return _name;
}

Player::Color Player::get_color()
{
	return _color;
}

int Player::get_player_number()
{
	return _player_number;
}

int Player::get_team_number()
{
	return _team_number;
}

Container<Unit>& Player::get_unit_container()
{
	return _unit_container;
}

std::vector<Container<Unit> >&	Player::get_control_group_vector()
{
	return _control_group_vector;
}

Game * Player::get_game()
{
	return _game;
}

std::vector<Building *>& Player::get_building_vector()
{
	return _building_vector;
}

Building * Player::get_hq()
{
	return _hq;
}

// --- SET ---

void Player::set_name(string name)
{
	_name = name;
}

void Player::set_color(Color color)
{
	_color = color;
}

void Player::set_player_number(int player_number)
{
	_player_number = player_number;
}

void Player::set_team_number(int team_number)
{
	_team_number = team_number;
}

void Player::set_hq(Building * hq)
{
	_hq = hq;
}

void Player::set_resources(int resources)
{
	_resources = resources;
}

// --- METHODES ---

float Player::compute_percent_of_known_map()
{
	float percent_of_known_map = 0.0;
	//Calcul
	return percent_of_known_map;
}

int Player::compute_number_player_building()
{
	int number_player_building = 0;
	//Calcul
	
	return number_player_building;
}

bool Player::is_ally(Player * player)
{
	bool ally = true;
	//Boucle de vérification
	return ally;
}

void Player::on_unit_destroyed(Unit * unit) {
	unsigned int i;
	int x,y;
	if(unit->getPlayer()==this) {
		const vector<MapTile *>& range_map_tile_list = unit->get_range_map_tile_list();
		for(i=0; i<range_map_tile_list.size(); i++) {
			x = range_map_tile_list[i]->get_tile_x();
			y = range_map_tile_list[i]->get_tile_y();
			if(_map_tile_info[y][x].range_unit_list.get_number_t()==0 && _map_tile_info[y][x].visible) {
				_map_tile_info[y][x].visible=false;
				get_game()->getEventHandler()->on_player_unrange_tile(x,y,this);
			}
		}
	}
}

void Player::on_unit_range_tile(int x, int y, Unit * unit) {
	if(unit->getPlayer()==this) {
		_map_tile_info[y][x].range_unit_list.add_t(unit);
		if(_map_tile_info[y][x].discovered==false) {
			_map_tile_info[y][x].discovered=true;
			get_game()->getEventHandler()->on_player_discovered_tile(x,y,this);
		}
		if(_map_tile_info[y][x].visible==false) {
			_map_tile_info[y][x].visible=true;
			get_game()->getEventHandler()->on_player_range_tile(x,y,this);
		}
	}
}

void Player::on_unit_unrange_tile(int x, int y, Unit * unit) {
	if(unit->getPlayer()==this) {
		_map_tile_info[y][x].range_unit_list.remove_t(unit);
		if(_map_tile_info[y][x].range_unit_list.get_number_t()==0 && _map_tile_info[y][x].range_building_list.size()==0 && _map_tile_info[y][x].visible) {
			_map_tile_info[y][x].visible=false;
			get_game()->getEventHandler()->on_player_unrange_tile(x,y,this);
		}
	}
}

void Player::remove_unit_selected(Unit * unit) {
	if(_unit_selected.contain_t(unit)) {
		unit->set_selected(false);
		_unit_selected.remove_t(unit);
	}
}

void Player::add_unit_selected(Unit * unit) {
	if(unit->getPlayer()==this && !_unit_selected.contain_t(unit)) {
		unit->set_selected(true);
		_unit_selected.add_t(unit);
	}
}

void Player::update(float dt)
{
	//Ajout de ressources
	int nbr_source = count_building_type("Source");
	float coeff = 1.0; //Variable d'ajustement
	set_resources(_resources+coeff*dt*(float)nbr_source);
	//Supply
	//Théoriquement, seule la RAM augmente le supply, mais bon
		
}

int Player::count_building_type(string name)
{
	//Renvoie un entier égal au nombre de bâtiments dont le nom est identique à celui donné en paramètre.
	int /*i, */count = 0;
	//Encore un problème entre le i et la size()
	/*for(i = 0 ; i < _building_vector.size() ; i++)
	{
		if (_building_vector[i]->get_name()==name)
		{
			count+=1;
		}
	}*/
	return count;
}

int Player::supply_provided()
{
	//Renvoie un entier égal à la somme de tous les supply fournis par tous les bâtiments du joueur
	int /*i, */supply = 0;
	//Encore un problème entre le i et la size()
	/*for(i = 0 ; i < _building_vector.size() ; i++)
	{
		//Ne pas vérifier que la RAM
		supply+=_building_vector[i]->get_supply();
	}*/
	return supply;
}

void Player::on_player_range_tile(int x, int y, Player * player) {
	if(get_game()->get_main_player()==this && player==this) {
		get_game()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[y][x]->set_fogStatus(FogOfWarDisplayable::visible);
	}
}

void Player::on_player_unrange_tile(int x, int y, Player * player) {
	if(get_game()->get_main_player()==this && player==this) {
		get_game()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[y][x]->set_fogStatus(FogOfWarDisplayable::unvisible);
	}
}

void Player::on_building_change_player(Building * building, Player * old_player, Player * new_player) {
	int x,y;
	vector<MapTile *> range_map_tile_list=building->get_range_map_tile_list();
	vector<MapTile *>::iterator it;
	if(old_player==this) {
		for(it=range_map_tile_list.begin();it!=range_map_tile_list.end();it++) {
			x = (*it)->get_tile_x();
			y = (*it)->get_tile_y();
			_map_tile_info[y][x].range_building_list.erase(std::remove(_map_tile_info[y][x].range_building_list.begin(), _map_tile_info[y][x].range_building_list.end(), building), _map_tile_info[y][x].range_building_list.end());
			if(_map_tile_info[y][x].range_unit_list.get_number_t()==0 && _map_tile_info[y][x].range_building_list.size()==0 && _map_tile_info[y][x].visible) {
				_map_tile_info[y][x].visible=false;
				get_game()->getEventHandler()->on_player_unrange_tile(x,y,this);
			}
		}
	}
	if(new_player==this) {
		for(it=range_map_tile_list.begin();it!=range_map_tile_list.end();it++) {
			x = (*it)->get_tile_x();
			y = (*it)->get_tile_y();
			if(std::find(_map_tile_info[y][x].range_building_list.begin(), _map_tile_info[y][x].range_building_list.end(), building) == _map_tile_info[y][x].range_building_list.end()) {
				_map_tile_info[y][x].range_building_list.push_back(building);
			}
			if(_map_tile_info[y][x].discovered==false) {
				_map_tile_info[y][x].discovered=true;
				get_game()->getEventHandler()->on_player_discovered_tile(x,y,this);
			}
			if(_map_tile_info[y][x].visible==false) {
				_map_tile_info[y][x].visible=true;
				get_game()->getEventHandler()->on_player_range_tile(x,y,this);
			}
		}
	}
}
