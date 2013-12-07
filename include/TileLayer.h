#ifndef TILELAYER_H
#define TILELAYER_H

#include "cocos2d.h"

#include <string>
#include <vector>

#include "Layer.h"
#include "MapTile.h"

using namespace std;

bool test_colision_droiteAB_segemntCD(CCPoint a, CCPoint b, CCPoint c, CCPoint d, int * marge = NULL);

class TileLayer : public Layer
{
	public:
		TileLayer();
		TileLayer(Game * game);
		// --- METHODES ---
		
		// --- GET ---
		std::vector<std::vector<MapTile *> >& get_map_tile_matrix();

		vector<MapTile *> line_through_tile(CCPoint point1, CCPoint point2);
		bool test_line_traversable(CCPoint point1, CCPoint point2);
		bool test_2_tile_crossable(int tile1_x, int tile1_y, int tile2_x, int tile2_y);
		vector<MapTile *> path_finding(int tile1_x, int tile1_y, int tile2_x, int tile2_y);
		
	private:
		std::vector<std::vector<MapTile *> > _map_tile_matrix;
		
		class PathFindingItem {
			private:
				MapTile * _map_tile;
				PathFindingItem * _parent;
				MapTile * _destination;
				vector<PathFindingItem *> _childs;
				int _g_score; //cout depuis l'origine
				int _h_score; //estimation du cout jusqu'a la destination
				int _f_score; //total
			public:
				PathFindingItem(MapTile * map_tile, PathFindingItem * parent, MapTile * destination);

				void set_parent(PathFindingItem * parent);
				void update_f_score();
				int compute_f_score_whith_parent(PathFindingItem * parent);

				MapTile * get_map_tile() { return _map_tile; }
				PathFindingItem * get_parent() { return _parent; }
				MapTile * get_destination() { return _destination; }
				const vector<PathFindingItem *>& get_childs() { return _childs; }
				int get_f_score() { return _f_score; }
				int get_g_score() { return _g_score; }
				int get_h_score() { return _h_score; }
		};
};

#endif
