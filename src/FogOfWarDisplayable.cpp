
#include "FogOfWarDisplayable.h"

#include "CCTexture2DMutable.h"
#include "Game.h"
#include "DisplayLayer.h"
#include "FogOfWarLayer.h"

#define SIDE 130

FogOfWarDisplayable::FogOfWarDisplayable(float x, float y, Game * game, Layer * layer, FogStatus fogStatus): Displayable(game, new CCSprite(), layer), _fogStatus(fogStatus) {
	int bytes = SIDE * SIDE * 4;
	void* textureData = malloc(bytes);
	memset(textureData, INT32_MAX, bytes);

	_texture = new CCTexture2DMutable();
	_texture->initWithData(textureData, kCCTexture2DPixelFormat_RGBA8888, SIDE, SIDE, CCSize(SIDE,SIDE));

	_texture->setAliasTexParameters();

	update();

	getSprite()->initWithTexture(_texture);
	getSprite()->setPosition(CCPoint(x,y));
	_texture->autorelease();
}

void FogOfWarDisplayable::update() {

	for (int x = 0; x < SIDE; x++) {
		for (int y = 0; y < SIDE; y++) {
			if(_fogStatus==visible)
				_texture->setPixelAt(CCPointMake(x, y), ccc4(0,0,0,0));
			else if(_fogStatus==unvisible)
				_texture->setPixelAt(CCPointMake(x, y), ccc4(0,0,0,200));
			else if(_fogStatus==undiscovered)
				_texture->setPixelAt(CCPointMake(x, y), ccc4(0,0,0,255));
		}
	}

	_texture->apply();

}

FogOfWarDisplayable::~FogOfWarDisplayable() {
	delete _texture;
}

void FogOfWarDisplayable::set_fogStatus(FogStatus fogStatus) {
	_fogStatus=fogStatus;
	update();
	/*
	CCPoint position = getSprite()->getPosition();
	int tile_x, tile_y;
	int i,j;
	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(position.x,position.y,tile_x,tile_y);
	for(i=tile_x-1;i<tile_x+2;i++) {
		for(j=tile_y-1;j<tile_y+2;j++) {
			if(j>=0 && j<(int)getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix().size() && i>=0 && i<(int)getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[0].size()) getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[j][i]->update();
		}
	}
	*/
}

