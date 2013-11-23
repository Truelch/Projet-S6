#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <vector>

#include "Player.h"

using namespace std;

class Team
{
	public:
		Team();
		
		// --- GET ---
		//vector<Player *> get_player_list(); //On devrait ne pas l'utiliser
		
		// --- SET ---

		// --- METHODES ---
		Player * get_player(int index);
		void     add_player(Player * player);
		void     remove_player(int index);
		int      get_number_player();

		
	private:
		vector<Player *> _player_list;
};

#endif
