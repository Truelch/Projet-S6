#ifndef EVENT_RECEIVER
#define EVENT_RECEIVER

class EventHandler;
class Unit;
class Moveable;
class Displayable;
class MapTile;
class Player;
class Building;
class HudItem;

class EventReceiver {
	public:
		EventReceiver();
		EventReceiver(EventHandler * eventHandler);
		virtual ~EventReceiver();

		virtual void on_unit_destroyed(Unit * unit) {}
		virtual void on_moveable_destination_reched(Moveable * moveable) {}
		virtual void on_displayable_contact(Displayable * displayableA, Displayable * displayableB) {}
		virtual void on_moveable_change_map_tile(int x, int y, Moveable * moveable) {}

		virtual void on_unit_range_tile(int x, int y, Unit * unit) {}
		virtual void on_unit_unrange_tile(int x, int y, Unit * unit) {}

		virtual void on_player_discovered_tile(int x, int y, Player * player) {}
		virtual void on_player_range_tile(int x, int y, Player * player) {}
		virtual void on_player_unrange_tile(int x, int y, Player * player) {}

		virtual void on_building_change_player(Building * building, Player * old_player, Player * new_player) {}

		virtual void on_hud_item_clicked(HudItem * hud_item) {}

	private:
		EventHandler * _eventHandler;
};

#endif
