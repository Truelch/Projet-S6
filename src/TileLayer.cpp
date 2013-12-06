#include "TileLayer.h"

#include <algorithm>

#include "Box2D/Box2D.h"
#include "Game.h"
#include "DisplayLayer.h"

bool test_colision_droiteAB_segemntCD(CCPoint a, CCPoint b, CCPoint c, CCPoint d) {
	b2Vec2 ab(b.x-a.x, b.y-a.y);
	b2Vec2 ac(c.x-a.x, c.y-a.y); 
	b2Vec2 ad(d.x-a.x, d.y-a.y); 
	float cross_ab_ac=b2Cross(ab,ac);
	float cross_ab_ad=b2Cross(ab,ad);
	return (cross_ab_ac>=0 && cross_ab_ad<=0) || (cross_ab_ac<=0 && cross_ab_ad>=0);
}

TileLayer::TileLayer(): Layer()
{
	std::cout << "Constructeur de TileLayer" << std::endl;
}


TileLayer::TileLayer(Game * game): Layer(game)
{
	std::cout << "Constructeur de TileLayer" << std::endl;
}


// --- GET ---
std::vector<std::vector<MapTile *> >& TileLayer::get_map_tile_matrix()
{
	return _map_tile_matrix;
}

// --- SET ---


// --- METHODES ---

bool TileLayer::test_line_traversable(CCPoint point1, CCPoint point2) {
	vector<MapTile *> list_map = line_through_tile(point1,point2);
	if(list_map.size()==0) return false;
	unsigned int i;
	for(i=0;i<list_map.size()-1;i++) {
		if(!test_2_tile_crossable(list_map[i]->get_tile_x(),list_map[i]->get_tile_y(),list_map[i+1]->get_tile_x(),list_map[i+1]->get_tile_y())) return false;
	}
	return true;
}

vector<MapTile *> TileLayer::line_through_tile(CCPoint point1, CCPoint point2) {
	int tile1_x, tile1_y, tile2_x, tile2_y;
	get_game()->get_display_layer()->coordonate_cocos2dx_to_tile(point1.x,point1.y,tile1_x,tile1_y);
	get_game()->get_display_layer()->coordonate_cocos2dx_to_tile(point2.x,point2.y,tile2_x,tile2_y);
	vector<MapTile *> result;
	MapTile * map_tile;

	while(true) {

		if(tile1_y<0 || tile1_y>=(int)_map_tile_matrix.size() || tile1_x<0 || tile1_x>=(int)_map_tile_matrix[0].size()) return result;
		if(tile2_y<0 || tile2_y>=(int)_map_tile_matrix.size() || tile2_x<0 || tile2_x>=(int)_map_tile_matrix[0].size()) return result;

		result.push_back(get_game()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[tile1_y][tile1_x]);

		if(tile1_x==tile2_x && tile1_y==tile2_y) return result;

		map_tile = *(result.end()-1);

		if(tile2_x>tile1_x) {
			if(test_colision_droiteAB_segemntCD(point1,point2,map_tile->get_vertex_right_bottom(),map_tile->get_vertex_right_top())) {
				tile1_x+=1;
				continue;
			}
		}
		else if(tile2_x<tile1_x) {
			if(test_colision_droiteAB_segemntCD(point1,point2,map_tile->get_vertex_left_bottom(),map_tile->get_vertex_left_top())) {
				tile1_x-=1;
				continue;
			}
		}
		if(tile2_y>tile1_y) {
			if(test_colision_droiteAB_segemntCD(point1,point2,map_tile->get_vertex_left_top(),map_tile->get_vertex_right_top())) {
				tile1_y+=1;
				continue;
			}
		}
		else if(tile2_y<tile1_y) {
			if(test_colision_droiteAB_segemntCD(point1,point2,map_tile->get_vertex_left_bottom(),map_tile->get_vertex_right_bottom())) {
				tile1_y-=1;
				continue;
			}
		}

		return vector<MapTile *>();

	}
	return result;
}

bool TileLayer::test_2_tile_crossable(int tile1_x, int tile1_y, int tile2_x, int tile2_y) {
	if(tile1_y<0 || tile1_y>=(int)_map_tile_matrix.size() || tile1_x<0 || tile1_x>=(int)_map_tile_matrix[0].size()) return false;
	if(tile2_y<0 || tile2_y>=(int)_map_tile_matrix.size() || tile2_x<0 || tile2_x>=(int)_map_tile_matrix[0].size()) return false;
	if(abs(tile1_x-tile2_x)>1 || abs(tile1_y-tile2_y)>1) return false;

	if(_map_tile_matrix[tile1_y][tile1_x]->get_building() || _map_tile_matrix[tile2_y][tile2_x]->get_building() || _map_tile_matrix[tile2_y][tile1_x]->get_building() || _map_tile_matrix[tile1_y][tile2_x]->get_building()) return false;

	if(tile1_x>tile2_x) {
		if(!_map_tile_matrix[tile1_y][tile1_x]->get_crossLeft() || !_map_tile_matrix[tile1_y][tile2_x]->get_crossRight()) return false;
		if(!_map_tile_matrix[tile2_y][tile1_x]->get_crossLeft() || !_map_tile_matrix[tile2_y][tile2_x]->get_crossRight()) return false;
	}
	else if(tile1_x<tile2_x) {
		if(!_map_tile_matrix[tile1_y][tile1_x]->get_crossRight() || !_map_tile_matrix[tile1_y][tile2_x]->get_crossLeft()) return false;
		if(!_map_tile_matrix[tile2_y][tile1_x]->get_crossRight() || !_map_tile_matrix[tile2_y][tile2_x]->get_crossLeft()) return false;
	}

	if(tile1_y>tile2_y) {
		if(!_map_tile_matrix[tile1_y][tile1_x]->get_crossDown() || !_map_tile_matrix[tile2_y][tile1_x]->get_crossUp()) return false;
		if(!_map_tile_matrix[tile1_y][tile2_x]->get_crossDown() || !_map_tile_matrix[tile2_y][tile2_x]->get_crossUp()) return false;
	}
	else if(tile1_y<tile2_y) {
		if(!_map_tile_matrix[tile1_y][tile1_x]->get_crossUp() || !_map_tile_matrix[tile2_y][tile1_x]->get_crossDown()) return false;
		if(!_map_tile_matrix[tile1_y][tile2_x]->get_crossUp() || !_map_tile_matrix[tile2_y][tile2_x]->get_crossDown()) return false;
	}

	return true;
}

vector<MapTile *> TileLayer::path_finding(int tile1_x, int tile1_y, int tile2_x, int tile2_y) {
	if(tile1_y<0 || tile1_y>=(int)_map_tile_matrix.size() || tile1_x<0 || tile1_x>=(int)_map_tile_matrix[0].size()) return vector<MapTile *>();
	if(tile2_y<0 || tile2_y>=(int)_map_tile_matrix.size() || tile2_x<0 || tile2_x>=(int)_map_tile_matrix[0].size()) return vector<MapTile *>();

	MapTile * destination = _map_tile_matrix[tile2_y][tile2_x];
	vector<PathFindingItem *> open_list, closed_list;
	PathFindingItem *min_f_scored_item, *parent;
	unsigned int k;
	int i,j;
	int tile_x, tile_y;
	bool already_exist;
	vector<MapTile *> result;

	open_list.push_back(new PathFindingItem(_map_tile_matrix[tile1_y][tile1_x], NULL, destination));

	while(true) {
		min_f_scored_item = open_list[0];
		for(k=1; k<open_list.size(); k++) {
			if(open_list[k]->get_f_score()<=min_f_scored_item->get_f_score()) {
				min_f_scored_item = open_list[k];
			}
		}
		if(min_f_scored_item->get_map_tile()==destination) break;

		open_list.erase(std::remove(open_list.begin(), open_list.end(), min_f_scored_item), open_list.end());
		closed_list.push_back(min_f_scored_item);

		tile_x = min_f_scored_item->get_map_tile()->get_tile_x();
		tile_y = min_f_scored_item->get_map_tile()->get_tile_y();
		for(i=tile_x-1;i<tile_x+2;i++) {
			for(j=tile_y-1;j<tile_y+2;j++) {
				if( i==tile_x-1 || i==tile_x+1 || j==tile_y-1 || j==tile_y+1 ) {
					if(test_2_tile_crossable(tile_x,tile_y,i,j)) {
						already_exist=false;
						for(k=0;k<open_list.size();k++) {
							if(open_list[k]->get_map_tile()->get_tile_x()==i && open_list[k]->get_map_tile()->get_tile_y()==j) {
								if(open_list[k]->get_f_score()>open_list[k]->compute_f_score_whith_parent(min_f_scored_item)) {
									open_list[k]->set_parent(min_f_scored_item);
								}
								already_exist=true;
								break;
							}
						}
						if(already_exist) continue;
						for(k=0;k<closed_list.size();k++) {
							if(closed_list[k]->get_map_tile()->get_tile_x()==i && closed_list[k]->get_map_tile()->get_tile_y()==j) {
								already_exist=true;
								break;
							}
						}
						if(!already_exist) open_list.push_back(new PathFindingItem(_map_tile_matrix[j][i],min_f_scored_item,destination));
					}
				}
			}
		}

		if(open_list.size()==0) {
			for(k=0;k<closed_list.size();k++) delete closed_list[k];
			return vector<MapTile *>();
		}
	}

	result.push_back(min_f_scored_item->get_map_tile());
	parent = min_f_scored_item->get_parent();
	while(parent) {
		result.insert(result.begin(), parent->get_map_tile());
		parent = parent->get_parent();
	}

	for(k=0;k<open_list.size();k++) delete open_list[k];
	for(k=0;k<closed_list.size();k++) delete closed_list[k];

	return result;
}

TileLayer::PathFindingItem::PathFindingItem(MapTile * map_tile, PathFindingItem * parent, MapTile * destination): _map_tile(map_tile), _parent(parent), _destination(destination) {
	if(_parent) {
		if(_parent->get_map_tile()->get_tile_x()!=_map_tile->get_tile_x() && _parent->get_map_tile()->get_tile_y()!=_map_tile->get_tile_y()) _g_score = _parent->get_g_score() + 14;
		else _g_score = _parent->get_g_score() + 10;
		_parent->_childs.push_back(this);
	}
	else _g_score = 0;
	_h_score = (abs(_map_tile->get_tile_x()-_destination->get_tile_x()) + abs(_map_tile->get_tile_y()-_destination->get_tile_y()))*10;
	_f_score = _g_score + _h_score;

}

void TileLayer::PathFindingItem::set_parent(PathFindingItem * parent) {
	_parent = parent;
	update_f_score();
}

void TileLayer::PathFindingItem::update_f_score() {
	if(_parent) {
		if(_parent->get_map_tile()->get_tile_x()!=_map_tile->get_tile_x() && _parent->get_map_tile()->get_tile_y()!=_map_tile->get_tile_y()) _g_score = _parent->get_g_score() + 14;
		else _g_score = _parent->get_g_score() + 10;
	}
	else _g_score = 0;
	_f_score = _g_score + _h_score;
	
	unsigned int i;
	for(i=0; i<_childs.size(); i++) _childs[i]->update_f_score();
}

int TileLayer::PathFindingItem::compute_f_score_whith_parent(PathFindingItem * parent) {
	if(parent->get_map_tile()->get_tile_x()!=_map_tile->get_tile_x() && parent->get_map_tile()->get_tile_y()!=_map_tile->get_tile_y()) return parent->get_g_score() + 14 + _h_score;
	else return parent->get_g_score() + 10 + _h_score;
}

