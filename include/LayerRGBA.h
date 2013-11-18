#ifndef LAYERRGBA_H
#define LAYERRGBA_H

#include "cocos2d.h"
#include <vector>
#include "Displayable.h"

class Scene;

USING_NS_CC;

class LayerRGBA : public cocos2d::CCLayer
{
	public:

		LayerRGBA();
		LayerRGBA(Scene * scene);

		virtual bool init();

		// a selector callback
		//Plus besoin, non ?
		/*
		void menuCloseCallback(CCObject* pSender);

		virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
		virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
		virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
		virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event);
		*/
		// --- GET ---
		
		Scene * get_scene() { return _scene; }
		//std::vector<Displayable *> get_displayable_list() { return _displayable_list; }
		
		// --- SET ---
		
		void set_scene(Scene * scene) { _scene = scene; }
	
	private:
		Scene * _scene;
		//td::vector<Displayable *> _displayable_list;
};

#endif
