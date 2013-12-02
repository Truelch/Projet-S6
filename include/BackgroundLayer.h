#ifndef BACKGROUND_LAYER
#define BACKGROUND_LAYER

#include <vector>

#include "Layer.h"
#include "MapDisplayable.h"

class BackgroundLayer : public Layer {
	public:
		BackgroundLayer();
		BackgroundLayer(Game * game);


		std::vector<std::vector<MapDisplayable *>>& get_map_displayable_matrix();
	
	private:
		std::vector<std::vector<MapDisplayable *>> _map_displayable_matrix;
};

#endif
