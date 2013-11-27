#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "cocos2d.h"
#include "cocos-ext.h"

#include "PhysicsDisplayable.h"

class Moveable : public PhysicsDisplayable
{
	public:
		typedef enum {
			UnitType,
		} MoveableType;

	private:
		CCPoint _destination;
		float   _move_speed;

		MoveableType _type;

		bool _rest;
		float _groundFixture;
		float _density;

		float _time_before_restore_position;
		bool _mode_restore_position;

		void goToDestination();
		void applyFixture(float dt);

		bool _tenir_position;
		bool _move_in_progress;
		
	public:
		Moveable();
		Moveable(MoveableType type, float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float hitboxRadius, float groundFixture, float density, const char * filename, Scene * scene, Layer * layer);
		virtual ~Moveable();

		// --- METHODES ---
		void bodyInit(int x,int y, int rotation, float hitboxRadius);
		void move(float dt);
		
		// --- GET ---
		CCPoint get_destination();
		float   get_move_speed();
		MoveableType getType() { return _type; }
		bool get_rest() { return _rest; }
		bool get_mode_restore_position() { return _mode_restore_position; }
		bool get_tenir_position() { return _tenir_position; }
		
		// --- SET ---
		void set_destination(float x_dest, float y_dest);
		void set_move_speed(float move_speed);
		void set_tenir_position(bool tenir_position);

		virtual void on_contact(Moveable * moveable);
		
};

#endif
