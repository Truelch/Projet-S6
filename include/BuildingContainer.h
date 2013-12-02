#ifndef BUILDING_CONTAINER_H
#define BUILDING_CONTAINER_H

#include "Building.h"

#include <vector>

class BuildingContainer {
	private:
		std::vector<Building *> _building_list;

		static std::vector<BuildingContainer *> _instance_list; //WTF

	public:
		BuildingContainer();
		~BuildingContainer();

		Building * get_building(int index);
		void add_building(Building * building);
		void remove_building(int index);
		void remove_building(Building * building);
		bool contain_building(Building * building);
		int get_number_building();

		static void on_building_destroyed(Building * building); //reservé au destructeur de Building
};

#endif
