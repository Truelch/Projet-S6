#ifndef DISPLAYLAYER_H
#define DISPLAYLAYER_H

#include "cocos2d.h"

#include <string>

#include "Layer.h"
#include "TileLayer.h"

using namespace std;

class DisplayLayer : public Layer
{
	public:
		DisplayLayer();
		DisplayLayer(Scene * scene);
		// --- METHODES ---
		void init2();
	
		// --- GET ---
		
		Layer * get_background_layer();
		Layer * get_opacity_layer();
		TileLayer * get_tile_layer();
		Layer * get_doodad_layer();
		Layer * get_unit_layer();
		Layer * get_missile_layer();
		

		// --- SET ---
		/*
		void set_tile_layer();
		void set_doodad_layer();
		void set_unite_layer();
		void set_missile_layer();
		*/
		//void set_interaction_layer();

	private:
		Layer * _background_layer;   //z = 0
		Layer * _opacity_layer;     //z = 1
		TileLayer * _tile_layer;        //z = 2
		Layer * _doodad_layer;      //z = 3
		Layer * _unit_layer;        //z = 4
		Layer * _missile_layer;     //z = 5	
};

#endif
