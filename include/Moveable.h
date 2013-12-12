#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D/Box2D.h"

#include "PhysicsDisplayable.h"

#include <vector>

class Moveable : public PhysicsDisplayable
{
	private:
		b2Body * _body;

		int _tile_x;
		int _tile_y;
		//CCPoint _destination;
		
		typedef struct {
			CCPoint destination;
			std::vector<MapTile *> map_tile_list;
		} ListDestinationItem;
		std::vector<ListDestinationItem> _list_destination;
		b2Vec2 _vect_ligne_destination;
		void init_point_ligne_destination();

		float   _move_speed;

		bool _rest;
		float _groundFixture;
		float _density;
		float _hitboxRadius;

		float _time_before_restore_position;
		bool _mode_restore_position;

		void goToDestination();
		void applyFixture(float dt);

		bool _hold_position;
		bool _move_in_progress;

		bool test_current_destination_reched();

	protected:
		virtual void updateCoordonates();
		
	public:
		Moveable();
		Moveable(float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float hitboxRadius, float groundFixture, float density, const char * filename, Game * game, Layer * layer);
		virtual ~Moveable();

		// --- METHODES ---
		void bodyInit(int x,int y, int rotation, float hitboxRadius);
		virtual void update(float dt);
		
		// --- GET ---
		CCPoint get_destination();
		float   get_move_speed();
		bool get_rest() { return _rest; }
		bool get_mode_restore_position() { return _mode_restore_position; }
		float get_hitboxRadius();

		bool get_hold_position() { return _hold_position; }
		int get_tile_x() { return _tile_x; }
		int get_tile_y() { return _tile_y; }
		virtual Displayable::DisplayableType getType() { return Displayable::moveableType; }
		
		// --- SET ---
		bool set_destination(float x_dest, float y_dest);
		void set_move_speed(float move_speed);
		void set_hold_position(bool hold_position);

		virtual void on_displayable_contact(Displayable * displayableA, Displayable * displayableB);
		virtual void on_player_range_tile(int x, int y, Player * player);
		virtual void on_player_unrange_tile(int x, int y, Player * player);

		bool test_point_in_moveable(CCPoint point);
		
};

#endif
