
#include "Unit.h"

#include "UnitContainer.h"
#include "Stat.h"
#include "Player.h"


Unit::Unit(): Moveable(), _player(NULL) {
	//
}

Unit::Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float groundFixture, float density, const char * filename, Scene * scene, string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time, Player * player): Moveable(Moveable::UnitType, x, y, x_dest, y_dest, rotation, move_speed, 0.7f, groundFixture, density, filename, scene), _player(player)
{
	_stat = new Stat();
	_stat->set_name(name);
	_stat->set_hp(hp);
	_stat->set_hp_max(hp_max);
	_stat->set_hp_regen(hp_regen);
	_stat->set_power(power);
	_stat->set_power_max(power_max);
	_stat->set_power_regen(power_regen);
	_stat->set_armor(armor);
	_stat->set_prod_time(prod_time);
}

Unit::~Unit() {
	UnitContainer::on_unit_destroyed(this);
}

// --- METHODES ---
void Unit::on_contact(Moveable * moveable) {
	Unit * unit;
	if(moveable->getType()==Moveable::UnitType) {
		unit = (Unit *)moveable;
		if(unit->getPlayer()==_player) set_tenir_position(false);
		else set_tenir_position(true);
	}
	Moveable::on_contact(moveable);
}

// --- GET ---

Stat * Unit::get_stat()
{
	return _stat;
}

