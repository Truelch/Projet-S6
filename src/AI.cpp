#include "AI.h"
#include "Scene.h"
#include "Player.h"
#include "Unit.h"

AI::AI(): EventReceiver()
{
	//
	std::cout << "Constructeur d'AI" << std::endl;
}

AI::AI(Scene * scene, Difficulty difficulty): EventReceiver(scene->getEventHandler()), _scene(scene)
{
	//
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
}

AI::AI(Scene * scene, AI::PlayStyle play_style, float coeff_ressource, float dt_time, bool omniscience): EventReceiver(scene->getEventHandler()), _scene(scene)
{
	std::cout << "Constructeur d'AI" << std::endl;
	set_play_style(play_style);
	set_coeff_ressource(coeff_ressource);
	set_dt_time(dt_time);
	set_omniscience(omniscience);
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

Scene* AI::get_scene()
{
	return _scene;
}

Player* AI::get_player()
{
	return _player;
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

void AI::set_scene(Scene * scene)
{
	_scene = scene;
}

void AI::set_player(Player * player)
{
	_player = player;
}

// --- METHODES ---

void AI::ai_monitor()
{
	// --- Affectation des ordres aux unités ---
	affecting_order();
	
	// --- Ordre de construction des unités ---
}



// --- METHODES APPELEES PAR LE MONITOR

void AI::affecting_order()
{
	
	int i;
	float percent_of_life;
	float need_scout, need_capture, need_attack, need_defense;
	float scout_value=0, capture_value=0, attack_value=0, defense_value=0; //Not used, mais si je commente, marche tjr pas !
	float max = 0;
	std::string order = "scout";
	std::cout << "Scout value : " << scout_value << "Capture value : " << capture_value << "Attack value : " << attack_value << "Defense value : " << defense_value << std::endl;
	//Boucle for traversant les unités du joueur
	// ------------------------------------
	// --- ORDRE AFFECTE A CHAQUE UNITE ---
	// ------------------------------------
	for(i=0;i<_player->get_unit_container().get_number_t();i++)
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
			
			
			if      (order == "scout")   
			{
				//_player->get_unit_container().get_t(i)->scout();
				//Comportement d'unité ; Rajouter un attribut pour le comportement intelligent d'une unité
				
			}   
			
			else if (order == "capture") 
			{
				//_player->get_unit_container().get_t(i)->capture();
			}
			
			else if (order == "attack")  
			{
				//_player->get_unit_container().get_t(i)->attack();
			}
			
			else if (order == "defense") 
			{
				//_player->get_unit_container().get_t(i)->defense();
			}
		}
		
		else //hp trop faibles
		{
			//retreat(_player->get_unit_container().get_t(i)); //set_destination(x_QG,y_QG); + impossible de lui redonner d'autres ordres
			
		}
	}
			
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
	float percent_of_unknown_map = 1 - percent_of_known_map;        //Pourcentage de la carte inconnue
	
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
	if(1)
	{
		need_capture = 1000;
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
