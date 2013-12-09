#include "Building.h"

#include "Box2D/Box2D.h"
#include "MapTile.h"
#include "Game.h"
#include "DisplayLayer.h"
#include "TileLayer.h"

#include "Player.h"
#include "EventHandler.h"

#include <algorithm>

Building::Building(): PhysicsDisplayable() 
{
	//
}

Building::Building(int x, int y, const char * filename, Game * game, Layer * layer, float x_rally_point, float y_rally_point, Player * player, float sight): PhysicsDisplayable(game,CCPhysicsSprite::create(filename),layer), _rally_point(CCPoint(x_rally_point,y_rally_point)), _map_tile(game->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[y][x]), _player(player), _sight(sight)
{
	init();

	_player->get_building_vector().push_back(this);
	update_range_map_tile_list();
	getGame()->getEventHandler()->on_building_change_player(this, NULL, _player);
}

Building::Building(MapTile * mapTile, const char * filename, Game * game, Layer * layer, float x_rally_point, float y_rally_point, Player * player, float sight): PhysicsDisplayable(game,CCPhysicsSprite::create(filename),layer), _rally_point(CCPoint(x_rally_point,y_rally_point)), _map_tile(mapTile), _player(player), _sight(sight)
{
	init();

	_player->get_building_vector().push_back(this);
	update_range_map_tile_list();
	getGame()->getEventHandler()->on_building_change_player(this, NULL, _player);
}

// --- GET ---
Player * Building::get_player()
{
	return _player;
}

// --- SET ---
void Building::set_player(Player * player)
{
	_player->get_building_vector().erase(std::remove(_player->get_building_vector().begin(), _player->get_building_vector().end(), this), _player->get_building_vector().end());
	player->get_building_vector().push_back(this);
	getGame()->getEventHandler()->on_building_change_player(this, _player, player);
	_player = player;
}

// --- METHODES ---

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

bool Building::map_tile_range(MapTile * map_tile) {
	return getSprite()->getPosition().getDistance(map_tile->getSprite()->getPosition())<_sight;
}

void Building::update_range_map_tile_list() {
	int tile_x, tile_y, i,j,k=0;
	tile_x=_map_tile->get_tile_x();
	tile_y=_map_tile->get_tile_y();
	MapTile * map_tile;
	bool end=false;

	while(!end) {
		end=true;
		for(i=tile_x-k;i<tile_x+k+1;i++) {
			for(j=tile_y-k;j<tile_y+k+1;j++) {
				if( ( i==tile_x-k || i==tile_x+k || j==tile_y-k || j==tile_y+k ) && i>=0 && i<getGame()->get_display_layer()->get_map_width() && j>=0 && j<getGame()->get_display_layer()->get_map_height() ) {
					map_tile = getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[j][i];
					if(map_tile_range(map_tile)) {
						end=false;
						_range_map_tile_list.push_back(map_tile);
					}
				}
			}
		}
		k+=1;
	}
}


