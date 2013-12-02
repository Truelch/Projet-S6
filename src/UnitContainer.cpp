#include "UnitContainer.h"

#include <algorithm>

std::vector<UnitContainer *> UnitContainer::_instance_list;

UnitContainer::UnitContainer() {
	_instance_list.push_back(this);
}

UnitContainer::~UnitContainer() {
	_instance_list.erase(std::remove(_instance_list.begin(), _instance_list.end(), this), _instance_list.end());
}

Unit * UnitContainer::get_unit(int index) {
	if(index>=0 && index<(int)_unit_list.size()) return _unit_list[index];
	else return NULL;
}

void UnitContainer::add_unit(Unit * unit) {
	if(std::find(_unit_list.begin(), _unit_list.end(), unit) == _unit_list.end()) {
		_unit_list.push_back(unit);
	}
}

void UnitContainer::remove_unit(int index) {
	if(index>0 && index<(int)_unit_list.size()) {
		std::vector<Unit *>::iterator it = _unit_list.begin()+index;
		_unit_list.erase(it);
	}
}

void UnitContainer::remove_unit(Unit * unit) {
	_unit_list.erase(std::remove(_unit_list.begin(), _unit_list.end(), unit), _unit_list.end());
}

bool UnitContainer::contain_unit(Unit * unit) {
	return std::find(_unit_list.begin(), _unit_list.end(), unit) != _unit_list.end();
}

int UnitContainer::get_number_unit() {
	return (int)(_unit_list.size());
}

void UnitContainer::on_unit_destroyed(Unit * unit) {
	unsigned int i;
	for(i=0; i<_instance_list.size(); i++) {
		_instance_list[i]->remove_unit(unit);
	}
}
