#ifndef MISSILELAYER_H
#define MISSILELAYER_H

#include "cocos2d.h"

#include <string>
#include <vector>

#include "Layer.h"
#include "MapTile.h"
#include "Container.h"
#include "Missile.h"

using namespace std;

class MissileLayer : public Layer
{
	public:
		MissileLayer();
		MissileLayer(Game * game);
		// --- METHODES ---

		void add_missile(float x, float y, float rotation, float x_dest, float y_dest, float move_speed, const char * filename, Game * game, Layer * layer, float range_max, int damage,
				Player * player);
		// --- GET ---
		
	private:
		Container<Missile> _missile_list;
};

#endif

