#include "Hud.h"

#include "Game.h"

Hud::Hud(): Displayable() {
	//
	std::cout << "Constructeur de Hud" << std::endl;
}

Hud::Hud(float x, float y, const char * filename, Game * game, Layer * layer): Displayable(x,y,0,filename,game,layer)
{
	//
	std::cout << "Constructeur de Hud" << std::endl;
	//getSprite()->setScaleX(0.9);
}
