#ifndef BUILDINGLAYER_H
#define BUILDINGLAYER_H

#include "cocos2d.h"

#include <string>
#include <vector>

#include "Layer.h"
//#include "Building.h"
class Building;

using namespace std;

class BuildingLayer : public Layer
{
	public:
		BuildingLayer();
		BuildingLayer(Game * game);

		Building * get_building(int index) { return _building_list[index]; }
		void   remove_building(Building * building);
		void   add_building(int x, int y, const char * filename, Game * game, Layer * layer, float x_rally_point, float y_rally_point,std::string name, Player * player, float sight);
		void   add_building(MapTile * mapTile, const char * filename, Game * game, Layer  * layer, float x_rally_point, float y_rally_point,std::string name, Player * player, float sight);
		int    get_number_building() { return (int)_building_list.size(); }

	private:
		std::vector<Building *> _building_list;
};

#endif

