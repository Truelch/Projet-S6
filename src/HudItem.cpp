
#include "HudItem.h"

#include "Game.h"
#include "Layer.h"

HudItem::HudItem(int x, int y, const char * filename, HudItemType hudItemType, Game * game, Layer * layer): Displayable(game,CCSprite::create(),layer), _hudItemType(hudItemType), _x(x), _y(y) {
	CCPoint point = getGame()->convert_opengl_point_to_layer_point(x,y,layer);
	getSprite()->initWithFile(filename);
	getSprite()->setPosition(point);
}
