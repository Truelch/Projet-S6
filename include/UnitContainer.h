#ifndef UNIT_CONTENER_H
#define UNIT_CONTENER_H

#include "Unit.h"

#include <vector>

class UnitContainer {
	private:
		std::vector<Unit *> _unit_list;

		static std::vector<UnitContainer *> _instance_list;

	public:
		UnitContainer();
		~UnitContainer();

		Unit * get_unit(int index);
		void add_unit(Unit * unit);
		void remove_unit(int index);
		void remove_unit(Unit * unit);
		bool contain_unit(Unit * unit);
		int get_number_unit();

		static void on_unit_destroyed(Unit * unit); //reservé au destructeur de Unit
};

#endif
