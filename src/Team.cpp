#include "Team.h"

Team::Team()
{
	
}

// --- METHODES ---

Player * Team::get_player(int index) 
{
	if(index<(int)_player_list.size()) return _player_list[index];
	else return NULL;
}

void Team::add_player(Player * player) 
{
	//Pas besoin car Player n'hérite pas d'une classe de cocos2d fonctionnant avec des child
	//addChild(unit->getSprite());
	_player_list.push_back(player);
}

void Team::remove_player(int index) 
{
	if(index<(int)_player_list.size()) 
	{
		vector<Player *>::iterator it = _player_list.begin()+index;
		delete (*it);
		_player_list.erase(it);
	}
}

int Team::get_number_player() 
{
	return (int)(_player_list.size());
}
