
#include "MapTile.h"

MapTile::MapTile(): MapDisplayable() {

}

MapTile::MapTile(float x, float y, const char * filename, Scene * scene, Layer * layer, bool crossUp, bool crossDown, bool crossRight, bool crossLeft): MapDisplayable(x,y,filename,scene,layer), _crossUp(crossUp), _crossDown(crossDown), _crossRight(crossRight), _crossLeft(crossLeft) {
	CCRect rect = getSprite()->getTextureRect();
	b2BodyDef groundBodyDef;
	groundBodyDef.userData = NULL;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
	b2Body* groundBody = getScene()->getWorld()->CreateBody(&groundBodyDef);
	b2EdgeShape groundBox;

	if(!_crossDown) {
		groundBox.Set(b2Vec2((x-rect.size.width/2)/PTM_RATIO,(y-rect.size.height/2)/PTM_RATIO), b2Vec2((x+rect.size.width/2)/PTM_RATIO,(y-rect.size.height/2)/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}
	if(!_crossUp) {
		groundBox.Set(b2Vec2((x-rect.size.width/2)/PTM_RATIO,(y+rect.size.height/2)/PTM_RATIO), b2Vec2((x+rect.size.width/2)/PTM_RATIO,(y+rect.size.height/2)/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}
	if(!_crossLeft) {
		groundBox.Set(b2Vec2((x-rect.size.width/2)/PTM_RATIO,(y-rect.size.height/2)/PTM_RATIO), b2Vec2((x-rect.size.width/2)/PTM_RATIO,(y+rect.size.height/2)/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}
	if(!_crossRight) {
		groundBox.Set(b2Vec2((x+rect.size.width/2)/PTM_RATIO,(y-rect.size.height/2)/PTM_RATIO), b2Vec2((x+rect.size.width/2)/PTM_RATIO,(y+rect.size.height/2)/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}
}
