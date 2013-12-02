#include "LayerRGBA.h"

#include "Game.h"
#include "TileLayer.h"
#include <iostream>

using namespace std;


LayerRGBA::LayerRGBA(): CCLayerRGBA(), _game(NULL)
{
	std::cout << "Constructeur de LayerRGBA" << std::endl;
	init();
}

LayerRGBA::LayerRGBA(Game * game): CCLayerRGBA(), _game(game)
{
	std::cout << "Constructeur de LayerRGBA" << std::endl;
	init();
}

bool LayerRGBA::init()
{
	if( !CCLayer::init() ) {
		return false;
	}
	//Opacité régler à 50% puis variable
	setOpacity(128);
	//Couleur noire
	
	return true;
}

