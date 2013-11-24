#ifndef UNIT_LAYER
#define UNIT_LAYER

#include <vector>
#include <iostream>
#include "Layer.h"
#include "Unit.h"
#include "UnitContainer.h"

class UnitLayer : public Layer {
	public:
		UnitLayer();
		UnitLayer(Scene * scene);
			
		Unit * get_unit(int index) { return _unit_list.get_unit(index); }
		void   remove_unit(Unit *);
		void   add_unit(Unit * unit);
		int    get_number_unit() { return _unit_list.get_number_unit(); }

		virtual void on_unit_destroyed(Unit * unit);
		
	private:
		UnitContainer _unit_list;
};

#endif
