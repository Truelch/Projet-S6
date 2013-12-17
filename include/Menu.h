#ifndef MENU
#define MENU

#include "Scene.h"
#include "Game.h"
#include "AppDelegate.h"

#include <string>

class MenuItem : public cocos2d::CCSprite {
	private:
		cocos2d::CCImage * _imageUnselected;
		cocos2d::CCImage * _imageSelected;
		cocos2d::CCTexture2D * _textureUnselected;
		cocos2d::CCTexture2D * _textureSelected;
		bool _selected;

	public:
		MenuItem(const char * filenameSelected, const char * filenameUnselected = NULL);
		virtual ~MenuItem();

		virtual void operator()() = 0;

		bool get_selected() { return _selected; }
		void set_selected(bool selected);
};

class CloseButton : public MenuItem {
	public:
		CloseButton(const char * filenameSelected, const char * filenameUnselected = NULL): MenuItem(filenameSelected,filenameUnselected) {}

		virtual void operator()() { cocos2d::CCDirector::sharedDirector()->end(); }
};

class PlayButton : public MenuItem {
	public:
		PlayButton(const char * filenameSelected, const char * filenameUnselected = NULL): MenuItem(filenameSelected,filenameUnselected) {}

		virtual void operator()() { cocos2d::CCDirector::sharedDirector()->replaceScene(((AppDelegate *)(cocos2d::CCApplication::sharedApplication()))->get_game()); }
};

class Menu : public Scene {
	private:
		vector<MenuItem *> _list_menu_item;
		cocos2d::CCSprite * _wallpaper;
		cocos2d::CCLayer * _layer;
		MenuItem * _menu_item_mouse;

		MenuItem * get_menu_item_mouse();;

	public:
		Menu(const char * wallpaperFilename);
		virtual ~Menu();

		cocos2d::CCPoint get_mouse_point();
		void update_position();
		void add_menu_item(MenuItem * menuItem);
		virtual void mouse_left_button_down();
		virtual void mouse_move( int opengl_x, int opengl_y);
};

#endif
