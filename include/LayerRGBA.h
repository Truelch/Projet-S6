#ifndef LAYERRGBA_H
#define LAYERRGBA_H

#include "cocos2d.h"
#include <vector>
//#include "Displayable.h"

class Game;
class Displayable;

USING_NS_CC;

class LayerRGBA : public cocos2d::CCLayerRGBA
{
	public:

		LayerRGBA();
		LayerRGBA(Game * game);

		virtual bool init();

		// --- GET ---
		
		Game * get_game() { return _game; }
		//std::vector<Displayable *> get_displayable_list() { return _displayable_list; }
		
		// --- SET ---
		
		void set_game(Game * game) { _game = game; }
	
	private:
		Game * _game;
		//std::vector<Displayable *> _displayable_list;
};

#endif
