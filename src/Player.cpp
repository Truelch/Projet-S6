#include "Player.h"

Player::Player(): EventReceiver(), _scene(NULL)
{
	//
}

Player::Player(Scene * scene, string name, Color color, int player_number, int team_number):EventReceiver(scene->getEventHandler()), _name(name), _color(color), _player_number(player_number), _team_number(team_number), _scene(scene)
{
	//
}

// --- METHODES ---

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

UnitContainer& Player::get_unit_container()
{
	return _unit_container;
}

std::vector<UnitContainer>&	Player::get_control_group_vector()
{
	return _control_group_vector;
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
