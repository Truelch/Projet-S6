#include "Hud.h"

Hud::Hud(): Displayable() {
	//
}

Hud::Hud(float x, float y, const char * filename, Scene * scene): Displayable(x,y,0,filename,scene)
{
	//
}
