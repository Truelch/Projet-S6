#include "HudLayer.h"

#include "Game.h"
#include "Hud.h"
#include "EGLView.h"

HudLayer::HudLayer(Game * game, const char * filename): Layer(game) {
	CCPoint origine = EGLView::sharedOpenGLView()->getVisibleOrigin();
	CCSize size = EGLView::sharedOpenGLView()->getVisibleSize();
	_hud = new Hud(origine.x+size.width/2.0,origine.y+size.height/2.0,filename,game,this);
	_hud->getSprite()->setScaleX(size.width/_hud->getSprite()->getTextureRect().size.width);
	_hud->getSprite()->setScaleY(size.height/_hud->getSprite()->getTextureRect().size.height);
}

HudLayer::~HudLayer() {
	delete _hud;
}
