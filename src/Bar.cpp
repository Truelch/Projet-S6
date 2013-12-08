
#include "Bar.h"
#include "Game.h"

#include "DisplayLayer.h"

Bar::Bar(Game * game, Layer * layer, float x, float y, float value, int width, int height, ccColor4B foregroundColor, ccColor4B backgroundColor): Displayable(game, new CCSprite(), layer), _value(value), _width(width), _height(height), _foregroundColor(foregroundColor), _backgroundColor(backgroundColor), _visible(false) {
	int bytes = _width * _height * 4;
	void* textureData = malloc(bytes);
	memset(textureData, INT32_MAX, bytes);

	_texture = new CCTexture2DMutable();
	_texture->initWithData(textureData, kCCTexture2DPixelFormat_RGBA8888, _width, _height, CCSize(_width,_height));

	_texture->setAliasTexParameters();

	update();

	getSprite()->initWithTexture(_texture);
	getSprite()->setPosition(CCPoint(x,y));
	_texture->autorelease();
	getSprite()->setScale(0);
}

void Bar::update() {

	for (int x = 0; x < _width; x++) {
		for (int y = 0; y < _height; y++) {
			if(x>_width*_value) _texture->setPixelAt(CCPointMake(x, y), _backgroundColor);
			else _texture->setPixelAt(CCPointMake(x, y), _foregroundColor);
			
		}
	}

	_texture->apply();

}

Bar::~Bar() {
	delete _texture;
}

void Bar::set_visible(bool visible) {
	_visible = visible;
	if(visible) getSprite()->setScale(1);
	else getSprite()->setScale(0);
}
