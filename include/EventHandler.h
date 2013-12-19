#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include <vector>

class EventReceiver;
class Unit;
class Moveable;
class Displayable;
class Player;
class Building;
class HudItem;
class Missile;

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

		void on_building_change_player(Building * building, Player * old_player, Player * new_player);

		void on_hud_item_clicked(HudItem * hud_item);

		void on_unit_shoot(Missile * missile);
		void on_unit_shooted(Unit * unit);

		void on_player_select_unit(Player * player, std::vector<Unit *> unit);

		void on_screen_change();

	private:
		std::vector<EventReceiver *> _receiver_list;
};

#endif
