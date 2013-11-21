#include "Building.h"

Building::Building(): PhysicsDisplayable() {
	//
}

Building::Building(float x, float y, const char * filename, Scene * scene, float x_rally_point, float y_rally_point)
{
	PhysicsDisplayable(x,y,0,filename,scene,NULL);
}

// --- METHODES ---

// --- GET ---

CCPoint Building::get_rally_point()
{
	return _rally_point;
}

// --- SET ---

void Building::set_rally_point(float x_rally_point,float y_rally_point)
{
	_rally_point.x = x_rally_point;
	_rally_point.y = y_rally_point;
}
