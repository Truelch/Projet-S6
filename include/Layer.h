#ifndef LAYER
#define LAYER

#include "cocos2d.h"

class Game;

USING_NS_CC;

class Layer : public cocos2d::CCLayer
{
	public:

		Layer();
		Layer(Game * game);

		virtual bool init();

		// a selector callback
		void menuCloseCallback(CCObject* pSender);

		virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
		virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
		virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
		virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event);

		Game * getGame() { return _game; }
		void setGame(Game * game) { _game = game; }
	
	private:
		Game * _game;
};

#endif
