#ifndef EVENT_RECEIVER
#define EVENT_RECEIVER

class EventHandler;
class Unit;
class Moveable;
class PhysicsDisplayable;

class EventReceiver {
	public:
		EventReceiver();
		EventReceiver(EventHandler * eventHandler);
		virtual ~EventReceiver();

		virtual void on_unit_destroyed(Unit * unit) {}
		virtual void on_moveable_destination_reched(Moveable * moveable) {}
		virtual void on_physics_displayable_contact(PhysicsDisplayable * physicsDisplayableA, PhysicsDisplayable * physicsDisplayableB) {}

	private:
		EventHandler * _eventHandler;
};

#endif
