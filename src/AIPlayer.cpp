#include "AIPlayer.h"
#include "AI.h"

AIPlayer::AIPlayer(): Player() 
{
	//std::cout << "Constructeur d'AIPlayer" << std::endl;
}

AIPlayer::AIPlayer(Game * game, string name, Color color, int player_number, int team_number): Player(game, name, color, player_number, team_number)
{
	//std::cout << "Constructeur de Hud" << std::endl;
	_ai = new AI(game, this, AI::d_medium);
}

void AIPlayer::update(float dt)
{
	Player::update(dt);
	_ai->update(dt);
}
