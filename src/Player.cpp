#include "Player.h"

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

std::vector<Container<Unit>>&	Player::get_control_group_vector()
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
