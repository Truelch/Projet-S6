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
		} HudItemType;

		
		HudItem(float x, float y, const char * filename, HudItemType hudItemType,  Game * game, Layer * layer);

		virtual Displayable::DisplayableType getType() { return Displayable::hudItemType; }

		HudItemType getButtonType() { return _hudItemType; }

	private:
		HudItemType _hudItemType;
};

#endif
