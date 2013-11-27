

#include "ContactListener.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {

	PhysicsDisplayable *physicsDisplayableA, *physicsDisplayableB;

	physicsDisplayableA = (PhysicsDisplayable *)(contact->GetFixtureA()->GetBody()->GetUserData());
	physicsDisplayableB = (PhysicsDisplayable *)(contact->GetFixtureB()->GetBody()->GetUserData());

	_scene->getEventHandler()->on_physics_displayable_contact(physicsDisplayableA, physicsDisplayableB);
	
	B2_NOT_USED(oldManifold);
}
