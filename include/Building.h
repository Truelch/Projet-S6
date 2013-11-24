#ifndef BUILDING_H
#define BUILDING_H

#include "cocos2d.h"
#include "PhysicsDisplayable.h"
#include "MapTile.h"

class Building : public PhysicsDisplayable
{
	public:
		Building();
		Building(int x, int y, const char * filename, Scene * scene, Layer * layer, float x_rally_point, float y_rally_point);
		Building(MapTile * mapTile, const char * filename, Scene * scene, Layer  * layer, float x_rally_point, float y_rally_point);
		
		// --- GET ---
		CCPoint get_rally_point() { return _rally_point; }
		
		// --- SET ---
		void set_rally_point(float x_rally_point, float y_rally_point) {
			_rally_point.x = x_rally_point;
			_rally_point.y = y_rally_point;
		};
		void set_rally_point(CCPoint rally_point) { _rally_point = rally_point; }

	private:
		CCPoint _rally_point;
};

#endif
