#ifndef SCENE
#define SCENE

#include "cocos2d.h"

class Scene : public cocos2d::CCScene
{
	public:
		virtual void ccTouchesBegan(CCSet* touches, CCEvent* event) = 0;
		virtual void ccTouchesMoved(CCSet* touches, CCEvent* event) = 0;
		virtual void ccTouchesEnded(CCSet* touches, CCEvent* event) = 0;
		virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event) = 0;
};

#endif
