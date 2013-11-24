
#include "EventReceiver.h"

#include "EventHandler.h"

#include <stdlib.h>

EventReceiver::EventReceiver(): _eventHandler(NULL) {
}

EventReceiver::EventReceiver(EventHandler * eventHandler): _eventHandler(eventHandler) {
	_eventHandler->addReceiver(this);
}

EventReceiver::~EventReceiver() {
	_eventHandler->removeReceiver(this);
}
