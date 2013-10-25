#include "Building.h"

Building::Building(): Displayable() {
	//
}

Building::Building(float x, float y, const char * filename, float x_rally_point, float y_rally_point): Displayable(x,y,0,filename)
{
	//
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
