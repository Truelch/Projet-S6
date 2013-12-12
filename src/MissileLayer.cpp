#include "MissileLayer.h"

//#include "Unit.h"

#include "MapTile.h"
#include "Missile.h"

MissileLayer::MissileLayer(): Layer()
{
	std::cout << "Constructeur de MissileLayer" << std::endl;
}


MissileLayer::MissileLayer(Game * game): Layer(game)
{
	std::cout << "Constructeur de MissileLayer" << std::endl;
}


// --- GET ---

// --- SET ---


// --- METHODES ---

void MissileLayer::add_missile(float x, float y, float rotation, float x_dest, float y_dest, float move_speed, const char * filename, Game * game, Layer * layer, float range_max, float damage,
				Player * player, Unit * shooter_unit) 
{
	Missile * missile = new Missile(x, y, rotation, x_dest, y_dest, move_speed, filename, game, layer, range_max, damage, player, shooter_unit);
	_missile_list.add_t(missile);
}

/*void MissileLayer::update(float dt)
{
	int i;
	for(i=0;i<get_number_missile();i++)
	{
		get_missile(i)->update(dt);
	}
}*/
