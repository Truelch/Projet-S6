
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
