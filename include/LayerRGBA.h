#ifndef LAYERRGBA_H
#define LAYERRGBA_H

#include "cocos2d.h"
#include <vector>
#include "Displayable.h"

class Scene;

USING_NS_CC;

class LayerRGBA : public cocos2d::CCLayerRGBA
{
	public:

		LayerRGBA();
		LayerRGBA(Scene * scene);

		virtual bool init();

		// --- GET ---
		
		Scene * get_scene() { return _scene; }
		//std::vector<Displayable *> get_displayable_list() { return _displayable_list; }
		
		// --- SET ---
		
		void set_scene(Scene * scene) { _scene = scene; }
	
	private:
		Scene * _scene;
		//std::vector<Displayable *> _displayable_list;
};

#endif
