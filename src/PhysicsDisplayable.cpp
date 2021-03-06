#include "PhysicsDisplayable.h"

#include "Scene.h"

PhysicsDisplayable::PhysicsDisplayable():Displayable(NULL, CCPhysicsSprite::create(), NULL) {
	_physicsSprite = (CCPhysicsSprite *)getSprite();
}

PhysicsDisplayable::PhysicsDisplayable(float x, float y, float rotation, const char * filename, Game * game, Layer * layer, b2Body * body): Displayable(game,CCPhysicsSprite::create(filename),layer) {
	_physicsSprite = (CCPhysicsSprite *)(getSprite());
	_physicsSprite->setB2Body(body);
	_physicsSprite->setPTMRatio(PTM_RATIO);
	_physicsSprite->setPosition( ccp(x,y) );
	_physicsSprite->setRotation(rotation);
}

PhysicsDisplayable::PhysicsDisplayable(Game * game, CCPhysicsSprite * physicsSprite, Layer * layer):Displayable(game,physicsSprite,layer), _physicsSprite(physicsSprite) {
}

PhysicsDisplayable::~PhysicsDisplayable() {
	/*
	if(_physicsSprite) {
		getGame()->getWorld()->DestroyBody(_physicsSprite->getB2Body());
		delete _physicsSprite;
		setSprite(NULL);
	}
	*/
}
