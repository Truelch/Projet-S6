#ifndef GAME_H
#define GAME_H

#include "cocos2d.h"
#include <vector>

#include "Displayable.h"

using namespace std;

class Game : public cocos2d::CCScene
{
	public:
		Game();
		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		CCLayer * layer;
		
		// implement the "static node()" method manually
		CREATE_FUNC(Game);

		//Faire bouger l'unite
		virtual void update(CCTime dt); //le virtual (qui n'est que dans le .h d'ailleurs) sert à indiquer qu'on surcharge une methode existante
		
		void ccTouchesBegan(CCSet* touches, CCEvent* event);
		void ccTouchesMoved(CCSet* touches, CCEvent* event);
		void ccTouchesEnded(CCSet* touches, CCEvent* event);
		void ccTouchesCancelled(CCSet* touches, CCEvent* event);
		
	
		//Attributs
		vector <Displayable *> _displayables;

};

#endif // GAME_H
