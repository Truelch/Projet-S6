#include "Player.h"

#include "DisplayLayer.h"
#include "EventHandler.h"
#include "FogOfWarDisplayable.h"
#include "FogOfWarLayer.h"
#include "TileLayer.h"
#include "Unit.h"

Player::Player(): EventReceiver(), _game(NULL)
{
	init();
}

Player::Player(Game * game, string name, Color color, int player_number, int team_number):EventReceiver(game->getEventHandler()), _name(name), _color(color), _player_number(player_number), _team_number(team_number), _game(game)
{
	init();
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
			get_game()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[y][x]->set_fogStatus(FogOfWarDisplayable::visible);
			get_game()->getEventHandler()->on_player_range_tile(x,y,this);
		}
	}
}

void Player::on_unit_unrange_tile(int x, int y, Unit * unit) {
	if(unit->getPlayer()==this) {
		_map_tile_info[y][x].range_unit_list.remove_t(unit);
		if(_map_tile_info[y][x].range_unit_list.get_number_t()==0 && _map_tile_info[y][x].visible) {
			_map_tile_info[y][x].visible=false;
			get_game()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[y][x]->set_fogStatus(FogOfWarDisplayable::unvisible);
			get_game()->getEventHandler()->on_player_unrange_tile(x,y,this);
		}
	}
}

