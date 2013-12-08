#ifndef PLAYER_H
#define PLAYER_H

//#include "cocos2d.h"

//using namespace cocos2d;

#include <string>

#include "EventReceiver.h"
#include "Game.h"
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
		Game *  _game;
		// --
		Container<Unit>              _unit_container;       //Contient toutes les unités du joueur
		Container<Unit> _unit_selected;
		std::vector<Container<Unit> > _control_group_vector; //Contient 10 slots de groupes d'unités
		//En fait, il faudrait que les groupes de contrôle puissent contenir soit des unités soit des bâtiments !
		
		// --
		//BuildingContainer          _building_container;
		std::vector<Building *>  _building_vector;
		Building *               _qg;
		
		std::vector<std::vector<TileInfo> > _map_tile_info;
		
		
	public:
		Player();
		Player(Game * game, string name, Color color, int player_number, int team_number);
		void init();
		
		//Unit*  _unit_selection;
		//Il faudra que je retrouve comment bien initialiser le pointeur. Est ce que ça doit être un container ??
		
		// --- GET ---
		string get_name();
		Color  get_color();
		int    get_player_number();
		int    get_team_number();
		// --
		Container<Unit>&                get_unit_container();
		std::vector<Container<Unit> >&	get_control_group_vector();
		std::vector<Building *>& get_building_vector();
		Building *               get_qg();

		Unit * get_unit_selected(int index) { return _unit_selected.get_t(index); }
		void   remove_unit_selected(Unit * unit);
		void   add_unit_selected(Unit * unit);
		bool   test_unit_selected(Unit * unit) { return _unit_selected.contain_t(unit); }
		int    get_number_unit_selected() { return _unit_selected.get_number_t(); }
		//
		Game * get_game();
		const std::vector<std::vector<TileInfo> >& get_map_tile_info() { return _map_tile_info; }
		
		// --- SET ---
		void set_name(string name);
		void set_color(Color color);
		void set_player_number(int player_number); //Eviter son utilisation
		void set_team_number(int team_number);     //Eviter son utilisation
		void set_qg(Building * qg);
		
		// --- METHODES ---
		float compute_percent_of_known_map();   //Renvoie le pourcentage de la map connue
		int   compute_number_player_building(); //Renvoie le nombre de bâtiments du joueur
		bool  is_ally(Player * player);

		virtual void on_unit_destroyed(Unit * unit);
		virtual void on_unit_range_tile(int x, int y, Unit * unit);
		virtual void on_unit_unrange_tile(int x, int y, Unit * unit);
};

#endif
