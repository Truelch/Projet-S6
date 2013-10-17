#include "Game.h"
#include "AppMacros.h"
#include <iostream>


USING_NS_CC;

using namespace std;


CCScene* Game::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Game *layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Game::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
                                
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);                               

    /////////////////////////////

    //Displayable* displayable = new Displayable(150,150,45,"01.png");
    _displayables.push_back(new Displayable(150,150,-90,"01.png"));
    this->addChild(*(_displayables.end()-1),0); //this->addChild(_displayables[_displayables.size()-1]),0);
    
    // --- --- ---
    this->schedule( schedule_selector( Game::update ), 1.0 / 50 );
    
    return true;
}


void Game::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Game::update(CCTime dt)
{
	vector <Displayable *>::iterator it;
	const CCPoint* pos=NULL; //cf doc
	for(it=_displayables.begin();it!=_displayables.end();it++)
	{
		if(pos) delete pos;
		pos = new CCPoint((*it)->getPosition());
		if (pos->x < 500)
		{
			(*it)->setPositionX(((*it)->getPosition().x)+1);
		}
		else
		{
			(*it)->setPositionX(150);
		}
	}
	if(pos) delete pos;

}
