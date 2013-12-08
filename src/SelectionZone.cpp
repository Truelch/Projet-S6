#include "SelectionZone.h"

#include "Layer.h"
#include "Unit.h"
#include <vector>
#include <cmath>
#include <Container.h>
#include "Game.h"
#include "DisplayLayer.h"
#include "TileLayer.h"

SelectionZone::SelectionZone(CCPoint p1, CCPoint p2, Game * game, Layer * layer, ccColor4B color): Displayable(game, CCSprite::create(), layer), _p1(p1), _p2(p2), _texture(new CCTexture2DMutable()), _color(color) {
	void* textureData = malloc(4);
	memset(textureData, INT32_MAX, 4);

	_texture->initWithData(textureData, kCCTexture2DPixelFormat_RGBA8888, 1, 1, CCSize(1,1));
	_texture->setAliasTexParameters();

	update();

	getSprite()->initWithTexture(_texture);
	layer->addChild(getSprite());
	_texture->autorelease();
}

SelectionZone::~SelectionZone() {
	delete _texture;
}

void SelectionZone::update() {
	_texture->setPixelAt(CCPointMake(0, 0), _color);
	_texture->apply();

	getSprite()->setScaleX(std::abs(_p1.x-_p2.x)*2.1);
	getSprite()->setScaleY(std::abs(_p1.y-_p2.y)*2.1);
	getSprite()->setPosition(CCPoint((_p1.x+_p2.x)/2.0,(_p1.y+_p2.y)/2.0));
}

std::vector<Unit *> SelectionZone::get_list_unit() {
	int tile_x_min, tile_x_max, tile_y_min, tile_y_max, i,j,k;
	float x_min,x_max,y_min,y_max;
	CCPoint point;
	std::vector<Unit *> result;
	Container<Unit> unit_container;
	if(_p1.x>_p2.x) {
		x_max=_p1.x;
		x_min=_p2.x;
	}
	else {
		x_max=_p2.x;
		x_min=_p1.x;
	}
	if(_p1.y>_p2.y) {
		y_max=_p1.y;
		y_min=_p2.y;
	}
	else {
		y_max=_p2.y;
		y_min=_p1.y;
	}

	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(x_min,y_min,tile_x_min,tile_y_min);
	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(x_max,y_max,tile_x_max,tile_y_max);

	for(i=tile_x_min;i<tile_x_max+1;i++) {
		for(j=tile_y_min;j<tile_y_max+1;j++) {
			if(j>=0 && j<(int)getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix().size() && i>=0 && i<(int)getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[0].size()) {
				unit_container = getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[j][i]->get_unit_container();
				for(k=0;k<unit_container.get_number_t();k++) {
					if( i!=tile_x_min && i!=tile_x_max && j!=tile_y_min && j!=tile_y_max ) {
						result.push_back(unit_container.get_t(k));
					}
					else {
						point = unit_container.get_t(k)->getSprite()->getPosition();
						if(point.x>=x_min && point.x<=x_max && point.y>=y_min && point.y<=y_max) {
							result.push_back(unit_container.get_t(k));
						}
					}
				}
			}
		}
	}
	return result;
}

