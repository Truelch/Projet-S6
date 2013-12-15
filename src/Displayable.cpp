#include "Displayable.h"

#include "Game.h"
#include "Layer.h"

Displayable::Displayable(): EventReceiver() {
	_game = NULL;
	_sprite = CCSprite::create();
	_layer = NULL;
}

Displayable::Displayable(float x, float y, float rotation, const char * filename, Game * game, Layer * layer): EventReceiver(game->getEventHandler()), _game(game), _layer(layer) {
	_sprite = CCSprite::create(filename);
	_sprite->setPosition(ccp(x,y)); //cpp(x,y) = CCPointMake((float)x, (float)y) 
	_sprite->setRotation(rotation);
	layer->addChild(_sprite);
}

Displayable::Displayable(Game * game, CCSprite * sprite, Layer * layer): EventReceiver(game->getEventHandler()), _sprite(sprite), _game(game), _layer(layer) {
	layer->addChild(sprite);
}

Displayable::~Displayable() {
	_layer->removeChild(_sprite);
	//if(_sprite) delete _sprite;
}

bool Displayable::containsPoint(CCPoint point) {
	CCSize size = getSprite()->getTextureRect().size;
	CCPoint pos = getSprite()->getPosition();
	if(point.x>=pos.x-size.width/2.0 && point.x<=pos.x+size.width/2.0 && point.y>=pos.y-size.height/2.0 && point.y<=pos.y+size.height/2.0) {
		return true;
	}
	return false;
}


