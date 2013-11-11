#include "DisplayLayer.h"


DisplayLayer::DisplayLayer(): Layer()
{
	init2();
}


DisplayLayer::DisplayLayer(Scene * scene): Layer(scene)
{
	init2();
}


// --- GET ---

Layer * DisplayLayer::get_tile_layer()
{
	return _tile_layer;
}

Layer * DisplayLayer::get_doodad_layer()
{
	return _doodad_layer;
}

Layer * DisplayLayer::get_unit_layer()
{
	return _unit_layer;
}

Layer * DisplayLayer::get_missile_layer()
{
	return _missile_layer;
}


// --- SET ---


// --- METHODES ---

void DisplayLayer::init2()
{
	// --- Layer des Tiles ---
	_tile_layer = new Layer(get_scene());
	_tile_layer->setZOrder(0);
	addChild(_tile_layer);
	
	// --- Layer des Doodads ---
	_doodad_layer = new Layer(get_scene());
	_doodad_layer->setZOrder(1);
	addChild(_doodad_layer);
	
	// --- Layer des Units ---
	_unit_layer = new Layer(get_scene());
	_unit_layer->setZOrder(2);
	addChild(_unit_layer);
	
	// --- Layer des Missiles ---
	_missile_layer = new Layer(get_scene());
	_missile_layer->setZOrder(3);
	addChild(_missile_layer);
}



