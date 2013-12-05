#ifndef BAR_H
#define BAR_H

#include "Displayable.h"
#include "CCTexture2DMutable.h"

class Bar : public Displayable {
	public:
		Bar(Game * game, Layer * layer, float x, float y, float value, int width, int height, ccColor4B foregroundColor, ccColor4B backgroundColor);
		~Bar();
		
		void setValue(float value) { _value = value; update(); }
		void set_backgroundColor(ccColor4B color) { _backgroundColor = color; update(); }
		void set_foregroundColor(ccColor4B color) { _foregroundColor = color; update(); }

		float getValue() { return _value; }
		int get_width() { return _width; }
		int get_height() { return _height; }
		ccColor4B get_backgroundColor() { return _backgroundColor; }
		ccColor4B get_foregroundColor() { return _foregroundColor; }

	private:
		void update();

		float _value;
		CCTexture2DMutable * _texture;
		int _width, _height;
		ccColor4B _foregroundColor;
		ccColor4B _backgroundColor;
};

#endif
