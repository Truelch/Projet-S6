#include "UnitLayer.h"

#include "Unit.h"

UnitLayer::UnitLayer(): Layer(){
}

UnitLayer::UnitLayer(Game * game): Layer(game){
}

void UnitLayer::add_unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float hitboxRadius, float groundFixture, float density, const char * filename, std::string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time, Player * owner, float sight) {
	Unit * unit = new Unit(x,y,x_dest,y_dest,rotation,move_speed,hitboxRadius,groundFixture,density,filename,get_game(),this,name,hp,hp_max,hp_regen,power,power_max,power_regen,armor,prod_time,owner,sight);
	_unit_list.add_t(unit);
}

void UnitLayer::remove_unit(Unit * unit) {
	_unit_list.remove_t(unit);
}

