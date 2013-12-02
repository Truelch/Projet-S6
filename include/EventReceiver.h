#ifndef EVENT_RECEIVER
#define EVENT_RECEIVER

class EventHandler;
class Unit;
class Moveable;
class Displayable;
class MapTile;

class EventReceiver {
	public:
		EventReceiver();
		EventReceiver(EventHandler * eventHandler);
		virtual ~EventReceiver();

		virtual void on_unit_destroyed(Unit * unit) {}
		virtual void on_moveable_destination_reched(Moveable * moveable) {}
		virtual void on_displayable_contact(Displayable * displayableA, Displayable * displayableB) {}
		virtual void on_unit_change_map_tile(int x, int y, Unit * unit) {}
		virtual void on_unit_range_tile(int x, int y, Unit * unit) {}
		virtual void on_unit_unrange_tile(int x, int y, Unit * unit) {}

	private:
		EventHandler * _eventHandler;
};

#endif
