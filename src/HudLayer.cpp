#include "HudLayer.h"

#include "Game.h"
#include "Hud.h"
#include "EGLView.h"
#include "MapHud.h"

HudLayer::HudLayer(Game * game, const char * filename): Layer(game) {
	CCPoint origine = EGLView::sharedOpenGLView()->getVisibleOrigin();
	CCSize size = EGLView::sharedOpenGLView()->getVisibleSize();

	_hud = new Hud(origine.x+size.width/2.0,origine.y+size.height/2.0,filename,game,this);
	setScaleX(size.width/_hud->getSprite()->getTextureRect().size.width);
	setScaleY(size.height/_hud->getSprite()->getTextureRect().size.height);
}

HudItem * HudLayer::get_hud_item(int index) {
	if(index<(int)_list_hud_item.size()) {
		return _list_hud_item[index];
	}
	return NULL;
}

void HudLayer::remove_hud_item(HudItem * hud_item) {
	delete hud_item;
	_list_hud_item.erase(std::remove(_list_hud_item.begin(), _list_hud_item.end(), hud_item), _list_hud_item.end());
}

void HudLayer::add_hud_item(int x, int y, const char * filename, HudItem::HudItemType hudItemType) {
	_list_hud_item.push_back( new HudItem(x,y, filename, hudItemType, get_game(), this) );
}

void HudLayer::add_map_hud(int x, int y, float width, float height) {
	_list_hud_item.push_back( new MapHud(x,y, width, height, get_game(), this) );
}

HudLayer::~HudLayer() {
	vector<HudItem *>::iterator it;
	for(it=_list_hud_item.begin(); it!=_list_hud_item.end(); it++) delete (*it);
	delete _hud;
}
