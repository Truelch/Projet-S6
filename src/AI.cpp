#include "AI.h"
#include "Scene.h"
#include "Player.h"
#include "Unit.h"
#include "DisplayLayer.h"
#include "UnitLayer.h"
#include "Building.h"
#include "TileLayer.h"
//Random
#include <stdlib.h>     /* srand, rand */

AI::AI(): EventReceiver()
{
	//
	std::cout << "Constructeur d'AI" << std::endl;
	set_periodic_time(0);
	set_go(false);
}

AI::AI(Scene * scene, Player * player, Difficulty difficulty): EventReceiver(scene->getEventHandler()), _scene(scene)
{
	//
	_player = player;
	std::cout << "Constructeur d'AI" << std::endl;
	if(difficulty==d_easy)
	{
		set_play_style(ps_defensive);
		set_coeff_ressource(0.5);
		set_dt_time(2.0);
		set_omniscience(false);
	}

	else if(difficulty==d_medium)
	{
		set_play_style(ps_balanced);
		set_coeff_ressource(1.0);
		set_dt_time(0.5);
		set_omniscience(false);
	}
	
	else if(difficulty==d_hard)
	{
		//Cette AI cheat !
		set_play_style(ps_offensive);
		set_coeff_ressource(2.0);
		set_dt_time(0.0);
		set_omniscience(true);
	}	
	set_periodic_time(0);
	set_go(false);
}

AI::AI(Scene * scene, Player * player, AI::PlayStyle play_style, float coeff_ressource, float dt_time, bool omniscience): EventReceiver(scene->getEventHandler()), _scene(scene)
{
	_player = player;
	std::cout << "Constructeur d'AI" << std::endl;
	set_play_style(play_style);
	set_coeff_ressource(coeff_ressource);
	set_dt_time(dt_time);
	set_omniscience(omniscience);
	set_periodic_time(0);
	set_go(false);
}


// --- GET ---

AI::Difficulty AI::get_difficulty()
{
	return _difficulty;
}

AI::PlayStyle AI::get_play_style()
{
	return _play_style;
}

float AI::get_coeff_ressource()
{
	return _coeff_ressource;
}

float AI::get_dt_time()
{
	return _dt_time;
}

bool AI::get_omniscience()
{
	return _omniscience;
}

float AI::get_percent_life_min()
{
	return _percent_life_min;
}

float AI::get_periodic_time()
{
	return _periodic_time;
}

bool AI::get_go()
{
	return _go;
}

//

Unit * AI::get_unit(int index, Container<Unit> * list)
{
	return list->get_t(index);
}

void AI::remove_unit(Unit * unit, Container<Unit> * list)
{
	list->remove_t(unit);
}

void AI::add_unit(Unit * unit, Container<Unit> * list)
{
	//On n'a pas à créer une unité ici (contraire à l'UnitLayer), on se contente de manipuler des unités déjà instanciées
	list->add_t(unit);
}

int AI::get_number_unit(Container<Unit> * list) 
{
	return list->get_number_t();
}

//

/*

AttackManager * AI::get_attack_manager()
{
	return _attack_manager;
}

DefenseManager * AI::get_defense_manager()
{
	return _defense_manager;
}

ScoutManager * AI::get_scout_manager()
{
	return _scout_manager;
}

CaptureManager * AI::get_capture_manager()
{
	return _capture_manager;
}

RetreatManager * AI::get_retreat_manager()
{
	return _retreat_manager;
}

*/

Scene* AI::get_scene()
{
	return _scene;
}

Player* AI::get_player()
{
	return _player;
}
//
std::vector<Building * >& AI::get_discovered_building_vector()
{
	return _discovered_building_vector;
}

// --- SET ---

void AI::set_difficulty(AI::Difficulty difficulty)
{
	_difficulty = difficulty;
}

void AI::set_play_style(AI::PlayStyle play_style)
{
	_play_style = play_style;
}


void AI::set_coeff_ressource(float coeff_ressource)
{
	_coeff_ressource = coeff_ressource;
	
}

void AI::set_dt_time(float dt_time)
{
	_dt_time = dt_time;
	//set_difficulty = custom; //Comme on modifie des paramètres de l'AI pendant la partie, elle est customisée. Faire attention à ne pas l'utiliser quand elle est crée, sinon
}

void AI::set_omniscience(bool omniscience)
{
	_omniscience = omniscience;
}

void AI::set_percent_life_min(float percent_life_min)
{
	_percent_life_min = percent_life_min;
}

void AI::set_periodic_time(float periodic_time)
{
	_periodic_time = periodic_time;
}

void AI::set_go(bool go)
{
	_go = go;
}

void AI::set_scene(Scene * scene)
{
	_scene = scene;
}

void AI::set_player(Player * player)
{
	_player = player;
}

// --- METHODES ---

void AI::update(float dt)
{
	set_periodic_time(_periodic_time+dt);
	if((_periodic_time>75) && (_go==false))
	{
		_go = true;
	}
	if((_periodic_time>10) && (_go==true))
	{
		set_periodic_time(0);
		ai_handler();
	}
}

void AI::ai_monitor()
{
	// --- Affectation des ordres aux unités ---
	affecting_order();
	
	// --- Ordre de construction des unités ---
}

void AI::ai_handler() // PRESENTATION
{
	//Pour la présentation
	float percent_of_life;
	float percent_life_min = 0.2;
	int x,y,x_max,y_max,i;
	int max_index = _player->get_game()->get_main_player()->get_unit_container().get_number_t();
	if(max_index == 0) return;
	x_max = _player->get_game()->get_display_layer()->get_map_width();
	y_max = _player->get_game()->get_display_layer()->get_map_height();
	
	int random_index = rand() % max_index;

	for(i=0;i<_player->get_unit_container().get_number_t();i++)
	{
		if(_player->get_unit_container().get_t(i)->get_name()!="boss")
		{
			percent_of_life = _player->get_unit_container().get_t(i)->get_hp()/(float)_player->get_unit_container().get_t(i)->get_hp_max();
			if (percent_of_life > percent_life_min) //Unité en état de combattre
			{
				x = _player->get_game()->get_main_player()->get_unit_container().get_t(random_index)->getSprite()->getPositionX();
				y = _player->get_game()->get_main_player()->get_unit_container().get_t(random_index)->getSprite()->getPositionY();
				_player->get_unit_container().get_t(i)->set_destination(x,y);
			}
			
			else //hp trop faibles
			{
				//x, y random !
				std::cout << x_max << "," << y_max << std::endl;
				x = rand() % x_max;
				y = rand() % y_max;	
				_player->get_unit_container().get_t(i)->set_destination(x,y);
			}
		}
	}
}



// --- METHODES APPELEES PAR LE MONITOR

void AI::affecting_order()
{
	
	/*
	int i;
	float percent_of_life;
	float need_scout, need_capture, need_attack, need_defense;
	float scout_value=0, capture_value=0, attack_value=0, defense_value=0; //Not used, mais si je commente, marche tjr pas !
	float max = 0;
	std::string order = "scout";
	//std::cout << "Scout value : " << scout_value << "Capture value : " << capture_value << "Attack value : " << attack_value << "Defense value : " << defense_value << std::endl;
	//Boucle for traversant les unités du joueur
	// ------------------------------------
	// --- ORDRE AFFECTE A CHAQUE UNITE ---
	// ------------------------------------
	for(i=0;i<_player->get_unit_container().get_number_t();i++)
	{
		//i désigne seulement l'index de l'unité dans le container (et pas l'élément lui-même comme en Python)
		//On affecte un ordre que si l'unité est oisive. Après, dans les différents manager, elle peut quitter son affectation pour une autre à certaines conditions..
		if(get_player()->get_unit_container().get_t(i)->get_ai_stat()->get_state()==AIStat::s_inactive)
		{
			//Vérification si l'unité est en état de se battre
			percent_of_life = _player->get_unit_container().get_t(i)->get_hp()/(float)_player->get_unit_container().get_t(i)->get_hp_max();
			if (percent_of_life > _percent_life_min) //Unité en état de combattre
			{
				// --- SCOUT ---
				//Calcul de scout_value, def_value, att_value et capture_value (ce dernier vérifiant la distance de l'unité à un élément capurable ?
				need_scout  = compute_need_scout();
				scout_value = (_player->get_unit_container().get_t(i)->get_ai_stat()->get_scout()) * need_scout;
				
				// --- CAPTURE ---
				need_capture  = compute_need_capture();
				capture_value = (_player->get_unit_container().get_t(i)->get_ai_stat()->get_capture()) * need_capture;
				
				// --- ATTACK ---
				need_attack   = compute_need_attack();
				attack_value  = (_player->get_unit_container().get_t(i)->get_ai_stat()->get_attack()) * need_attack;
							
				// --- DEFENSE ---
				need_defense  = compute_need_capture();
				defense_value = (_player->get_unit_container().get_t(i)->get_ai_stat()->get_defense()) * need_defense;
				
				// --- CALCUL DU MAX(SCOUT, CAPTURE, ATTACK, DEFENSE) ---
				max = need_scout;
				
				
				
				if (need_capture > max)
				{
					order = "capture";
				}
				
				else if (need_attack > max)
				{
					order = "attack";
				}
				
				else if (need_defense > max)
				{
					order = "defense";
				}
				
				// --- --- ---
				
				
				if (order == "scout")   
				{
					//_player->get_unit_container().get_t(i)->scout();
					//Comportement d'unité ; Rajouter un attribut pour le comportement intelligent d'une unité
					
					//Changer son attribut d'état
					get_player()->get_unit_container().get_t(i)->get_ai_stat()->set_state(AIStat::s_scout);
					//La rajouter dans le conteneur des unités affectées au scouting
					add_unit(get_player()->get_unit_container().get_t(i),&_scout_list);
				}   
				
				else if (order == "capture") 
				{
					//_player->get_unit_container().get_t(i)->capture();
					
					//Changer son attribut d'état
					get_player()->get_unit_container().get_t(i)->get_ai_stat()->set_state(AIStat::s_capture);
					//La rajouter dans le conteneur des unités affectées au scouting
					add_unit(get_player()->get_unit_container().get_t(i),&_capture_list);
				}
				
				else if (order == "attack")  
				{
					//_player->get_unit_container().get_t(i)->attack();
					
					//Changer son attribut d'état
					get_player()->get_unit_container().get_t(i)->get_ai_stat()->set_state(AIStat::s_attack);
					//La rajouter dans le conteneur des unités affectées au scouting
					add_unit(get_player()->get_unit_container().get_t(i),&_attack_list);					
				}
				
				else if (order == "defense") 
				{
					//_player->get_unit_container().get_t(i)->defense();
					
					//Changer son attribut d'état
					get_player()->get_unit_container().get_t(i)->get_ai_stat()->set_state(AIStat::s_defense);
					//La rajouter dans le conteneur des unités affectées à la défense
					add_unit(get_player()->get_unit_container().get_t(i),&_defense_list);					
				}
			}
			
			else //hp trop faibles
			{
				//i->get_ai_stat()->retreat(_player->get_unit_container().get_t(i)); //set_destination(x_QG,y_QG); + impossible de lui redonner d'autres ordres
				
			}
		}
	}
			
	*/
}


void AI::build_order()
{
	//
	
}

float AI::compute_need_scout()
{
	int number_player_building = _player->compute_number_player_building();
	
	float need_scout             = 0.0;
	//Appel d'une fonction renvoie un float percent_of_map_know = nbrTilesConnus / nbrTotalTiles
	float percent_of_known_map   = _player->compute_percent_of_known_map(); //Pourcentage de la carte connue 0.0 => 1.0
	float percent_of_unknown_map = 1 - percent_of_known_map;                //Pourcentage de la carte inconnue
	
	float coeff = 10; //coefficient de normalisation avec les valeurs de priorité. Sert à l'ajustement
	
	//Faire calcul du nombre de bâtiments neutres connus
	
	//Si nbr de bâtiments capturés = 0 (nbr bat == 1 avec le QG) => capture
	//nbr bâtiments visibles = 0 => priorité absolue (n)
	if(number_player_building == 0)
	{
		need_scout = 10000; //Priorité maximale
	}
	else //Calcul normal
	{
		need_scout = coeff * percent_of_unknown_map;
	}

	//
	
	return need_scout;
}

float AI::compute_need_capture()
{
	float need_capture = 0.0;
	
	//Si nbr bâtiments capturés = 0 => Priorité absolue (n-1)
	int controlled_building = get_player()->get_building_vector().size();
	if(controlled_building == 1) //Le QG compte dans les bâtiments
	{
		need_capture = 1000; //Grande priorité
	}
	else
	{
		//
	}
	
	//
	return need_capture;
}

float AI::compute_need_attack()
{
	float need_attack = 0.0;
	//
	
	
	return need_attack;
}

float AI::compute_need_defense()
{
	float need_defense = 0.0;
	//
	
	
	return need_defense;
}

void AI::attack_management()
{
	//
}

void AI::defense_management()
{
	//
}

void AI::scout_management()
{
	int x,y,x_max,y_max,i;
	x_max = _player->get_game()->get_display_layer()->get_map_width();
	y_max = _player->get_game()->get_display_layer()->get_map_height();
	//A partir du conteneur de scout formé, on donne les ordres à chacun
	//Ici, on envoie les unités dans des directions random, en faisant attention à ce qu'elles aillent tout de même vers du terrain non-exploré
	for(i=0;i<_scout_list.get_number_t();i++) //On traverse le container à unité qui scoutent
	{
		x = rand() % x_max;
		y = rand() % y_max;		
		while(_player->get_map_tile_info()[y][x].discovered == true) //Attention si tout le terrain a déjà été découvert !
		{
			x = rand() % x_max;
			y = rand() % y_max;	
		}	
		if (_player->get_map_tile_info()[y][x].discovered == false)
		{		
			//Go go go !
			get_player()->get_unit_container().get_t(i)->set_destination(x,y);
		}	
	}
}

void AI::capture_management()
{
	//Pour chaque bâtiment donné, on regarde l'unité la plus à même de le capturer. Personne d'autre ne s'occupe de la capture => Quoique ?
	
}

void AI::on_player_discovered_tile(int x, int y, Player * player)
{
	if(player == _player)
	{
		Building * building;
		//Si il y a un bâtiment, on le rajoute dans la liste des bâtiments
		building = _player->get_game()->get_display_layer()->get_tile_layer()->get_map_tile_matrix()[y][x]->get_building();
		if(building)
		{
			//On rajoute le bâtiment dans la liste des bâtiments découverts du Joueur
			_discovered_building_vector.push_back(building);
		}
	}
}
