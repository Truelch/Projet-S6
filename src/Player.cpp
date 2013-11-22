#include "Player.h"

Player::Player()
{
	//
}

Player::Player(string name, string color, int player_number, int team_number): _name(name), _color(color), _player_number(player_number), _team_number(team_number)
{
}

// --- METHODES ---

// --- GET ---

string Player::get_name()
{
	return _name;
}

string Player::get_color()
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

// --- SET ---

void Player::set_name(string name)
{
	_name = name;
}

void Player::set_color(string color)
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
