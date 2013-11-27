#ifndef CONTACT_LISTENER
#define CONTACT_LISTENER

#include "Box2D/Box2D.h"

#include <iostream>

#include "Scene.h"
#include "PhysicsDisplayable.h"

class ContactListener : public b2ContactListener {
	public:
		ContactListener(): _scene(NULL) {}
		ContactListener(Scene * scene): _scene(scene) {}
		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	private:
		Scene * _scene;
};

#endif
