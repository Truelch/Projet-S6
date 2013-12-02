
#include "Unit.h"

#include "Container.h"
#include "Stat.h"
#include "Player.h"
#include "Layer.h"
#include "Game.h"


Unit::Unit(): Moveable(), _player(NULL) 
{
	//
}

Unit::Unit(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float groundFixture, float density, const char * filename, Game * game, Layer * layer, string name, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time, Player * player, float sight): Moveable(x, y, x_dest, y_dest, rotation, move_speed, 0.7f, groundFixture, density, filename, game, layer), _player(player)
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
	_stat->set_sight(sight);
}

Unit::~Unit() {
	Container<Unit>::on_destroyed(this);
	getLayer()->removeChild(getPhysicsSprite());
	getGame()->getEventHandler()->on_unit_destroyed(this);
}

void Unit::updateCoordonates() {
	int old_tile_x=get_tile_x(), old_tile_y=get_tile_y();

	Moveable::updateCoordonates();

	if(old_tile_x!=get_tile_x() || old_tile_y!=get_tile_y()) {
		if(old_tile_x!=-1 && old_tile_y!=-1) {
			getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[old_tile_y][old_tile_x]->get_unit_container().remove_t(this);
		}
		getGame()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[get_tile_x()][get_tile_y()]->get_unit_container().add_t(this);
		getGame()->getEventHandler()->unit_change_map_tile(get_tile_x(), get_tile_y(), this);
	}

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
void Unit::on_displayable_contact(Displayable * displayableA, Displayable * displayableB) {
	Unit * unit = NULL;
	if(displayableA==this) {
		if(displayableB->getType()==Displayable::unitType) {
			unit = (Unit *)displayableB;
		}
	}
	else if(displayableB==this) {
		if(displayableA->getType()==Displayable::unitType) {
			unit = (Unit *)displayableA;
		}
	}
	if(unit) {
		if(unit->getPlayer()==_player) set_hold_position(false);
		else set_hold_position(true);
	}
	Moveable::on_displayable_contact(displayableA, displayableB);
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
