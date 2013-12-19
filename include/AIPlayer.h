#ifndef AIPLAYER_H
#define AIPLAYER_H


#include "Player.h"

class AI;

using namespace cocos2d;


class AIPlayer : public Player
{
	public:
		AIPlayer();
		AIPlayer(Game * game, string name, Color color, int player_number, int team_number);
		
		// --- METHODES ---
		virtual void update(float dt);
		
		// --- GET ---
		AI * get_ai() { return _ai; }
		
		// --- SET ---
					
		
	private:	
		// --- ATTRIBUTS ---
		AI * _ai;
};

#endif




