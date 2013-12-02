#include "TileLayer.h"


TileLayer::TileLayer(): Layer()
{
	std::cout << "Constructeur de TileLayer" << std::endl;
}


TileLayer::TileLayer(Game * game): Layer(game)
{
	std::cout << "Constructeur de TileLayer" << std::endl;
}


// --- GET ---
std::vector<std::vector<MapTile *> >& TileLayer::get_map_tile_matrix()
{
	return _map_tile_matrix;
}

// --- SET ---


// --- METHODES ---

