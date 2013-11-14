#include "TileLayer.h"

#include <fstream>

using namespace std;


TileLayer::TileLayer(): Layer()
{
	init2();
}


TileLayer::TileLayer(Scene * scene): Layer(scene)
{
	init2();
}


// --- GET ---

// --- SET ---


// --- METHODES ---

void TileLayer::init2()
{
	ifstream mapFile;
	mapFile.open("map/map1");
	sting line;
	if(mapFile.is_open())
}

