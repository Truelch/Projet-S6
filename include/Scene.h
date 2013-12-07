#ifndef SCENE
#define SCENE

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCArmature/external_tool/GLES-Render.h"
#include "Box2D/Box2D.h"

class EventHandler;
class DisplayLayer;

#define PTM_RATIO 32

class Scene : public cocos2d::CCScene
{
	public:
		Scene();
		virtual ~Scene();

		virtual void mouse_left_button_down( int opengl_x, int opengl_y ) {}
		virtual void mouse_left_button_up( int opengl_x, int opengl_y ) {}
		virtual void mouse_right_button_down( int opengl_x, int opengl_y ) {}
		virtual void mouse_right_button_up( int opengl_x, int opengl_y ) {}
		virtual void mouse_move( int opengl_x, int opengl_y) {}
		virtual void mouse_wheel_up(int opengl_x, int opengl_y) {}
		virtual void mouse_wheel_down(int opengl_x, int opengl_y) {}
		virtual void key_press(int key) {}
		virtual void key_release(int key) {}

		b2World * getWorld() { return _world; }
		EventHandler * getEventHandler() { return _event_handler; }
		cocos2d::extension::GLESDebugDraw * get_debug_draw() { return _debug_draw; }
		
		//Mon ajout
		virtual DisplayLayer * get_display_layer() = 0;
		
	private:
		EventHandler * _event_handler;
		b2World * _world;
		cocos2d::extension::GLESDebugDraw * _debug_draw;
};

#endif
