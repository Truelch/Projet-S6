#ifndef PLAYER_H
#define PLAYER_H

//#include "cocos2d.h"

//using namespace cocos2d;

#include <string>

#include "EventReceiver.h"
#include "Scene.h"
#include "UnitContainer.h"

using namespace std;

class Player: public EventReceiver
{
	public:
		typedef enum {
			red,
			blue,
			green,
			purple,
			cyan,
			yellow,
			orange,
			brown,
			pink,
		} Color;
		
	private:
		//ATTRIBUTS
		string  _name;
		Color   _color;
		int     _player_number;
		int     _team_number;
		Scene * _scene;
		// --
		UnitContainer              _unit_container;       //Contient toutes les unités du joueur
		std::vector<UnitContainer> _control_group_vector; //Contient 10 slots de groupes d'unités
		
	public:
		Player();
		Player(Scene * scene, string name, Color color, int player_number, int team_number);
		
		//Unit*  _unit_selection;
		//Il faudra que je retrouve comment bien initialiser le pointeur. Est ce que ça doit être un container ??
		
		//METHODES
		
		//GET
		string get_name();
		Color get_color();
		int    get_player_number();
		int    get_team_number();
		// --
		UnitContainer&              get_unit_container();
		std::vector<UnitContainer>&	get_control_group_vector();	
		
		//SET
		void set_name(string name);
		void set_color(Color color);
		void set_player_number(int player_number); //Eviter son utilisation
		void set_team_number(int team_number);     //Eviter son utilisation	
};

#endif
