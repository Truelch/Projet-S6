
#include "Scene.h"
#include "EventHandler.h"
#include "DisplayLayer.h"

#include "CCArmature/external_tool/GLES-Render.h"

Scene::Scene(): CCScene() {
	_event_handler = new EventHandler(); 

	//box2d world
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	_world = new b2World(gravity);

	_debug_draw = new cocos2d::extension::GLESDebugDraw( PTM_RATIO );
	_world->SetDebugDraw(_debug_draw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	_debug_draw->SetFlags(flags);

}

Scene::~Scene() {
	delete _world;
	delete _event_handler;
}
