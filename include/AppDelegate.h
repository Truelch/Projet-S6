#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

class Game;
class Menu;
class VictoryScene;

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication
{
	private:
		Game * _game;
		Menu * _menu;
		VictoryScene * _victory_scene;

	public:
		AppDelegate();
		virtual ~AppDelegate();

		/**
		@brief    Implement CCDirector and CCScene init code here.
		@return true    Initialize success, app continue.
		@return false   Initialize failed, app terminate.
		*/
		virtual bool applicationDidFinishLaunching();

		/**
		@brief  The function be called when the application enter background
		@param  the pointer of the application
		*/
		virtual void applicationDidEnterBackground();

		/**
		@brief  The function be called when the application enter foreground
		@param  the pointer of the application
		*/
		virtual void applicationWillEnterForeground();

		Game * get_game() { return _game; }
		Menu * get_menu() { return _menu; }
		VictoryScene * get_victory_scene() { return _victory_scene; }
};

#endif // _APP_DELEGATE_H_

