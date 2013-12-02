
#include "MapTile.h"

#include "Building.h"
#include "Layer.h"
#include "Box2D/Box2D.h"
#include "Game.h"

MapTile::MapTile(): MapDisplayable(), _crossUp(true), _crossDown(true), _crossRight(true), _crossLeft(true), _building(NULL), _tile_x(0), _tile_y(0) {

}

MapTile::MapTile(float x, float y, const char * filename, Game * game, Layer * layer, bool crossUp, bool crossDown, bool crossRight, bool crossLeft): MapDisplayable(x,y,filename,game,layer), _crossUp(crossUp), _crossDown(crossDown), _crossRight(crossRight), _crossLeft(crossLeft), _building(NULL) {
	game->get_display_layer()->coordonate_cocos2dx_to_tile(x,y,_tile_x,_tile_y);

	CCRect rect = getSprite()->getTextureRect();
	b2BodyDef groundBodyDef;
	groundBodyDef.userData = this;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
	b2Body* groundBody = getGame()->getWorld()->CreateBody(&groundBodyDef);
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
