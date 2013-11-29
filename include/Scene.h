#ifndef SCENE
#define SCENE

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "EventHandler.h"

#define PTM_RATIO 32
#define COEFF     2.1

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
		virtual void key_press(int key) {}

		b2World * getWorld() { return _world; }
		EventHandler * getEventHandler() { return _event_handler; }
	private:
		EventHandler * _event_handler;
		b2World * _world;
};

#endif
