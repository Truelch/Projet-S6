#ifndef GAME_H
#define GAME_H

#include "cocos2d.h"
#include <vector>

#include "Displayable.h"

using namespace std;

class Game : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	void menuCloseCallback(CCObject* pSender);
	
	// implement the "static node()" method manually
	CREATE_FUNC(Game);
	
	//Faire bouger l'unite
	virtual void update(CCTime dt); //le virtual (qui n'est que dans le .h d'ailleurs) sert à indiquer qu'on surcharge une methode existante
	
	//Attributs
	vector <Displayable *> _displayables;

	virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
	virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event);
};

#endif // GAME_H
