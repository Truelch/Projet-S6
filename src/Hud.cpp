#include "Hud.h"

Hud::Hud(): Displayable() {
	//
	std::cout << "Constructeur de Hud" << std::endl;
}

Hud::Hud(float x, float y, const char * filename, Scene * scene, Layer * layer): Displayable(x,y,0,filename,scene,layer)
{
	//
	std::cout << "Constructeur de Hud" << std::endl;
}
