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
Layer * DisplayLayer::get_background_layer()
{
	return _background_layer;
}

Layer * DisplayLayer::get_opacity_layer()
{
	return _opacity_layer;
}

TileLayer * DisplayLayer::get_tile_layer()
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
	// --- Layer de Background ---
	_background_layer = new Layer(get_scene());
	_background_layer->setZOrder(0);
	addChild(_background_layer);
	
	// --- Layer d'Opacité ---
	_opacity_layer = new Layer(get_scene());
	_opacity_layer->setZOrder(1);
	addChild(_opacity_layer);	
	
	// --- Layer des Tiles ---
	_tile_layer = new TileLayer(get_scene());
	_tile_layer->setZOrder(2);
	addChild(_tile_layer);
	
	// --- Layer des Doodads ---
	_doodad_layer = new Layer(get_scene());
	_doodad_layer->setZOrder(3);
	addChild(_doodad_layer);
	
	// --- Layer des Unités ---
	_unit_layer = new Layer(get_scene());
	_unit_layer->setZOrder(4);
	addChild(_unit_layer);
	
	// --- Layer des Missiles ---
	_missile_layer = new Layer(get_scene());
	_missile_layer->setZOrder(5);
	addChild(_missile_layer);
}




