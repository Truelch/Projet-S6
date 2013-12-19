
#include "MapTile.h"

#include "Building.h"
#include "Layer.h"
#include "Box2D/Box2D.h"
#include "Game.h"
#include "DisplayLayer.h"

MapTile::MapTile(): MapDisplayable(), _crossUp(true), _crossDown(true), _crossRight(true), _crossLeft(true), _building(NULL), _tile_x(0), _tile_y(0) {

}

MapTile::MapTile(std::string id, float x, float y, const char * filename, Game * game, Layer * layer, bool crossUp, bool crossDown, bool crossRight, bool crossLeft): MapDisplayable(x,y,filename,game,layer), _crossUp(crossUp), _crossDown(crossDown), _crossRight(crossRight), _crossLeft(crossLeft), _building(NULL), _id(id) {
	b2BodyDef groundBodyDef;
	groundBodyDef.userData = this;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
	b2Body* groundBody = getGame()->getWorld()->CreateBody(&groundBodyDef);
	b2EdgeShape groundBox;

	game->get_display_layer()->coordonate_cocos2dx_to_tile(x,y,_tile_x,_tile_y);

	if(!_crossDown) {
		groundBox.Set(b2Vec2(get_min_x()/PTM_RATIO,get_min_y()/PTM_RATIO), b2Vec2(get_max_x()/PTM_RATIO,get_min_y()/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}
	if(!_crossUp) {
		groundBox.Set(b2Vec2(get_min_x()/PTM_RATIO,get_max_y()/PTM_RATIO), b2Vec2(get_max_x()/PTM_RATIO,get_max_y()/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}
	if(!_crossLeft) {
		groundBox.Set(b2Vec2(get_min_x()/PTM_RATIO,get_min_y()/PTM_RATIO), b2Vec2(get_min_x()/PTM_RATIO,get_max_y()/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}
	if(!_crossRight) {
		groundBox.Set(b2Vec2(get_max_x()/PTM_RATIO,get_min_y()/PTM_RATIO), b2Vec2(get_max_x()/PTM_RATIO,get_max_y()/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}
}

float MapTile::get_min_x() {
	return getSprite()->getPosition().x-getSprite()->getTextureRect().size.width/2.0;
}

float MapTile::get_max_x() {
	return getSprite()->getPosition().x+getSprite()->getTextureRect().size.width/2.0;
}

float MapTile::get_min_y() {
	return getSprite()->getPosition().y-getSprite()->getTextureRect().size.height/2.0;
}

float MapTile::get_max_y() {
	return getSprite()->getPosition().y+getSprite()->getTextureRect().size.height/2.0;
}

CCPoint MapTile::get_vertex_left_bottom() {
	return CCPoint(get_min_x(),get_min_y());
}

CCPoint MapTile::get_vertex_left_top() {
	return CCPoint(get_min_x(),get_max_y());
}

CCPoint MapTile::get_vertex_right_bottom() {
	return CCPoint(get_max_x(),get_min_y());
}

CCPoint MapTile::get_vertex_right_top() {
	return CCPoint(get_max_x(),get_max_y());
}

bool MapTile::test_achievable() {
	return (_crossUp || _crossDown || _crossRight || _crossLeft) && !_building;
}

