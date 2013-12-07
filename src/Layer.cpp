#include "Layer.h"

#include "Game.h"
#include "TileLayer.h"

#include <iostream>

#include "Displayable.h"

using namespace std;


Layer::Layer(): CCLayer(), _game(NULL)
{
	std::cout << "Constructeur de Layer" << std::endl;
	init();
}

Layer::Layer(Game * game): CCLayer(), _game(game)
{
	std::cout << "Constructeur de Layer" << std::endl;
	init();
}

Layer::~Layer() {
	unsigned int i;
	for(i=0; i<_displayable_list.size(); i++) {
		delete _displayable_list[i];
	}
}


