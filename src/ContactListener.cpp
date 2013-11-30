

#include "ContactListener.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {

	PhysicsDisplayable *physicsDisplayableA, *physicsDisplayableB;

	if( contact->GetFixtureA()->GetBody()->GetUserData() && contact->GetFixtureB()->GetBody()->GetUserData() ) {
		physicsDisplayableA = (PhysicsDisplayable *)(contact->GetFixtureA()->GetBody()->GetUserData());
		physicsDisplayableB = (PhysicsDisplayable *)(contact->GetFixtureB()->GetBody()->GetUserData());

		_scene->getEventHandler()->on_physics_displayable_contact(physicsDisplayableA, physicsDisplayableB);
	}
	
	B2_NOT_USED(oldManifold);
}
