#ifndef GAME_H
#define GAME_H

#include "cocos2d.h"
#include <vector>

#include "Moveable.h"
//#include Unit.h"
#include "Hud.h"

using namespace std;

class Game : public cocos2d::CCScene
{
	public:
		Game();
		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

		// implement the "static node()" method manually
		CREATE_FUNC(Game);

		//Faire bouger l'unite
		virtual void update(CCTime dt); //le virtual (qui n'est que dans le .h d'ailleurs) sert à indiquer qu'on surcharge une methode existante
		
		void ccTouchesBegan(CCSet* touches, CCEvent* event);
		void ccTouchesMoved(CCSet* touches, CCEvent* event);
		void ccTouchesEnded(CCSet* touches, CCEvent* event);
		void ccTouchesCancelled(CCSet* touches, CCEvent* event);
		
	private:

		CCLayer * _main_layer;
		CCLayer * _hud_layer;
		
		vector <Moveable *> _moveables;
		Hud* _hud;

};

#endif // GAME_H
