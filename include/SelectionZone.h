#ifndef SELECTION_ZONE
#define SELECTION_ZONE

#include "Displayable.h"

#include "CCTexture2DMutable.h"

class Unit;

class SelectionZone : public Displayable {
	public:
		SelectionZone(CCPoint p1, CCPoint p2, Game * game, Layer * layer, ccColor4B color);
		virtual ~SelectionZone();
		
		cocos2d::CCPoint getP1() { return _p1; }
		cocos2d::CCPoint getP2() { return _p2; }
		ccColor4B getColor() { return _color; }

		void setP1(cocos2d::CCPoint p1) { _p1 = p1; }
		void setP2(cocos2d::CCPoint p2) { _p2 = p2; }
		void setColor(ccColor4B color) { _color = color; }

		std::vector<Unit *> get_list_unit();

		void update();
	private:

		CCPoint _p1,_p2;
		CCTexture2DMutable* _texture;
		ccColor4B _color;
};

#endif
