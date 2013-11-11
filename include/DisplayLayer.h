#ifndef DISPLAYLAYER_H
#define DISPLAYLAYER_H

#include "cocos2d.h"

#include <string>

#include "Layer.h"

using namespace std;

class DisplayLayer : public Layer
{
	public:
		DisplayLayer();
		DisplayLayer(Scene * scene);
		// --- METHODES ---
		void init2();
	
		// --- GET ---
		
		Layer * get_tile_layer();
		Layer * get_doodad_layer();
		Layer * get_unit_layer();
		Layer * get_missile_layer();
		//CCLayer * get_interaction_layer();
		

		// --- SET ---
		/*
		void set_tile_layer();
		void set_doodad_layer();
		void set_unite_layer();
		void set_missile_layer();
		*/
		//void set_interaction_layer();

	private:
		Layer * _tile_layer;        //z = 0
		Layer * _doodad_layer;      //z = 1
		Layer * _unit_layer;        //z = 2
		Layer * _missile_layer;     //z = 3
		//CCLayer * _interaction_layer; //z = 7	
		
};

#endif
