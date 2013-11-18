#include "LayerRGBA.h"

#include "Scene.h"
#include "TileLayer.h"


using namespace std;


LayerRGBA::LayerRGBA(): CCLayerRGBA(), _scene(NULL)
{
	init();
}

LayerRGBA::LayerRGBA(Scene * scene): CCLayerRGBA(), _scene(scene)
{
	init();
}

bool LayerRGBA::init()
{
	if( !CCLayer::init() ) {
		return false;
	}
	//Opacité régler à 50% puis variable
	setOpacity(128);
	//Couleur noire
	
	return true;
}


void Layer::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void Layer::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	_scene->ccTouchesBegan(touches, event);
}

void Layer::ccTouchesMoved(CCSet* touches, CCEvent* event) {
	_scene->ccTouchesMoved(touches, event);
}

void Layer::ccTouchesEnded(CCSet* touches, CCEvent* event) {
	_scene->ccTouchesEnded(touches, event);
}

void Layer::ccTouchesCancelled(CCSet* touches, CCEvent* event) {
	_scene->ccTouchesCancelled(touches, event);
}
