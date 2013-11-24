#ifndef LAYER_H
#define LAYER_H

#include "cocos2d.h"
#include <vector>
#include "Displayable.h"

#include "EventReceiver.h"

class Scene;

USING_NS_CC;

class Layer : public cocos2d::CCLayer
{
	public:

		Layer();
		Layer(Scene * scene);
		virtual ~Layer();

		virtual bool init();

		// a selector callback
		void menuCloseCallback(CCObject* pSender);

		virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
		virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
		virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
		virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event);
		
		// --- GET ---
		
		Scene * get_scene() { return _scene; }
		std::vector<Displayable *> get_displayable_list() { return _displayable_list; }
		
		// --- SET ---
		
		void set_scene(Scene * scene) { _scene = scene; }
	
	private:
		Scene * _scene;
		std::vector<Displayable *> _displayable_list;
};

#endif
