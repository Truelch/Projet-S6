#ifndef FOG_OF_WAR_LAYER
#define FOG_OF_WAR_LAYER

#include "Layer.h"

class FogOfWarDisplayable;

class FogOfWarLayer : public Layer {
	private:
		std::vector<std::vector<FogOfWarDisplayable *> > _map_fog_matrix;

	public:
		FogOfWarLayer(Game * game);

		std::vector<std::vector<FogOfWarDisplayable *> >& get_map_fog_matrix() { return _map_fog_matrix; }
};

#endif
