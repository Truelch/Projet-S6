#include "TileLayer.h"

#include <algorithm>


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
		_g_score = _parent->get_g_score() + _map_tile->getSprite()->getPosition().getDistance(_parent->get_map_tile()->getSprite()->getPosition());
		_parent->_childs.push_back(this);
	}
	else _g_score = 0;
	_h_score = _map_tile->getSprite()->getPosition().getDistance(_destination->getSprite()->getPosition());
	_f_score = _g_score + _h_score;
}

void TileLayer::PathFindingItem::set_parent(PathFindingItem * parent) {
	_parent = parent;
	update_f_score();
}

void TileLayer::PathFindingItem::update_f_score() {
	if(_parent) _g_score = _parent->get_g_score() + _map_tile->getSprite()->getPosition().getDistance(_parent->get_map_tile()->getSprite()->getPosition());
	else _g_score = 0;
	_f_score = _g_score + _h_score;
	
	unsigned int i;
	for(i=0; i<_childs.size(); i++) _childs[i]->update_f_score();
}

float TileLayer::PathFindingItem::compute_f_score_whith_parent(PathFindingItem * parent) {
	return parent->_g_score + _map_tile->getSprite()->getPosition().getDistance(parent->get_map_tile()->getSprite()->getPosition()) + _h_score;
}

