#ifndef UNIT_LAYER
#define UNIT_LAYER

#include <vector>
#include "Layer.h"
#include <iostream>
#include "Unit.h"

class UnitLayer : public Layer {
	public:
		UnitLayer();
		UnitLayer(Scene * scene);

		Unit * getUnit(int index);
		void addUnit(Unit * unit);
		void removeUnit(int index);
		int getNumberUnit();
	private:
		std::vector<Unit *> _unit_list;
};

#endif
