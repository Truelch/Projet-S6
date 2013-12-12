#ifndef HUD_LAYER
#define HUD_LAYER

#include "Layer.h"

#include <vector>

#include "HudItem.h"

class Hud;
class Game;

class HudLayer : public Layer {
	private:
		Hud * _hud;
		std::vector<HudItem *> _list_hud_item;

	public:
		HudLayer(Game * game, const char * filename);
		virtual ~HudLayer();

		Hud * get_hud() { return _hud; }

		void add_hud_item(int x, int y, const char * filename, HudItem::ButtonType buttonType);
		HudItem * get_hud_item(int index);
		void remove_hud_item(HudItem * hud_item);
		int get_number_hud_item() { return _list_hud_item.size(); }
};

#endif
