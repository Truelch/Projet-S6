#ifndef GAME_H
#define GAME_H

#include "cocos2d.h"
#include <vector>

#include "Scene.h"

class Moveable;
class Unit;
class Hud;
class UnitLayer;
class ContactListener;
class Building;
class DisplayLayer;
class Layer;
class Player;

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
		//CREATE_FUNC(Game);

		cocos2d::CCPoint get_center_screen();
		void set_tile_to_center_of_screen(int tile_x, int tile_y);
		void set_point_to_center_of_screen(cocos2d::CCPoint point);

		//Faire bouger l'unite
		virtual void update(float dt); //le virtual (qui n'est que dans le .h d'ailleurs) sert à indiquer qu'on surcharge une methode existante
		
		virtual void mouse_left_button_down( int x, int y );
		virtual void mouse_move( int x, int y);
		virtual void key_press(int key);
		virtual void key_release(int key);
		
	private:
		int _map_width;
		int _map_height;

		ContactListener * _contactListener;
		
		DisplayLayer *    _display_layer;

		Layer * _hud_layer;
		Hud * _hud;

		bool _scroll_left_mouse;
		bool _scroll_right_mouse;
		bool _scroll_up_mouse;
		bool _scroll_down_mouse;
		bool _scroll_left_key;
		bool _scroll_right_key;
		bool _scroll_up_key;
		bool _scroll_down_key;

		Player * _main_player;
		vector<Player *> _player_list;
};

#endif
