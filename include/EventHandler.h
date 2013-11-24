#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include <vector>

class EventReceiver;
class Unit;

class EventHandler {
	public:
		EventHandler() {}

		void addReceiver(EventReceiver * eventReceiver);
		void removeReceiver(EventReceiver * eventReceiver);

		void on_unit_destroyed(Unit * unit);

	private:
		std::vector<EventReceiver *> _receiver_list;
};

#endif
