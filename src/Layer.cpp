#include "Layer.h"

#include "Scene.h"
#include "TileLayer.h"

#include <iostream>


using namespace std;


Layer::Layer(): CCLayer(), EventReceiver(), _scene(NULL)
{
	std::cout << "Constructeur de Layer" << std::endl;
	init();
}

Layer::Layer(Scene * scene): CCLayer(), EventReceiver(scene->getEventHandler()), _scene(scene)
{
	std::cout << "Constructeur de Layer" << std::endl;
	init();
}

Layer::~Layer() {
	unsigned int i;
	for(i=0; i<_displayable_list.size(); i++) {
		delete _displayable_list[i];
	}
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
