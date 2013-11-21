#include "UnitLayer.h"

UnitLayer::UnitLayer(): Layer(){
}

UnitLayer::UnitLayer(Scene * scene): Layer(scene){
}

Unit * UnitLayer::getUnit(int index) {
	if(index<(int)_unit_list.size()) return _unit_list[index];
	else return NULL;
}

void UnitLayer::addUnit(Unit * unit) {
	addChild(unit->getSprite());
	_unit_list.push_back(unit);
}

void UnitLayer::removeUnit(int index) {
	if(index<(int)_unit_list.size()) {
		std::vector<Unit *>::iterator it = _unit_list.begin()+index;
		delete (*it);
		_unit_list.erase(it);
	}
}

int UnitLayer::getNumberUnit() {
	return (int)(_unit_list.size());
}

