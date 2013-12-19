
#include "VictoryScene.h"

#include "EGLView.h"

VictoryScene::VictoryScene(const char * filename): _victory_image(cocos2d::CCSprite::create(filename)), _layer(new cocos2d::CCLayer()) {
	addChild(_layer);
	_layer->addChild(_victory_image);

	cocos2d::CCPoint origine = EGLView::sharedOpenGLView()->getVisibleOrigin();
	cocos2d::CCSize size = EGLView::sharedOpenGLView()->getVisibleSize();
	_victory_image->setPosition(cocos2d::CCPoint(origine.x+size.width/2.0,origine.y+size.height/2.0));
	_layer->setScaleX(size.width/_victory_image->getTextureRect().size.width);
	_layer->setScaleY(size.height/_victory_image->getTextureRect().size.height);
	_victory_image->setPosition(cocos2d::CCPoint(270,180));

	int x,y;
	get_center_of_screen(x,y);
	cocos2d::CCPoint point = convert_opengl_point_to_layer_point(x,y,_layer);
	point.x+=_victory_image->getTextureRect().size.width/4.0;
	point.y+=_victory_image->getTextureRect().size.height/4.0;
	_victory_image->setPosition(point);
}

VictoryScene::~VictoryScene() {
	delete _victory_image;
}

void VictoryScene::key_press(int key) {
	if(key=='Q') cocos2d::CCDirector::sharedDirector()->end();
}
