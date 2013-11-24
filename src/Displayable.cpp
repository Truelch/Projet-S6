#include "Displayable.h"

Displayable::Displayable() {
	_scene = NULL;
	_sprite = CCSprite::create();
	_layer = NULL;
}

Displayable::Displayable(CCSprite * sprite, Layer * layer): _sprite(sprite), _layer(layer) {
	_scene = NULL;
}

Displayable::Displayable(float x, float y, float rotation, const char * filename, Scene * scene, Layer * layer): _scene(scene), _layer(layer) {
	_sprite = CCSprite::create(filename);
	_sprite->setPosition(ccp(x,y)); //cpp(x,y) = CCPointMake((float)x, (float)y) 
	_sprite->setRotation(rotation);
}

Displayable::Displayable(Scene * scene, CCSprite * sprite, Layer * layer): _sprite(sprite), _scene(scene), _layer(layer) {
}

Displayable::~Displayable() {
	//if(_sprite) delete _sprite;
}
