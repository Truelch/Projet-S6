#include "UnitLayer.h"

UnitLayer::UnitLayer(): Layer(){
}

UnitLayer::UnitLayer(Scene * scene): Layer(scene){
}

void UnitLayer::add_unit(Unit * unit) {
	addChild(unit->getSprite());
	_unit_list.add_unit(unit);
}
