#include "Building.h"

Building::Building(): PhysicsDisplayable() {
	//
}

Building::Building(int x, int y, const char * filename, Scene * scene, Layer * layer, float x_rally_point, float y_rally_point): PhysicsDisplayable(scene,CCPhysicsSprite::create(filename),layer), _rally_point(CCPoint(x_rally_point,y_rally_point))
{
}

Building::Building(MapTile * mapTile, const char * filename, Scene * scene, Layer * layer, float x_rally_point, float y_rally_point): PhysicsDisplayable(scene,CCPhysicsSprite::create(filename),layer), _rally_point(CCPoint(x_rally_point,y_rally_point))
{
	CCPoint position = mapTile->getSprite()->getOffsetPosition();
	b2BodyDef bodyDef;
	bodyDef.userData = this;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x,position.y);

	b2Body *body = getScene()->getWorld()->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(getSprite()->getTextureRect().size.width/PTM_RATIO/2,getSprite()->getTextureRect().size.height/PTM_RATIO/2);

	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;	
	body->CreateFixture(&fixtureDef);	

	getPhysicsSprite()->setB2Body(body);
	getPhysicsSprite()->setPTMRatio(PTM_RATIO);
	getPhysicsSprite()->setPosition( mapTile->getSprite()->getPosition() );
}
