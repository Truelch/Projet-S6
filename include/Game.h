#ifndef GAME_H
#define GAME_H

#include "cocos2d.h"
#include <vector>

#include "Moveable.h"
#include "Unit.h"
#include "Hud.h"
#include "DisplayLayer.h"
#include "Scene.h"
#include "UnitLayer.h"
#include "ContactListener.h"
#include "Building.h"

using namespace std;

class Game : public Scene
{
	public:
		Game();
		virtual ~Game();
		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

		
		// --- GET ---
		int get_map_width();
		int get_map_height();
		
		DisplayLayer * get_display_layer();
		
		// --- SET ---
		
		
		// implement the "static node()" method manually
		CREATE_FUNC(Game);

		//Faire bouger l'unite
		virtual void update(float dt); //le virtual (qui n'est que dans le .h d'ailleurs) sert à indiquer qu'on surcharge une methode existante
		
		virtual void mouse_left_button_down( int x, int y );
		virtual void mouse_move( int x, int y);
		
	private:
		int _map_width;
		int _map_height;

		ContactListener * _contactListener;
		
		DisplayLayer * _display_layer;

		Layer * _hud_layer;
		Hud * _hud;

		bool _scroll_left;
		bool _scroll_right;
		bool _scroll_up;
		bool _scroll_down;
};

#endif
