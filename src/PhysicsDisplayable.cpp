#include "PhysicsDisplayable.h"

PhysicsDisplayable::PhysicsDisplayable():Displayable(CCPhysicsSprite::create()) {
	_physicsSprite = (CCPhysicsSprite *)getSprite();
}

PhysicsDisplayable::PhysicsDisplayable(float x, float y, float rotation, const char * filename, Scene * scene, b2Body * body):Displayable(scene,CCPhysicsSprite::create(filename)) {
	_physicsSprite = (CCPhysicsSprite *)(getSprite());
	_physicsSprite->setB2Body(body);
	_physicsSprite->setPTMRatio(PTM_RATIO);
	_physicsSprite->setPosition( ccp(x,y) );
	_physicsSprite->setRotation(rotation);
}

PhysicsDisplayable::PhysicsDisplayable(Scene * scene, CCPhysicsSprite * physicsSprite):Displayable(scene,physicsSprite), _physicsSprite(physicsSprite) {
}

PhysicsDisplayable::~PhysicsDisplayable() {
	if(_physicsSprite) {
		getScene()->getWorld()->DestroyBody(_physicsSprite->getB2Body());
		delete _physicsSprite;
		setSprite(NULL);
	}
}
