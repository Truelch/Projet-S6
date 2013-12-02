#ifndef PLAYER_H
#define PLAYER_H

//#include "cocos2d.h"

//using namespace cocos2d;

#include <string>

#include "EventReceiver.h"
#include "Scene.h"
#include "Container.h"

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

		typedef struct {
			bool discovered;
			bool visible;
			Container<Unit> range_unit_list;
		} TileInfo;
		
	private:
		//ATTRIBUTS
		string  _name;
		Color   _color;
		int     _player_number;
		int     _team_number;
		Scene * _scene;
		// --
		Container<Unit>              _unit_container;       //Contient toutes les unités du joueur
		std::vector<Container<Unit>> _control_group_vector; //Contient 10 slots de groupes d'unités
		//En fait, il faudrait que les groupes de contrôle puissent contenir soit des unités soit des bâtiments !
		
		// --
		//BuildingContainer          _building_container;
		
		std::vector<std::vector<TileInfo> > _map_tile_info;
		
		
	public:
		Player();
		Player(Scene * scene, string name, Color color, int player_number, int team_number);
		
		//Unit*  _unit_selection;
		//Il faudra que je retrouve comment bien initialiser le pointeur. Est ce que ça doit être un container ??
		
		//GET
		string get_name();
		Color  get_color();
		int    get_player_number();
		int    get_team_number();
		// --
		Container<Unit>&              get_unit_container();
		std::vector<Container<Unit>>&	get_control_group_vector();
		//
		Scene * get_scene();
		
		//SET
		void set_name(string name);
		void set_color(Color color);
		void set_player_number(int player_number); //Eviter son utilisation
		void set_team_number(int team_number);     //Eviter son utilisation	
		
		//METHODES
		float compute_percent_of_known_map();   //Renvoie le pourcentage de la map connue
		int   compute_number_player_building(); //Renvoie le nombre de bâtiments du joueur
		bool  is_ally(Player * player);
};

#endif
