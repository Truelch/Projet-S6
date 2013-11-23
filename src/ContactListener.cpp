

#include "ContactListener.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	Moveable *moveableA, *moveableB;

	moveableA = (Moveable *)(contact->GetFixtureA()->GetBody()->GetUserData());
	moveableB = (Moveable *)(contact->GetFixtureB()->GetBody()->GetUserData());

	if(moveableA && moveableA->getType()==Moveable::UnitType) ((Unit *)moveableA)->on_contact(moveableB);
	if(moveableB && moveableB->getType()==Moveable::UnitType) ((Unit *)moveableB)->on_contact(moveableA);

	B2_NOT_USED(oldManifold);
}
