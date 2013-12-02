#ifndef PHYSICS_DISPLAYABLE
#define PHYSICS_DISPLAYABLE

#include "Displayable.h"

#include "cocos-ext.h"

USING_NS_CC_EXT;

class PhysicsDisplayable : public Displayable {
	public:

		PhysicsDisplayable();
		PhysicsDisplayable(float x, float y, float rotation, const char * filename, Game * game, Layer * layer, b2Body * body);
		PhysicsDisplayable(Game * game, CCPhysicsSprite * physicsSprite, Layer * layer);
		virtual ~PhysicsDisplayable();

		CCPhysicsSprite * getPhysicsSprite() { return _physicsSprite; }
		virtual Displayable::DisplayableType getType() { return Displayable::physicsDisplayableType; }
	private:
		CCPhysicsSprite * _physicsSprite;
};

#endif
