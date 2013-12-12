#ifndef HUD_LAYER
#define HUD_LAYER

#include "Layer.h"

class Hud;
class Game;

class HudLayer : public Layer {
	private:
		Hud * _hud;

	public:
		HudLayer(Game * game, const char * filename);
		virtual ~HudLayer();

		Hud * get_hud() { return _hud; }
};

#endif
