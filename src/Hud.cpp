#include "Hud.h"

Hud::Hud(): Displayable() {
	//
	std::cout << "Constructeur de Hud" << std::endl;
}

Hud::Hud(float x, float y, const char * filename, Scene * scene): Displayable(x,y,0,filename,scene)
{
	//
	std::cout << "Constructeur de Hud" << std::endl;
}
