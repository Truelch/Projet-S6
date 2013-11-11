#ifndef GAME_H
#define GAME_H

#include "cocos2d.h"
#include <vector>

#include "Moveable.h"
//#include Unit.h"
#include "Hud.h"
#include "DisplayLayer.h"
#include "Scene.h"

using namespace std;

class Game : public Scene
{
	public:
		Game();
		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

		
		// --- GET ---
		DisplayLayer * get_display_layer();
		
		// --- SET ---
		
		
		// implement the "static node()" method manually
		CREATE_FUNC(Game);

		//Faire bouger l'unite
		virtual void update(float dt); //le virtual (qui n'est que dans le .h d'ailleurs) sert à indiquer qu'on surcharge une methode existante
		
		virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
		virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
		virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
		virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event);
		
	private:
		DisplayLayer * _display_layer;

};

#endif
