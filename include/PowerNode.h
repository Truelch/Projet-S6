#ifndef POWERNODE_H
#define POWERNODE_H

#include "cocos2d.h"
#include "Displayable.h"

#include <vector>

using namespace cocos2d;

class PowerNode : public Displayable
{
	public:
		PowerNode();
		
		// --- METHODES ---
		
		
		// --- GET ---
		virtual Displayable::DisplayableType getType() { return Displayable::powerNodeType; }
		
		
		// --- SET ---
		

	private:
		// --- Attributs ---
		//Un container à power node pour indiquer avec quels power node il est relié
		std::vector <PowerNode *> _power_node_list; //Hm finalement il faudrait que ce container puisse aussi contenir également des bâtiments !
};

#endif
