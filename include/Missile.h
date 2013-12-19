#ifndef MISSILE_H
#define MISSILE_H

#include "cocos2d.h"
#include "Displayable.h"

#include <string>

class Player;

using namespace std;

class Missile : public Displayable
{
	public:
		Missile();
		Missile(float x, float y, float rotation, float x_dest, float y_dest, float move_speed, const char * filename, Game * game, Layer * layer, float range_max, float damage, 
				Player * player, Unit * shooter_unit);
		~Missile();
		
		// --- METHODES ---

	
		// --- GET ---
		CCPoint get_origin();
		CCPoint get_destination();
		
		float   get_move_speed();
		float   get_range_max();
		float     get_damage();
		//
		Player * get_player();
		Unit * get_shooter_unit();
		bool get_visible();

		// --- SET ---
		void set_origin(float x_origin, float y_origin);  //Il ne faudrait pas l'utiliser
		void set_destination(float x_dest, float y_dest); //Il ne faudrait pas l'utiliser
		
		void set_move_speed(float move_speed);
		void set_range_max(float range_max);
		void set_damage(float damage);
		//
		void set_player(Player * player);
		void set_shooter_unit(Unit * shooter_unit);
		void set_visible(bool visible);
		
		// --- METHODES ---
		bool update(float dt);
		bool check_collision();
		void deal_dmg(Unit * unit);
		//void check_range();	

		virtual void on_player_range_tile(int x, int y, Player * player);
		virtual void on_player_unrange_tile(int x, int y, Player * player);
		
	private:
		// --- ATTRIBUTS ---
		CCPoint      _origin;
		CCPoint      _destination;
		CCPoint      _movement;   //Vecteur unitaire de déplacement
		float        _move_speed;
		const char * _filename;
		float        _range_max;
		float        _damage;
		//
		Player *     _player;
		Unit *       _shooter_unit;		

		int _tile_x;
		int _tile_y;

};

#endif
