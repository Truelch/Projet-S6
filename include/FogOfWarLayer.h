#ifndef FOG_OF_WAR_LAYER
#define FOG_OF_WAR_LAYER

#include "Layer.h"

class FogOfWarDisplayable;

class FogOfWarLayer : public Layer {
	private:
		std::vector<std::vector<FogOfWarDisplayable *> > _map_fog_matrix;
		std::vector<FogOfWarDisplayable *> _fog_og_war_to_update;

	public:
		FogOfWarLayer(Game * game);

		std::vector<std::vector<FogOfWarDisplayable *> >& get_map_fog_matrix() { return _map_fog_matrix; }

		void add_fog_og_war_to_update(FogOfWarDisplayable * fogOfWarDisplayable );
		void update();
};

#endif
