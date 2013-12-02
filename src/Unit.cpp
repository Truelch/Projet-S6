
#include "Unit.h"

#include "UnitContainer.h"
#include "Stat.h"
#include "Player.h"
#include "Layer.h"


Unit::Unit(): Moveable(), _player(NULL) 
{
	//
}

Unit::Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float groundFixture, float density, const char * filename, Scene * scene, Layer * layer, string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time, Player * player): Moveable(Moveable::unitType, x, y, x_dest, y_dest, rotation, move_speed, 0.7f, groundFixture, density, filename, scene, layer), _player(player)
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
	getLayer()->removeChild(getPhysicsSprite());
	getScene()->getEventHandler()->on_unit_destroyed(this);
}

// --- GET ---

Stat * Unit::get_stat()
{
	return _stat;
}

AIStat * Unit::get_ai_stat()
{
	return _ai_stat;
}

// --- METHODES ---

void Unit::on_physics_displayable_contact(PhysicsDisplayable * physicsDisplayableA, PhysicsDisplayable * physicsDisplayableB) {
	Unit * unit = NULL;
	if(physicsDisplayableA==this) {
		if(physicsDisplayableB->getType()==PhysicsDisplayable::moveableType && ((Moveable *)(physicsDisplayableB))->getType()==Moveable::unitType) {
			unit = (Unit *)physicsDisplayableB;
		}
	}
	else if(physicsDisplayableB==this) {
		if(physicsDisplayableA->getType()==PhysicsDisplayable::moveableType && ((Moveable *)(physicsDisplayableA))->getType()==Moveable::unitType) {
			unit = (Unit *)physicsDisplayableA;
		}
	}
	if(unit) {
		if(unit->getPlayer()==_player) set_hold_position(false);
		else set_hold_position(true);
	}
	Moveable::on_physics_displayable_contact(physicsDisplayableA, physicsDisplayableB);
}


void Unit::check_attack()
{
	/*
	int i = 0;
	float distance = get_stat()->; //hors de portée => valeur infinie
	float delta_x, delta_y;
	//Pour accéder aux container d'unités !	
	for(i = 0 ; i < _player->get_scene()->get_display_layer()->get_unit_layer()->get_number_unit() ; i++) //Ici
	{
		i.check_attack();
	}
	*/
}
