#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include <vector>

class EventReceiver;
class Unit;
class Moveable;
class Displayable;
class Player;

class EventHandler {
	public:
		EventHandler() {}

		void addReceiver(EventReceiver * eventReceiver);
		void removeReceiver(EventReceiver * eventReceiver);

		void on_unit_destroyed(Unit * unit);
		void on_moveable_destination_reched(Moveable * moveable);
		void on_displayable_contact(Displayable * displayableA, Displayable * displayableB);

		void on_moveable_change_map_tile(int x, int y, Moveable * moveable);

		void on_unit_range_tile(int x, int y, Unit * unit);
		void on_unit_unrange_tile(int x, int y, Unit * unit);

		void on_player_discovered_tile(int x, int y, Player * player);
		void on_player_range_tile(int x, int y, Player * player);
		void on_player_unrange_tile(int x, int y, Player * player);

	private:
		std::vector<EventReceiver *> _receiver_list;
};

#endif
