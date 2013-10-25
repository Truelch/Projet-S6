#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include "cocos2d.h"

using namespace cocos2d;

class Displayable : public CCSprite
{
	public:
		Displayable();
		Displayable(float x, float y, float rotation, const char * filename);
};

#endif
