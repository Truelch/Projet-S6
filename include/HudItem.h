#ifndef HUD_ITEM
#define HUD_ITEM

#include "Displayable.h"

class HudItem : public Displayable {
	public:
		typedef enum {
			stopType,
			holdPositionType,
			moveType,
			patrolType,
		} ButtonType;

		
		HudItem(float x, float y, const char * filename, ButtonType buttonType,  Game * game, Layer * layer);

		virtual Displayable::DisplayableType getType() { return Displayable::hudItemType; }

		ButtonType getButtonType() { return _buttonType; }

	private:
		ButtonType _buttonType;
};

#endif
