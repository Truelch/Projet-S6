#ifndef BUILDINGLAYER_H
#define BUILDINGLAYER_H

#include "cocos2d.h"

#include <string>
#include <vector>

#include "Layer.h"
#include "Building.h"

using namespace std;

class BuildingLayer : public Layer
{
	public:
		BuildingLayer();
		BuildingLayer(Game * game);
		// --- METHODES ---
		
		// --- GET ---
		std::vector<Building *>& get_building_list() { return _building_list; }

	private:
		std::vector<Building *> _building_list;
};

#endif

