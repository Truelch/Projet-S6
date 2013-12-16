#ifndef FOG_OF_WAR_DISPLAYABLE
#define FOG_OF_WAR_DISPLAYABLE

#include "Displayable.h"

class CCTexture2DMutable;
class FogOfWarLayer;

ccColor4B moyenne_color(ccColor4B color1, ccColor4B color2, float coeff);

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
		bool _update_needed;
		FogOfWarLayer * _fog_of_war_layer;
		int _x, _y;

		void linear_degrad(int x_orig, int y_orig, int x_vect_deg, int y_vect_deg, int x_vect_width, int y_vect_width, ccColor4B color_adjacent);
		void radius_degrad(int x_orig, int y_orig, int x_dest, int y_dest, ccColor4B color_orig, ccColor4B color_dest);
		void fillZone(int x_orig, int y_orig, int width, int height, ccColor4B color);

	public:
		FogOfWarDisplayable(int x, int y, Game * game, FogOfWarLayer * layer, FogStatus fogStatus);
		virtual ~FogOfWarDisplayable();

		virtual Displayable::DisplayableType getType() { return Displayable::fogOfWarDisplayableType; }
		ccColor4B getColor();

		FogStatus get_fogStatus() { return _fogStatus; }
		void set_fogStatus(FogStatus fogStatus);

		void update(); //doit etre appeler uniquement par FogOfWarLayer
		void set_update_needed();

};

#endif
