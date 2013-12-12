
#include "HudItem.h"

HudItem::HudItem(float x, float y, const char * filename, ButtonType buttonType, Game * game, Layer * layer): Displayable(x,y,0,filename,game,layer), _buttonType(buttonType) {
}
