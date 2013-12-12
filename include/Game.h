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
class SelectionZone;
class Cursor;

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
		Player * get_main_player() { return _main_player; }
		const vector<Player *>& get_player_list() { return _player_list; }
		
		// --- SET ---
		
		
		// implement the "static node()" method manually
		//CREATE_FUNC(Game);

		void set_tile_to_center_of_screen(int tile_x, int tile_y);
		void get_center_of_screen(int& x, int& y);
		void set_point_to_center_of_screen(cocos2d::CCPoint point);
		bool check_out_of_map_whith_new_scrolling(float& offset_x, float& offset_y);
		void set_map_point_to_opengl_point(cocos2d::CCPoint map_point, int opengl_x, int opengl_y);
		cocos2d::CCPoint convert_opengl_point_to_layer_point(int opengl_x, int opengl_y, Layer * layer);
		cocos2d::CCPoint convert_opengl_point_to_layer_point_with_new_offset(int opengl_x, int opengl_y, Layer * layer, float offset_x, float offset_y);

		virtual void update(float dt);

		virtual void mouse_left_button_down();
		virtual void mouse_left_button_up();
		virtual void mouse_right_button_down();
		virtual void mouse_move( int x, int y);
		virtual void key_press(int key);
		virtual void key_release(int key);
		virtual void mouse_wheel_up();
		virtual void mouse_wheel_down();
		
	private:
		void set_bar_visible(bool visible);


		int _map_width;
		int _map_height;

		ContactListener * _contactListener;
		
		DisplayLayer *    _display_layer;

		Layer * _hud_layer;
		Layer * _cursor_layer;
		Cursor * _cursor;

		bool _scroll_left_mouse;
		bool _scroll_right_mouse;
		bool _scroll_up_mouse;
		bool _scroll_down_mouse;
		bool _scroll_left_key;
		bool _scroll_right_key;
		bool _scroll_up_key;
		bool _scroll_down_key;
		bool _mouse_button_left_down;

		bool _key_left_alt;
		bool _key_right_alt;

		Player * _main_player;
		vector<Player *> _player_list;

		SelectionZone * _selectionZone;
		bool _selection_zone_enable;

		int _mouse_x, _mouse_y;
		int _old_x, _old_y;
		bool _mouse_initiate;
};

#endif
