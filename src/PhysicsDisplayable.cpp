#include "PhysicsDisplayable.h"

#include "Scene.h"

PhysicsDisplayable::PhysicsDisplayable():Displayable(NULL, CCPhysicsSprite::create(), NULL), _type(moveableType) {
	_physicsSprite = (CCPhysicsSprite *)getSprite();
}

PhysicsDisplayable::PhysicsDisplayable(PhysicsDisplayableType type, float x, float y, float rotation, const char * filename, Scene * scene, Layer * layer, b2Body * body): Displayable(scene,CCPhysicsSprite::create(filename),layer), _type(type) {
	_physicsSprite = (CCPhysicsSprite *)(getSprite());
	_physicsSprite->setB2Body(body);
	_physicsSprite->setPTMRatio(PTM_RATIO);
	_physicsSprite->setPosition( ccp(x,y) );
	_physicsSprite->setRotation(rotation);
}

PhysicsDisplayable::PhysicsDisplayable(PhysicsDisplayableType type, Scene * scene, CCPhysicsSprite * physicsSprite, Layer * layer):Displayable(scene,physicsSprite,layer), _physicsSprite(physicsSprite), _type(type) {
}

PhysicsDisplayable::~PhysicsDisplayable() {
	/*
	if(_physicsSprite) {
		getScene()->getWorld()->DestroyBody(_physicsSprite->getB2Body());
		delete _physicsSprite;
		setSprite(NULL);
	}
	*/
}
