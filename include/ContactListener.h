#ifndef CONTACT_LISTENER
#define CONTACT_LISTENER

#include "Box2D/Box2D.h"

#include <iostream>

#include "Moveable.h"
#include "Unit.h"

class ContactListener : public b2ContactListener {
	public:
		ContactListener() {}
		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
};

#endif
