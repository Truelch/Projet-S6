#ifndef HUD_ITEM
#define HUD_ITEM

#include "Displayable.h"

class HudItem : public Displayable {
	public:
		typedef enum {
			stopButtonType,
			holdPositionButtonType,
			moveButtonType,
			patrolButtonType,
			retreatButtonType,
		} HudItemType;

		
		HudItem(int x, int y, const char * filename, HudItemType hudItemType,  Game * game, Layer * layer);

		virtual Displayable::DisplayableType getType() { return Displayable::hudItemType; }

		HudItemType getButtonType() { return _hudItemType; }

		int getX() { return _x; }
		int getY() { return _y; }

	private:
		HudItemType _hudItemType;
		int _x, _y;
};

#endif
