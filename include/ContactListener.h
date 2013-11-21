#ifndef CONTACT_LISTENER
#define CONTACT_LISTENER

#include "Box2D/Box2D.h"

#include <iostream>

class ContactListener : public b2ContactListener {
	public:
		ContactListener() {}
		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
			std::cout << "A : " << contact->GetFixtureA() << ", B : " << contact->GetFixtureB() << std::endl;
			B2_NOT_USED(contact);
			B2_NOT_USED(oldManifold);
		}
};

#endif
