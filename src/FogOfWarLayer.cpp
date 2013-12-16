
#include "FogOfWarLayer.h"

#include "FogOfWarDisplayable.h"

#include <algorithm>

FogOfWarLayer::FogOfWarLayer(Game * game): Layer(game) {
	
}


void FogOfWarLayer::add_fog_og_war_to_update(FogOfWarDisplayable * fogOfWarDisplayable) {
	if(std::find(_fog_og_war_to_update.begin(), _fog_og_war_to_update.end(), fogOfWarDisplayable) == _fog_og_war_to_update.end()) {
		_fog_og_war_to_update.push_back(fogOfWarDisplayable);
	}
}

void FogOfWarLayer::update() {
	std::vector<FogOfWarDisplayable *>::iterator it;
	for(it=_fog_og_war_to_update.begin(); it!=_fog_og_war_to_update.end(); it++) {
		(*it)->update();
	}
	_fog_og_war_to_update.clear();
}
