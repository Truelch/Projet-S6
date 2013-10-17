#include "Displayable.h"

Displayable::Displayable(): CCSprite() {
	//
}

Displayable::Displayable(float x, float y, float rotation, const char * filename): CCSprite() {
	initWithFile(filename);
	setPosition(ccp(x,y)); //cpp(x,y) = CCPointMake((float)x, (float)y) 
	setRotation(rotation);
}

