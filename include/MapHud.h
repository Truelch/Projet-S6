#ifndef MAP_HUD
#define MAP_HUD

#include "HudItem.h"

class Game;
class Layer;
class CCTexture2DMutable;

class MapHud : public HudItem {
	public:
		MapHud(int x, int y, float width, float height, Game * game, Layer * layer);
		virtual ~MapHud();

		void update_screen_edge();
		void update_unit();
		virtual void on_player_range_tile(int x, int y, Player * player);
		virtual void on_player_unrange_tile(int x, int y, Player * player);
		virtual void on_screen_change();
		virtual void on_moveable_change_map_tile(int x, int y, Moveable * moveable);
		virtual void on_unit_destroyed(Unit * unit);

	private:
		CCTexture2DMutable * _texture;
		CCTexture2DMutable * _texture_screen_edge;
		CCSprite * _sprite_screen_edge;
		CCTexture2DMutable * _texture_unit;
		CCSprite * _sprite_unit;
};

#endif
