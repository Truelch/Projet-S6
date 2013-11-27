#ifndef PHYSICS_DISPLAYABLE
#define PHYSICS_DISPLAYABLE

#include "Displayable.h"

#include "cocos-ext.h"

USING_NS_CC_EXT;

class PhysicsDisplayable : public Displayable {
	public:
		typedef enum {
			buildingType,
			moveableType,
		} PhysicsDisplayableType;

		PhysicsDisplayable();
		PhysicsDisplayable(PhysicsDisplayableType type, float x, float y, float rotation, const char * filename, Scene * scene, Layer * layer, b2Body * body);
		PhysicsDisplayable(PhysicsDisplayableType type, Scene * scene, CCPhysicsSprite * physicsSprite, Layer * layer);
		virtual ~PhysicsDisplayable();

		CCPhysicsSprite * getPhysicsSprite() { return _physicsSprite; }
		PhysicsDisplayableType getType() { return _type; }
	private:
		CCPhysicsSprite * _physicsSprite;
		PhysicsDisplayableType _type;
};

#endif
