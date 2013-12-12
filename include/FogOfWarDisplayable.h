#ifndef FOG_OF_WAR_DISPLAYABLE
#define FOG_OF_WAR_DISPLAYABLE

#include "Displayable.h"

class CCTexture2DMutable;

class FogOfWarDisplayable : public Displayable {
	public:
	typedef enum {
		visible,
		unvisible,
		undiscovered,
	} FogStatus;

	private:
		FogStatus _fogStatus;
		CCTexture2DMutable * _texture;

		void update();

	public:
		FogOfWarDisplayable(float x, float y, Game * game, Layer * layer, FogStatus fogStatus);
		virtual ~FogOfWarDisplayable();

		virtual Displayable::DisplayableType getType() { return Displayable::fogOfWarDisplayableType; }

		FogStatus get_fogStatus() { return _fogStatus; }
		void set_fogStatus(FogStatus fogStatus);
};

#endif
