#include "BuildingLayer.h"

#include "Building.h"

#include <algorithm>

BuildingLayer::BuildingLayer(): Layer()
{
	std::cout << "Constructeur de BuildingLayer" << std::endl;
}


BuildingLayer::BuildingLayer(Game * game): Layer(game)
{
	std::cout << "Constructeur de BuildingLayer" << std::endl;
}

void BuildingLayer::add_building(int x, int y, const char * filename, Game * game, Layer * layer, float x_rally_point, float y_rally_point, Player * player, float sight) {
	_building_list.push_back(new Building(x,y,filename,game,layer,x_rally_point,y_rally_point,player,sight));
}

void BuildingLayer::add_building(MapTile * mapTile, const char * filename, Game * game, Layer  * layer, float x_rally_point, float y_rally_point, Player * player, float sight) {
	_building_list.push_back(new Building(mapTile,filename,game,layer,x_rally_point,y_rally_point,player,sight));
}


void BuildingLayer::remove_building(Building * building) {
	_building_list.erase(std::remove(_building_list.begin(), _building_list.end(), building), _building_list.end());
}

// --- GET ---

// --- SET ---


// --- METHODES ---

