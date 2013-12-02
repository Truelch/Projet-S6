
#include "EventHandler.h"

#include "EventReceiver.h"
#include <algorithm>

void EventHandler::addReceiver(EventReceiver * eventReceiver) {
	if(std::find(_receiver_list.begin(), _receiver_list.end(), eventReceiver) == _receiver_list.end()) {
		_receiver_list.push_back(eventReceiver);
	}
}

void EventHandler::removeReceiver(EventReceiver * eventReceiver) {
	_receiver_list.erase(std::remove(_receiver_list.begin(), _receiver_list.end(), eventReceiver), _receiver_list.end());
}

void EventHandler::on_unit_destroyed(Unit * unit) {
	unsigned int i;
	for(i=0; i<_receiver_list.size(); i++) {
		_receiver_list[i]->on_unit_destroyed(unit);
	}
}

void EventHandler::on_moveable_destination_reched(Moveable * moveable) {
	unsigned int i;
	for(i=0; i<_receiver_list.size(); i++) {
		_receiver_list[i]->on_moveable_destination_reched(moveable);
	}
}

void EventHandler::on_physics_displayable_contact(PhysicsDisplayable * physicsDisplayableA, PhysicsDisplayable * physicsDisplayableB) {
	unsigned int i;
	for(i=0; i<_receiver_list.size(); i++) {
		_receiver_list[i]->on_physics_displayable_contact(physicsDisplayableA, physicsDisplayableB);
	}
}

void EventHandler::unit_change_map_tile(MapTile * map_tile, Unit * unit) {
	unsigned int i;
	for(i=0; i<_receiver_list.size(); i++) {
		_receiver_list[i]->unit_change_map_tile(map_tile, unit);
	}
}
