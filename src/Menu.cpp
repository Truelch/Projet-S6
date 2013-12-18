
#include "Menu.h"

#include "EGLView.h"
#include "SimpleAudioEngine.h"

MenuItem::MenuItem(const char * filenameSelected, const char * filenameUnselected): cocos2d::CCSprite(), _selected(false) {
	initWithFile(filenameSelected);
	_imageSelected = new cocos2d::CCImage();
	_imageSelected->initWithImageFile(filenameSelected);
	_textureSelected = new cocos2d::CCTexture2D;
	_textureSelected->initWithImage(_imageSelected);

	if(filenameUnselected) {
		_imageUnselected = new cocos2d::CCImage;
		_imageUnselected->initWithImageFile(filenameUnselected);
		_textureUnselected = new cocos2d::CCTexture2D;
		_textureUnselected->initWithImage(_imageUnselected);
	}
	else {
		_imageUnselected = NULL;
		_textureUnselected = NULL;
	}

	if(_textureUnselected) setTexture(_textureUnselected);
	else setTexture(_textureSelected);
}

void MenuItem::set_selected(bool selected) {
	if(_textureUnselected) {
		if(selected) {
			if(!_selected) {
				setTexture(_textureSelected);
				_selected=true;
			}
		}
		else if(_selected) {
			setTexture(_textureUnselected);
			_selected=false;
		}
	}
}

MenuItem::~MenuItem() {
	delete _imageSelected;
	delete _textureSelected;
	if(_imageUnselected) delete _imageUnselected;
	if(_textureUnselected) delete _textureUnselected;
}

void CloseButton::operator()() {
	cocos2d::CCDirector::sharedDirector()->end();
}

void PlayButton::operator()() {
	cocos2d::CCDirector::sharedDirector()->replaceScene(((AppDelegate *)(cocos2d::CCApplication::sharedApplication()))->get_game());
}

Menu::Menu(const char * wallpaperFilename): Scene(), _wallpaper(cocos2d::CCSprite::create(wallpaperFilename)), _layer(new cocos2d::CCLayer()), _menu_item_mouse(NULL) {
	addChild(_layer);
	_layer->addChild(_wallpaper);

	cocos2d::CCPoint origine = EGLView::sharedOpenGLView()->getVisibleOrigin();
	cocos2d::CCSize size = EGLView::sharedOpenGLView()->getVisibleSize();
	_wallpaper->setPosition(cocos2d::CCPoint(origine.x+size.width/2.0,origine.y+size.height/2.0));
	_layer->setScaleX(size.width/_wallpaper->getTextureRect().size.width);
	_layer->setScaleY(size.height/_wallpaper->getTextureRect().size.height);
	_wallpaper->setPosition(cocos2d::CCPoint(270,180));
}

Menu::~Menu() {
	unsigned int i;
	for(i=0;i<_list_menu_item.size();i++) {
		delete _list_menu_item[i];
	}
	delete _wallpaper;
	delete _layer;
}

void Menu::add_menu_item(MenuItem * menuItem) {
	_list_menu_item.push_back(menuItem);

	_layer->addChild(menuItem);
}

void Menu::update_position() {
	float hauteur=0;
	float position;
	unsigned int i;
	if(_list_menu_item.size()==0) return;

	for(i=0; i<_list_menu_item.size(); i++) hauteur+=_list_menu_item[i]->getTextureRect().size.height;
	hauteur+=10*(_list_menu_item.size()-1);

	position=_wallpaper->getPositionY()+(hauteur/2.0)-(_list_menu_item[0]->getTextureRect().size.height/2.0);
	for(i=0; i<_list_menu_item.size(); i++) {
		_list_menu_item[i]->setPosition(cocos2d::CCPoint(_wallpaper->getPositionX(),position));

		if(i!=_list_menu_item.size()-1)
			position-=(10+(_list_menu_item[i]->getTextureRect().size.height/2.0)+_list_menu_item[i+1]->getTextureRect().size.height/2.0);
	}
}

cocos2d::CCPoint Menu::get_mouse_point() {
	cocos2d::CCPoint point = convert_opengl_point_to_layer_point(get_mouse_x(), get_mouse_y(), _layer);
	point.x+=30;
	point.y+=20;
	return point;
}

MenuItem * Menu::get_menu_item_mouse() {
	cocos2d::CCSize size;
	cocos2d::CCPoint pos;
	unsigned int i;
	cocos2d::CCPoint point = get_mouse_point();
	for(i=0; i<_list_menu_item.size(); i++) {
		size = _list_menu_item[i]->getTextureRect().size;
		pos = _list_menu_item[i]->getPosition();
		if(point.x>=pos.x-size.width/2.0 && point.x<=pos.x+size.width/2.0 && point.y>=pos.y-size.height/2.0 && point.y<=pos.y+size.height/2.0) {
			return _list_menu_item[i];
		}
	}
	return NULL;
}

void Menu::mouse_left_button_down() {
	if(_menu_item_mouse) (*_menu_item_mouse)();
}

void Menu::mouse_move(int opengl_x, int opengl_y) {
	Scene::mouse_move(opengl_x,opengl_y);

	MenuItem * menu_item_mouse = get_menu_item_mouse();
	if(menu_item_mouse!=_menu_item_mouse) {
		if(_menu_item_mouse) _menu_item_mouse->set_selected(false);
		if(menu_item_mouse) menu_item_mouse->set_selected(true);
		_menu_item_mouse=menu_item_mouse;
	}
}

