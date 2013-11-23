#include "UnitLayer.h"

UnitLayer::UnitLayer(): Layer(){
}

UnitLayer::UnitLayer(Scene * scene): Layer(scene){
}

Unit * UnitLayer::get_unit(int index) {
	if(index<(int)_unit_list.size()) return _unit_list[index];
	else return NULL;
}

void UnitLayer::add_unit(Unit * unit) {
	addChild(unit->getSprite());
	_unit_list.push_back(unit);
}

void UnitLayer::remove_unit(int index) {
	if(index<(int)_unit_list.size()) {
		std::vector<Unit *>::iterator it = _unit_list.begin()+index;
		delete (*it);
		_unit_list.erase(it);
	}
}

int UnitLayer::get_number_unit() {
	return (int)(_unit_list.size());
}

