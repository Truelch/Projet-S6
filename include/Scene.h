#ifndef SCENE
#define SCENE

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "EventHandler.h"
#include "DisplayLayer.h"

#define PTM_RATIO 32
#define COEFF     2.1

class Scene : public cocos2d::CCScene
{
	public:
		Scene();
		virtual ~Scene();

		virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event) = 0;
		virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event) = 0;
		virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event) = 0;
		virtual void ccTouchesCancelled(cocos2d::CCSet* touches, cocos2d::CCEvent* event) = 0;

		b2World * getWorld() { return _world; }
		EventHandler * getEventHandler() { return _event_handler; }
		
		//Mon ajout
		virtual DisplayLayer * get_display_layer() = 0;
		
	private:
		EventHandler * _event_handler;
		b2World * _world;
};

#endif
