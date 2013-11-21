#include "LayerRGBA.h"

#include "Scene.h"
#include "TileLayer.h"
#include <iostream>

using namespace std;


LayerRGBA::LayerRGBA(): CCLayerRGBA(), _scene(NULL)
{
	std::cout << "Constructeur de LayerRGBA" << std::endl;
	init();
}

LayerRGBA::LayerRGBA(Scene * scene): CCLayerRGBA(), _scene(scene)
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

