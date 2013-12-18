#ifndef SCENE
#define SCENE

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCArmature/external_tool/GLES-Render.h"
#include "Box2D/Box2D.h"

class EventHandler;
class DisplayLayer;
class Layer;

#define PTM_RATIO 32

class Scene : public cocos2d::CCScene
{
	public:
		Scene();
		virtual ~Scene();

		void get_center_of_screen(int& x, int& y);
		cocos2d::CCPoint convert_opengl_point_to_layer_point(int opengl_x, int opengl_y, cocos2d::CCLayer * layer);
		cocos2d::CCPoint convert_opengl_point_to_layer_point_with_new_offset(int opengl_x, int opengl_y, cocos2d::CCLayer * layer, float offset_x, float offset_y);

		int get_mouse_x() { return _mouse_x; }
		int get_mouse_y() { return _mouse_y; }
		cocos2d::CCLayer * get_cursor_layer() { return _cursor_layer; }

		virtual void mouse_left_button_down() {}
		virtual void mouse_left_button_up() {}
		virtual void mouse_right_button_down() {}
		virtual void mouse_right_button_up() {}
		virtual void mouse_move( int opengl_x, int opengl_y);
		virtual void mouse_wheel_up() {}
		virtual void mouse_wheel_down() {}
		virtual void key_press(int key) {}
		virtual void key_release(int key) {}

		b2World * getWorld() { return _world; }
		EventHandler * getEventHandler() { return _event_handler; }
		cocos2d::extension::GLESDebugDraw * get_debug_draw() { return _debug_draw; }
		
	private:
		EventHandler * _event_handler;
		b2World * _world;
		cocos2d::extension::GLESDebugDraw * _debug_draw;

		int _mouse_x, _mouse_y;
		int _old_x, _old_y;
		bool _mouse_initiate;

		cocos2d::CCLayer * _cursor_layer;
		cocos2d::CCSprite * _cursor;
};

#endif
