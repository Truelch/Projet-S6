
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

void EventHandler::on_displayable_contact(Displayable * displayableA, Displayable * displayableB) {
	unsigned int i;
	for(i=0; i<_receiver_list.size(); i++) {
		_receiver_list[i]->on_displayable_contact(displayableA, displayableB);
	}
}

void EventHandler::on_moveable_change_map_tile(int x, int y, Moveable * moveable) {
	unsigned int i;
	for(i=0; i<_receiver_list.size(); i++) {
		_receiver_list[i]->on_moveable_change_map_tile(x, y, moveable);
	}
}

void EventHandler::on_unit_range_tile(int x, int y, Unit * unit) {
	unsigned int i;
	for(i=0; i<_receiver_list.size(); i++) {
		_receiver_list[i]->on_unit_range_tile(x, y, unit);
	}
}

void EventHandler::on_unit_unrange_tile(int x, int y, Unit * unit) {
	unsigned int i;
	for(i=0; i<_receiver_list.size(); i++) {
		_receiver_list[i]->on_unit_unrange_tile(x, y, unit);
	}
}

void EventHandler::on_player_discovered_tile(int x, int y, Player * player) {
	unsigned int i;
	for(i=0; i<_receiver_list.size(); i++) {
		_receiver_list[i]->on_player_discovered_tile(x, y, player);
	}
}

void EventHandler::on_player_range_tile(int x, int y, Player * player) {
	unsigned int i;
	for(i=0; i<_receiver_list.size(); i++) {
		_receiver_list[i]->on_player_range_tile(x, y, player);
	}
}

void EventHandler::on_player_unrange_tile(int x, int y, Player * player) {
	unsigned int i;
	for(i=0; i<_receiver_list.size(); i++) {
		_receiver_list[i]->on_player_unrange_tile(x, y, player);
	}
}

