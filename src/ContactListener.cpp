

#include "ContactListener.h"

#include "EventHandler.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	Displayable *displayableA, *displayableB;

	displayableA = (Displayable *)(contact->GetFixtureA()->GetBody()->GetUserData());
	displayableB = (Displayable *)(contact->GetFixtureB()->GetBody()->GetUserData());

	_scene->getEventHandler()->on_displayable_contact(displayableA, displayableB);
	
	B2_NOT_USED(oldManifold);
}
