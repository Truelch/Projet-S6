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
			
		Unit * get_unit(int index);
		void   add_unit(Unit * unit);
		void   remove_unit(int index);
		int    get_number_unit();
		
	private:
		std::vector<Unit *> _unit_list;
};

#endif
