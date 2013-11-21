#include "Layer.h"

#include "Scene.h"
#include "TileLayer.h"

#include <iostream>


using namespace std;


Layer::Layer(): CCLayer(), _scene(NULL)
{
	init();
}

Layer::Layer(Scene * scene): CCLayer(), _scene(scene)
{
	init();
}

bool Layer::init()
{
	if( !CCLayer::init() ) {
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//	you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
										"CloseNormal.png",
										"CloseSelected.png",
										this,
										menu_selector(Layer::menuCloseCallback));
	
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
								origin.y + pCloseItem->getContentSize().height/2));
								
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);							   

	/////////////////////////////
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
