#ifndef MISSILELAYER_H
#define MISSILELAYER_H

#include "cocos2d.h"

#include <string>
#include <vector>

#include "Layer.h"
//#include "MapTile.h"
#include "Container.h"
//#include "Missile.h"

class MapTile;
class Missile;

using namespace std;

class MissileLayer : public Layer
{
	public:
		MissileLayer();
		MissileLayer(Game * game);


		void add_missile(float x, float y, float rotation, float x_dest, float y_dest, float move_speed, const char * filename, Game * game, Layer * layer, float range_max, float damage,
				Player * player, Unit * shooter_unit);
		int get_number_missile() { return _missile_list.get_number_t(); }
		Missile * get_missile(int index) { return _missile_list.get_t(index); }
		void   remove_missile(Missile * missile) { _missile_list.remove_t(missile); }
		// --- GET ---
		
		// --- METHODES ---
		//void update(float dt);
		
		
	private:
		Container<Missile> _missile_list;
};

#endif

