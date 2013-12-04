#include "Building.h"

#include "Box2D/Box2D.h"
#include "MapTile.h"
#include "Game.h"

Building::Building(): PhysicsDisplayable() {
	//
}

Building::Building(int x, int y, const char * filename, Game * game, Layer * layer, float x_rally_point, float y_rally_point): PhysicsDisplayable(game,CCPhysicsSprite::create(filename),layer), _rally_point(CCPoint(x_rally_point,y_rally_point)), _map_tile(game->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[y][x])
{
	init();
}

Building::Building(MapTile * mapTile, const char * filename, Game * game, Layer * layer, float x_rally_point, float y_rally_point): PhysicsDisplayable(game,CCPhysicsSprite::create(filename),layer), _rally_point(CCPoint(x_rally_point,y_rally_point)), _map_tile(mapTile)
{
	init();
}

void Building::init() {
	CCPoint position = _map_tile->getSprite()->getOffsetPosition();
	int tile_x, tile_y;

	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(position.x, position.y, tile_x, tile_y);
	if(_map_tile->get_building()) {
		std::cerr << "ERREUR : impossible de construire un batiment aux coordonnee " << tile_x << "," << tile_y << " le batiment existe deja." << std::endl;
	}
	_map_tile->set_building(this);

	b2BodyDef bodyDef;
	bodyDef.userData = this;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x,position.y);

	b2Body *body = getGame()->getWorld()->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(getSprite()->getTextureRect().size.width/PTM_RATIO/2,getSprite()->getTextureRect().size.height/PTM_RATIO/2);

	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;	
	body->CreateFixture(&fixtureDef);	

	getPhysicsSprite()->setB2Body(body);
	getPhysicsSprite()->setPTMRatio(PTM_RATIO);
	getPhysicsSprite()->setPosition( _map_tile->getSprite()->getPosition() );
}
