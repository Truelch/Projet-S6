#include "Scene.h"
#include "EventHandler.h"
#include "DisplayLayer.h"
#include "Scene.h"
#include "EGLView.h"

#include "CCArmature/external_tool/GLES-Render.h"

Scene::Scene(): CCScene(),_mouse_x(0), _mouse_y(0), _old_x(0), _old_y(0), _mouse_initiate(false) {
	_event_handler = new EventHandler(); 

	//box2d world
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	_world = new b2World(gravity);

	_debug_draw = new cocos2d::extension::GLESDebugDraw( PTM_RATIO );
	_world->SetDebugDraw(_debug_draw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	_debug_draw->SetFlags(flags);

	_cursor_layer = new cocos2d::CCLayer();
	_cursor_layer->setZOrder(3);
	addChild(_cursor_layer);
	_cursor = cocos2d::CCSprite::create("fleche.png");
	_cursor_layer->addChild(_cursor);
}

Scene::~Scene() {
	delete _world;
	delete _event_handler;
	delete _cursor;
	delete _cursor_layer;
}


CCPoint Scene::convert_opengl_point_to_layer_point_with_new_offset(int opengl_x, int opengl_y, cocos2d::CCLayer * layer, float offset_x, float offset_y) {
	CCPoint map_point;
	float cocos_x, cocos_y;
	CCSize frameSize = EGLView::sharedOpenGLView()->getFrameSize();

	opengl_x=frameSize.width/2+((opengl_x-frameSize.width/2)/layer->getScaleX());
	opengl_y=frameSize.height/2+((opengl_y-frameSize.height/2)/layer->getScaleY());

	coordinateOpenglToCocos2dx(opengl_x,opengl_y,cocos_x,cocos_y);

	map_point.x = cocos_x+offset_x;
	map_point.y = cocos_y+offset_y;

	return map_point;
}

CCPoint Scene::convert_opengl_point_to_layer_point(int opengl_x, int opengl_y, cocos2d::CCLayer * layer) {
	float offset_x,offset_y,offset_z;
	layer->getCamera()->getCenterXYZ(&offset_x,&offset_y,&offset_z);

	return convert_opengl_point_to_layer_point_with_new_offset(opengl_x, opengl_y, layer, offset_x, offset_y);
}

void Scene::get_center_of_screen(int& x, int& y) {
	CCSize frame_size = EGLView::sharedOpenGLView()->getFrameSize();
	x=(frame_size.width)/2;
	y=(frame_size.height)/2;
}

void Scene::mouse_move( int x, int y) {
	CCSize frameSize = EGLView::sharedOpenGLView()->getFrameSize();
	if(_mouse_initiate) {
		_mouse_x+=x-_old_x;
		_mouse_y+=y-_old_y;
	}
	else {
		_mouse_x=x;
		_mouse_y=y;
		_mouse_initiate=true;
	}
	_old_x=x;
	_old_y=y;
	if(_mouse_x<0) _mouse_x=0;
	else if(_mouse_x>frameSize.width) _mouse_x=frameSize.width;
	if(_mouse_y<0) _mouse_y=0;
	else if(_mouse_y>frameSize.height) _mouse_y=frameSize.height;

	CCPoint point = convert_opengl_point_to_layer_point(get_mouse_x(),get_mouse_y(),_cursor_layer);
	point.x+=_cursor->getTextureRect().size.width/2.0;
	point.y-=_cursor->getTextureRect().size.height/2.0;
	_cursor->setPosition(point);

}
