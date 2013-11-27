#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include <vector>

class EventReceiver;
class Unit;
class Moveable;

class EventHandler {
	public:
		EventHandler() {}

		void addReceiver(EventReceiver * eventReceiver);
		void removeReceiver(EventReceiver * eventReceiver);

		void on_unit_destroyed(Unit * unit);
		void on_moveable_destination_reched(Moveable * moveable);

	private:
		std::vector<EventReceiver *> _receiver_list;
};

#endif
