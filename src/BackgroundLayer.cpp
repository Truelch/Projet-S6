#include "BackgroundLayer.h"

#include "MapDisplayable.h"

BackgroundLayer::BackgroundLayer(): Layer() 
{
	//
}

BackgroundLayer::BackgroundLayer(Game * game): Layer(game) {

}

std::vector<std::vector<MapDisplayable *> >& BackgroundLayer::get_map_displayable_matrix() {
	return _map_displayable_matrix;
}
