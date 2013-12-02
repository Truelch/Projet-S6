#ifndef LAYER_H
#define LAYER_H

#include "cocos2d.h"
#include <vector>
#include "Displayable.h"

#include "EventReceiver.h"

class Game;

USING_NS_CC;

class Layer : public cocos2d::CCLayer
{
	public:

		Layer();
		Layer(Game * game);
		virtual ~Layer();

		// --- GET ---
		
		Game * get_game() { return _game; }
		std::vector<Displayable *> get_displayable_list() { return _displayable_list; }
		
		// --- SET ---
		
		void set_game(Game * game) { _game = game; }
	
	private:
		Game * _game;
		std::vector<Displayable *> _displayable_list;
};

#endif
