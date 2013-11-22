#include "Displayable.h"

Displayable::Displayable() {
	_scene = NULL;
	_sprite = CCSprite::create();
}

Displayable::Displayable(CCSprite * sprite): _sprite(sprite) {
	_scene = NULL;
}

Displayable::Displayable(float x, float y, float rotation, const char * filename, Scene * scene): _scene(scene) {
	_sprite = CCSprite::create(filename);
	_sprite->setPosition(ccp(x,y)); //cpp(x,y) = CCPointMake((float)x, (float)y) 
	_sprite->setRotation(rotation);
}

Displayable::Displayable(Scene * scene, CCSprite * sprite): _sprite(sprite), _scene(scene) {
}

Displayable::~Displayable() {
	delete _sprite;
}
