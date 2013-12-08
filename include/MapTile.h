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
		float get_min_x();
		float get_max_x();
		float get_min_y();
		float get_max_y();
		CCPoint get_vertex_left_bottom();
		CCPoint get_vertex_left_top();
		CCPoint get_vertex_right_bottom();
		CCPoint get_vertex_right_top();
		bool get_crossUp() { return _crossUp; }
		bool get_crossDown() { return _crossDown; }
		bool get_crossRight() { return _crossRight; }
		bool get_crossLeft() { return _crossLeft; }
		bool test_achievable();

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
