#include "Hud.h"

Hud::Hud(): Displayable() {
	//
	std::cout << "Constructeur de Hud" << std::endl;
}

Hud::Hud(float x, float y, const char * filename): Displayable(x,y,0,filename)
{
	//
	std::cout << "Constructeur de Hud" << std::endl;
}
