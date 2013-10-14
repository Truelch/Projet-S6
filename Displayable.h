#ifndef DISPLAYABLE_CPP
#define DISPLAYABLE_CPP

#include "cocos2d.h"

using namespace cocos2d;

class Displayable : public CCSprite
{
	public:
		Displayable();
		Displayable(float x, float y, float rotation, const char * filename);
		
};

#endif
