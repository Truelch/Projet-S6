#ifndef EVENT_RECEIVER
#define EVENT_RECEIVER

class EventHandler;
class Unit;

class EventReceiver {
	public:
		EventReceiver();
		EventReceiver(EventHandler * eventHandler);
		virtual ~EventReceiver();

		virtual void on_unit_destroyed(Unit * unit) {}

	private:
		EventHandler * _eventHandler;
};

#endif
