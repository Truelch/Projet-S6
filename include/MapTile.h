#ifndef MAP_TILE_H
#define MAP_TILE_H

#include "MapDisplayable.h"
#include "Container.h"

class Building;

class MapTile : public MapDisplayable {
	public:
		MapTile();
		MapTile(float x, float y, const char * filename, Game * game, Layer * layer, bool crossUp = true, bool crossDown = true, bool crossRight = true, bool crossLeft = true);

		Building * get_building() { return _building; }
		Container<Unit>& get_unit_container() { return _unit_container; }
		virtual Displayable::DisplayableType getType() { return Displayable::mapTileType; }
		int get_tile_x() { return _tile_x; }
		int get_tile_y() { return _tile_y; }

		void set_building( Building * building ) { _building = building; }

	private:
		bool _crossUp;
		bool _crossDown;
		bool _crossRight;
		bool _crossLeft;

		Building * _building;
		Container<Unit> _unit_container;

		int _tile_x, _tile_y;
};

#endif
