
#include "FogOfWarDisplayable.h"

#include "CCTexture2DMutable.h"
#include "Game.h"
#include "DisplayLayer.h"
#include "FogOfWarLayer.h"

#include <stdio.h>

ccColor4B moyenne_color(ccColor4B color1, ccColor4B color2, float coeff) {
	ccColor4B result;
	if(coeff<0) coeff=0;
	else if(coeff>1) coeff=1;
	result.r = color1.r*coeff + color2.r*(1-coeff);
	result.g = color1.g*coeff + color2.g*(1-coeff);
	result.b = color1.b*coeff + color2.b*(1-coeff);
	result.a = color1.a*coeff + color2.a*(1-coeff);
	return result;
}

FogOfWarDisplayable::FogOfWarDisplayable(int x, int y, Game * game, FogOfWarLayer * layer, FogStatus fogStatus): Displayable(game, new CCSprite(), layer), _fogStatus(fogStatus), _fog_of_war_layer(layer), _x(x), _y(y) {
	int side = getGame()->get_display_layer()->get_tile_size_pixel();
	int bytes = side * side * 4;
	float cocos_x, cocos_y;
	void* textureData = malloc(bytes);
	memset(textureData, INT32_MAX, bytes);

	_texture = new CCTexture2DMutable();
	_texture->initWithData(textureData, kCCTexture2DPixelFormat_RGBA8888, side, side, CCSize(side,side));

	for(x=0;x<side;x++) {
		for(y=0;y<side;y++) {
			_texture->setPixelAt(CCPointMake(x,y), ccc4(0,0,0,255));
		}
	}
	_texture->apply();

	_texture->setAliasTexParameters();

	set_update_needed();

	getSprite()->initWithTexture(_texture);
	getGame()->get_display_layer()->coordonate_tile_to_cocos2dx(_x,_y,cocos_x,cocos_y);
	getSprite()->setPosition(CCPoint(cocos_x,cocos_y));
	_texture->autorelease();
}

void FogOfWarDisplayable::linear_degrad(int x_orig, int y_orig, int x_vect_deg, int y_vect_deg, int x_vect_width, int y_vect_width, ccColor4B color_adjacent) {
	int x=x_orig,y=y_orig;
	ccColor4B color = getColor();
	float coeff;

	while((x_vect_width!=0 && x-x_orig!=x_vect_width) || (y_vect_width!=0 && y-y_orig!=y_vect_width)) {
		if(x_vect_deg!=0) x=x_orig;
		else y=y_orig;

		while((x_vect_deg!=0 && x-x_orig!=x_vect_deg) || (y_vect_deg!=0 && y-y_orig!=y_vect_deg)) {
			if(x_vect_deg!=0) coeff = ((float)(x-x_orig))/x_vect_deg;
			else coeff = ((float)(y-y_orig))/y_vect_deg;
			_texture->setPixelAt(CCPointMake(x, y), moyenne_color(color_adjacent,color,coeff));
			if(x_vect_deg>0) x++;
			else if(x_vect_deg<0) x--;
			else if(y_vect_deg>0) y++;
			else y--;
		}
		if(x_vect_width>0) x++;
		else if(x_vect_width<0) x--;
		else if(y_vect_width>0) y++;
		else y--;
	}
}

void FogOfWarDisplayable::radius_degrad(int x_orig, int y_orig, int x_dest, int y_dest, ccColor4B color_orig, ccColor4B color_dest) {
	float radius = fminf(abs(x_orig-x_dest),abs(y_orig-y_dest));
	int x,y,x_max,y_max,i,j;
	if(x_orig<x_dest) {
		x=x_orig;
		x_max=x_dest;
	}
	else {
		x=x_dest;
		x_max=x_orig;
	}
	if(y_orig<y_dest) {
		y=y_orig;
		y_max=y_dest;
	}
	else {
		y=y_dest;
		y_max=y_orig;
	}
	for(i=x;i<=x_max;i++) {
		for(j=y;j<=y_max;j++) {
			_texture->setPixelAt(CCPointMake(i,j), moyenne_color(color_dest,color_orig,sqrt(((i-x_orig)*(i-x_orig))+((j-y_orig)*(j-y_orig)))/radius));
		}
	}
}

ccColor4B FogOfWarDisplayable::getColor() {
	if(_fogStatus==visible)
		return ccc4(0,0,0,0);
	if(_fogStatus==unvisible)
		return ccc4(0,0,0,200);
	return ccc4(0,0,0,255);
}

void FogOfWarDisplayable::fillZone(int x_orig, int y_orig, int width, int height, ccColor4B color) {
	int x,y;
	for(x=x_orig;x<x_orig+width;x++) {
		for(y=y_orig;y<y_orig+height;y++) {
			_texture->setPixelAt(CCPointMake(x,y), color);
		}
	}
}

void FogOfWarDisplayable::update() {
	int side = getGame()->get_display_layer()->get_tile_size_pixel();
	fillZone(10,10,side-20,side-20,getColor());
	bool presence_color_left, presence_color_right, presence_color_top, presence_color_bottom;
	ccColor4B color_left, color_right, color_top, color_bottom;

	//fondu right
	if(_x==getGame()->get_display_layer()->get_map_width()-1 || getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y][_x+1]->getColor().a<=getColor().a) {
		presence_color_right=false;
		fillZone(side-10,10,10,side-20,getColor());
	}
	else {
		presence_color_right=true;
		color_right=getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y][_x+1]->getColor();
		linear_degrad(side-10,10,10,0,0,side-20,color_right);
	}

	
	//fondu left
	if(_x==0 || getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y][_x-1]->getColor().a<=getColor().a) {
		presence_color_left=false;
		fillZone(0,10,10,side-20,getColor());
	}
	else {
		presence_color_left=true;
		color_left=getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y][_x-1]->getColor();
		linear_degrad(9,10,-10,0,0,side-20,color_left);
	}

	//fondu top
	if(_y==getGame()->get_display_layer()->get_map_height()-1 || getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y+1][_x]->getColor().a<=getColor().a) {
		presence_color_top=false;
		fillZone(10,0,side-20,10,getColor());
	}
	else {
		presence_color_top=true;
		color_top=getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y+1][_x]->getColor();
		linear_degrad(10,9,0,-10,side-20,0,color_top);
	}

	//fondu bottom
	if(_y==0 || getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y-1][_x]->getColor().a<=getColor().a) {
		presence_color_bottom=false;
		fillZone(10,side-10,side-20,10,getColor());
	}
	else {
		presence_color_bottom=true;
		color_bottom=getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y-1][_x]->getColor();
		linear_degrad(10,side-10,0,10,side-20,0,color_bottom);
	}

	((void)(presence_color_left));
	((void)(presence_color_top));
	((void)(presence_color_right));
	((void)(presence_color_bottom));

	//fondu coin left top
	if(presence_color_left && presence_color_top)
		radius_degrad(9,9,0,0,getColor(),getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y+1][_x-1]->getColor());
	else if(presence_color_left)
		linear_degrad(9,10,-10,0,0,-10,color_left);
	else if(presence_color_top)
		linear_degrad(9,9,0,-10,-10,0,color_top);
	else if(_x!=0 && _y!=getGame()->get_display_layer()->get_map_height()-1 && getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y+1][_x-1]->getColor().a>getColor().a)
		radius_degrad(0,0,9,9,getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y+1][_x-1]->getColor(),getColor());
	else
		fillZone(0,0,10,10,getColor());

	//fondu coin right top
	if(presence_color_right && presence_color_top)
		radius_degrad(side-10,9,side,0,getColor(),getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y+1][_x+1]->getColor());
	else if(presence_color_right)
		linear_degrad(side-10,9,10,0,0,-10,color_right);
	else if(presence_color_top)
		linear_degrad(side-10,9,0,-10,10,0,color_top);
	else if(_x!=getGame()->get_display_layer()->get_map_width()-1 && _y!=getGame()->get_display_layer()->get_map_height()-1 && getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y+1][_x+1]->getColor().a>getColor().a) {
		radius_degrad(side,0,side-10,9,getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y+1][_x+1]->getColor(),getColor());
	}
	else
		fillZone(side-10,0,10,10,getColor());
	
	//fondu coin right bottom
	if(presence_color_right && presence_color_bottom)
		radius_degrad(side-10,side-10,side,side,getColor(),getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y-1][_x+1]->getColor());
	else if(presence_color_right)
		linear_degrad(side-10,side-10,10,0,0,10,color_right);
	else if(presence_color_bottom)
		linear_degrad(side-10,side-10,0,10,10,0,color_bottom);
	else if(_x!=getGame()->get_display_layer()->get_map_width()-1 && _y!=0 && getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y-1][_x+1]->getColor().a>getColor().a)
		radius_degrad(side,side,side-10,side-10,getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y-1][_x+1]->getColor(),getColor());
	else
		fillZone(side-10,side-10,10,10,getColor());
	
	//fondu coin left bottom
	if(presence_color_left && presence_color_bottom)
		radius_degrad(9,side-10,0,side,getColor(),getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y-1][_x-1]->getColor());
	else if(presence_color_left)
		linear_degrad(9,side-10,-10,0,0,10,color_left);
	else if(presence_color_bottom)
		linear_degrad(9,side-10,0,10,-10,0,color_bottom);
	else if(_x!=0 && _y!=0 && getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y-1][_x-1]->getColor().a>getColor().a)
		radius_degrad(0,side,9,side-10,getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[_y-1][_x-1]->getColor(),getColor());
	else
		fillZone(0,side-10,10,10,getColor());
	
	_texture->apply();

}

void FogOfWarDisplayable::set_update_needed() {
	_fog_of_war_layer->add_fog_og_war_to_update(this);
}

FogOfWarDisplayable::~FogOfWarDisplayable() {
	delete _texture;
}

void FogOfWarDisplayable::set_fogStatus(FogStatus fogStatus) {
	_fogStatus=fogStatus;
	set_update_needed();

	CCPoint position = getSprite()->getPosition();
	int tile_x, tile_y;
	int i,j;
	getGame()->get_display_layer()->coordonate_cocos2dx_to_tile(position.x,position.y,tile_x,tile_y);
	for(i=tile_x-1;i<tile_x+2;i++) {
		for(j=tile_y-1;j<tile_y+2;j++) {
			if(j>=0 && j<(int)getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix().size() && i>=0 && i<(int)getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[0].size())
				getGame()->get_display_layer()->get_fog_of_war_layer()->get_map_fog_matrix()[j][i]->set_update_needed();
		}
	}
}
