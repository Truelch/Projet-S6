
#include "HudItem.h"

HudItem::HudItem(float x, float y, const char * filename, HudItemType hudItemType, Game * game, Layer * layer): Displayable(x,y,0,filename,game,layer), _hudItemType(hudItemType) {
}
