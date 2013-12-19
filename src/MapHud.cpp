
#include "MapHud.h"

#include "Game.h"
#include "Layer.h"
#include "CCTexture2DMutable.h"
#include "DisplayLayer.h"
#include "TileLayer.h"
#include "HudLayer.h"
#include "Player.h"
#include "EGLView.h"
#include "Unit.h"

MapHud::MapHud(int x, int y, float width, float height, Game * game, Layer * layer): HudItem(x,y,CCSprite::create(),HudItem::mapButtonType,game,layer) {
	int width_map = getGame()->get_display_layer()->get_map_width();
	int height_map = getGame()->get_display_layer()->get_map_height();
	int bytes = width_map * height_map * 4;
	void* textureData = malloc(bytes);
	memset(textureData, INT32_MAX, bytes);

	_texture = new CCTexture2DMutable();
	_texture->initWithData(textureData, kCCTexture2DPixelFormat_RGBA8888, width_map, height_map, CCSize(width_map,height_map));

	std::string id;
	for(x=0;x<width_map;x++) {
		for(y=0;y<height_map;y++) {
			_texture->setPixelAt(CCPointMake(x,height_map-y-1),ccc4(0,0,0,255));
		}
	}
	_texture->apply();
	_texture->setAliasTexParameters();
	getSprite()->initWithTexture(_texture);
	_texture->autorelease();

	float scale = fmaxf( width/getSprite()->getTextureRect().size.width,height/getSprite()->getTextureRect().size.height );
	getSprite()->setScale(scale);

	textureData = malloc(bytes);
	memset(textureData, INT32_MAX, bytes);
	_texture_screen_edge = new CCTexture2DMutable();
	_texture_screen_edge->initWithData(textureData, kCCTexture2DPixelFormat_RGBA8888, width_map, height_map, CCSize(width_map,height_map));

	for(x=0;x<width_map;x++) {
		for(y=0;y<height_map;y++) {
			_texture_screen_edge->setPixelAt(CCPointMake(x,height_map-y-1),ccc4(0,0,0,0));
		}
	}
	_texture_screen_edge->apply();
	_texture_screen_edge->setAliasTexParameters();
	_sprite_screen_edge = CCSprite::createWithTexture(_texture_screen_edge);
	getSprite()->addChild(_sprite_screen_edge);
	_sprite_screen_edge->setPositionX(getSprite()->getTextureRect().size.width/2.0);
	_sprite_screen_edge->setPositionY(getSprite()->getTextureRect().size.height/2.0);
	_texture_screen_edge->autorelease();

	update_screen_edge();

	textureData = malloc(bytes);
	memset(textureData, INT32_MAX, bytes);
	_texture_unit = new CCTexture2DMutable();
	_texture_unit->initWithData(textureData, kCCTexture2DPixelFormat_RGBA8888, width_map, height_map, CCSize(width_map,height_map));

	for(x=0;x<width_map;x++) {
		for(y=0;y<height_map;y++) {
			_texture_unit->setPixelAt(CCPointMake(x,height_map-y-1),ccc4(0,0,0,0));
		}
	}
	_texture_unit->apply();
	_texture_unit->setAliasTexParameters();
	_sprite_unit = CCSprite::createWithTexture(_texture_unit);
	getSprite()->addChild(_sprite_unit);
	_sprite_unit->setPositionX(getSprite()->getTextureRect().size.width/2.0);
	_sprite_unit->setPositionY(getSprite()->getTextureRect().size.height/2.0);
	_texture_unit->autorelease();

	update_unit();
}

MapHud::~MapHud() {
	delete _texture;
	delete _texture_screen_edge;
	delete _sprite_screen_edge;
	delete _texture_unit;
	delete _sprite_unit;
}

void MapHud::update_unit() {
	int tile_x,tile_y;
	Container<Unit> unit_container;
	int width_map = getGame()->get_display_layer()->get_map_width();
	int height_map = getGame()->get_display_layer()->get_map_height();
	for(tile_x=0;tile_x<width_map;tile_x++) {
		for(tile_y=0;tile_y<height_map;tile_y++) {
			unit_container = getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[tile_y][tile_x]->get_unit_container();
			if(!getGame()->get_main_player()->get_map_tile_info()[tile_y][tile_x].discovered)
				_texture_unit->setPixelAt(CCPointMake(tile_x,height_map-tile_y-1),ccc4(0,0,0,0));
			else if(unit_container.get_number_t()>0) {
				if(unit_container.get_t(0)->getPlayer()==getGame()->get_main_player())
					_texture_unit->setPixelAt(CCPointMake(tile_x,height_map-tile_y-1),ccc4(0,0,255,128));
				else
					_texture_unit->setPixelAt(CCPointMake(tile_x,height_map-tile_y-1),ccc4(255,0,0,128));
			}
			else
				_texture_unit->setPixelAt(CCPointMake(tile_x,height_map-tile_y-1),ccc4(0,0,0,0));
		}
	}
	_texture_unit->apply();
}

void MapHud::on_moveable_change_map_tile(int x, int y, Moveable * moveable) {
	update_unit();
}

void MapHud::update_screen_edge() {
	int min_tile_x, min_tile_y, max_tile_x, max_tile_y;
	float min_x, min_y, max_x, max_y;
	CCSize frameSize = EGLView::sharedOpenGLView()->getFrameSize();
	CCPoint point;
	point = getGame()->convert_opengl_point_to_layer_point(0,0,getGame()->get_display_layer());
	min_x = point.x;
	max_y = point.y;
	point = getGame()->convert_opengl_point_to_layer_point(frameSize.width,frameSize.height,getGame()->get_display_layer());
	max_x = point.x;
	min_y = point.y;
	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(min_x,min_y,min_tile_x,min_tile_y);
	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(max_x,max_y,max_tile_x,max_tile_y);
	int width_map = getGame()->get_display_layer()->get_map_width();
	int height_map = getGame()->get_display_layer()->get_map_height();

	if(min_tile_x<0) min_tile_x=0;
	else if(min_tile_x>=width_map) min_tile_x=width_map-1;
	if(max_tile_x<0) max_tile_x=0;
	else if(max_tile_x>=width_map) max_tile_x=width_map-1;
	if(min_tile_y<0) min_tile_y=0;
	else if(min_tile_y>=height_map) min_tile_y=height_map-1;
	if(max_tile_y<0) max_tile_y=0;
	else if(max_tile_y>=height_map) max_tile_y=height_map-1;

	int tile_x,tile_y;
	for(tile_x=0;tile_x<width_map;tile_x++) {
		for(tile_y=0;tile_y<height_map;tile_y++) {
			if( tile_x>=min_tile_x && tile_x<=max_tile_x && tile_y>=min_tile_y && tile_y<=max_tile_y && ( tile_x==min_tile_x || tile_x==max_tile_x || tile_y==min_tile_y || tile_y==max_tile_y) )
				_texture_screen_edge->setPixelAt(CCPointMake(tile_x,height_map-tile_y-1),ccc4(255,255,255,128));
			else
				_texture_screen_edge->setPixelAt(CCPointMake(tile_x,height_map-tile_y-1),ccc4(0,0,0,0));
		}
	}
	_texture_screen_edge->apply();
}

void MapHud::on_screen_change() {
	update_screen_edge();
}

void MapHud::on_player_range_tile(int x, int y, Player * player) {
	int height_map = getGame()->get_display_layer()->get_map_height();
	if(player==getGame()->get_main_player()) {
		_texture->setPixelAt(CCPointMake(x,height_map-y-1), getGame()->get_display_layer()->get_sprite_map()[getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[y][x]->get_id()].colorMap);
	}
	_texture->apply();
}

void MapHud::on_player_unrange_tile(int x, int y, Player * player) {
	int height_map = getGame()->get_display_layer()->get_map_height();
	ccColor4B color = getGame()->get_display_layer()->get_sprite_map()[getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[y][x]->get_id()].colorMap;
	color.a=128;
	if(player==getGame()->get_main_player()) {
		_texture->setPixelAt(CCPointMake(x,height_map-y-1), color);
	}
	_texture->apply();
}

