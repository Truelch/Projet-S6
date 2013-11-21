#include "LayerRGBA.h"

#include "Scene.h"
#include "TileLayer.h"
#include <iostream>

using namespace std;


LayerRGBA::LayerRGBA(): CCLayerRGBA(), _scene(NULL)
{
	init();
}

LayerRGBA::LayerRGBA(Scene * scene): CCLayerRGBA(), _scene(scene)
{
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

