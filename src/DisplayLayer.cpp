#include "DisplayLayer.h"

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>

#include "Scene.h"
#include "FogOfWarLayer.h"
#include "FogOfWarDisplayable.h"
#include "DisplayLayer.h"
#include "TileLayer.h"
#include "BackgroundLayer.h"
#include "LayerRGBA.h"
#include "UnitLayer.h"
#include "DoodadLayer.h"
#include "BuildingLayer.h"
#include "MapTile.h"
#include "MissileLayer.h"
#include "Building.h"
#include "Game.h"
#define COEFF     2.1


typedef struct {
	std::string sprite;
	bool        crossUp;
	bool        crossDown;
	bool        crossRight;
	bool        crossLeft;
} TileID;

DisplayLayer::DisplayLayer(): Layer(), _debug_mode(false)
{
	_tile_size = 128;
	std::cout << "Constructeur de DisplayLayer" << std::endl;
	init2();
}


DisplayLayer::DisplayLayer(Game * game): Layer(game), _debug_mode(false)
{
	_tile_size = 128;
	std::cout << "Constructeur de DisplayLayer" << std::endl;
	init2();
}

DisplayLayer::~DisplayLayer() {
	delete _black_layer;
	delete _background_layer;
	delete _opacity_layer;
	delete _tile_layer;
	delete _doodad_layer;
	delete _building_layer;
	delete _unit_layer;
	delete _missile_layer;
	delete _fog_of_war_layer;
	delete _selection_zone_layer;
}

float DisplayLayer::get_tile_size_cocos() { return (float)_tile_size/COEFF; }

void DisplayLayer::addDebugLine(CCPoint p1, CCPoint p2) {
	_debug_line.push_back({b2Vec2(p1.x/PTM_RATIO,p1.y/PTM_RATIO),b2Vec2(p2.x/PTM_RATIO,p2.y/PTM_RATIO)});
}

void DisplayLayer::set_debug_mode(bool debug_mode) {
	if(debug_mode && !_debug_mode) {
		_debug_mode=true;
		removeChild(_black_layer);
		removeChild(_background_layer);
		removeChild(_opacity_layer);
		removeChild(_tile_layer);
		removeChild(_unit_layer);
		removeChild(_fog_of_war_layer);
	}
	else if(!debug_mode && _debug_mode) {
		_debug_mode=false;
		addChild(_black_layer);
		addChild(_background_layer);
		addChild(_opacity_layer);
		addChild(_tile_layer);
		addChild(_unit_layer);
		addChild(_fog_of_war_layer);
	}
}

void DisplayLayer::draw()
{
	//
	CCLayer::draw();

	//afficher les hitbox
	if(_debug_mode) {
		ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
		kmGLPushMatrix();
		get_game()->getWorld()->DrawDebugData();
		b2Color color(1,0,0);
		unsigned int i;
		for(i=0; i<_debug_line.size();i++) {
			get_game()->get_debug_draw()->DrawSegment(_debug_line[i].p1,_debug_line[i].p2,color);
		}

		kmGLPopMatrix();
	}
}

// --- GET ---
BackgroundLayer * DisplayLayer::get_background_layer()
{
	return _background_layer;
}

LayerRGBA * DisplayLayer::get_opacity_layer()
{
	return _opacity_layer;
}

TileLayer * DisplayLayer::get_tile_layer()
{
	return _tile_layer;
}

DoodadLayer * DisplayLayer::get_doodad_layer()
{
	return _doodad_layer;
}

BuildingLayer * DisplayLayer::get_building_layer()
{
	return _building_layer;
}

UnitLayer * DisplayLayer::get_unit_layer()
{
	return _unit_layer;
}

MissileLayer * DisplayLayer::get_missile_layer()
{
	return _missile_layer;
}

FogOfWarLayer * DisplayLayer::get_fog_of_war_layer()
{
	return _fog_of_war_layer;
}

Layer * DisplayLayer::get_selection_zone_layer() {
	return _selection_zone_layer;
}


// --- SET ---


// --- METHODES ---

void DisplayLayer::init2()
{
	// --- Layer de Background noir ---
	_black_layer = new LayerRGBA(get_game());
	_black_layer->setZOrder(0);
	addChild(_black_layer);
		
	// --- Layer de Background avec Tiles ---
	_background_layer = new BackgroundLayer(get_game());
	_background_layer->setZOrder(1);
	addChild(_background_layer);
	
	// --- Layer d'Opacité ---
	_opacity_layer = new LayerRGBA(get_game());
	_opacity_layer->setZOrder(2);
	addChild(_opacity_layer);	
	
	// --- Layer des Tiles ---
	_tile_layer = new TileLayer(get_game());
	_tile_layer->setZOrder(3);
	addChild(_tile_layer);
	
	// --- Layer des Doodads ---
	_doodad_layer = new DoodadLayer(get_game());
	_doodad_layer->setZOrder(4);
	addChild(_doodad_layer);
	
	// --- Layer des Unités ---
	_building_layer = new BuildingLayer(get_game());
	_building_layer->setZOrder(5);
	addChild(_building_layer);
	
	// --- Layer des Unités ---
	_unit_layer = new UnitLayer(get_game());
	_unit_layer->setZOrder(6);
	addChild(_unit_layer);
	
	// --- Layer des Missiles ---
	_missile_layer = new MissileLayer(get_game());
	_missile_layer->setZOrder(7);
	addChild(_missile_layer);
	
	// --- Layer des FogOfWar ---
	_fog_of_war_layer = new FogOfWarLayer(get_game());
	_fog_of_war_layer->setZOrder(8);
	addChild(_fog_of_war_layer);

	_selection_zone_layer = new Layer(get_game());
	_selection_zone_layer->setZOrder(9);
	addChild(_selection_zone_layer);
}

void DisplayLayer::coordonate_tile_to_cocos2dx(int x, int y, float& cocos_x, float& cocos_y) {
	cocos_x = (_tile_size*x)/COEFF;
	cocos_y = (_tile_size*y)/COEFF;
}

void DisplayLayer::coordonate_cocos2dx_to_tile(float cocos_x, float cocos_y, int& x, int& y) {
	x = (int)floor((cocos_x*COEFF+_tile_size/2)/_tile_size);
	y = (int)floor((cocos_y*COEFF+_tile_size/2)/_tile_size);
}

int DisplayLayer::init_file(string filename)
{
	/*
	 * Ne vaut-il pas mieux mettre toutes les initialisations du terrain directement dans le parent ? => DisplayLayer
	 * 
	 */
	
	unsigned int i,j, nombreLigne=0;
	float x,y;
	int findIndex;
	istringstream buffer;
	std::string line, tileString;
	
	std::map<std::string,TileID> sprite_map;
	std::string img_filename;
	bool crossUp, crossDown, crossRight, crossLeft;
	StringMatrix string_matrix;
	
	sprite_map["s00"]= {"tiles/ground/000.png",true,true,true,true};
	sprite_map["f00"]= {"tiles/cliff/000.png",false,false,false,false};

	string_matrix.clear();
	
	ifstream fileMap;
	fileMap.open(filename.c_str());

	if(!fileMap.is_open()) return EXIT_FAILURE;

	if(fileMap.eof()) return EXIT_FAILURE;
	std::getline(fileMap, line);
	findIndex=line.find(',');
	if(findIndex==-1) return EXIT_FAILURE;
	buffer.str(line.substr(0,findIndex));
	buffer >> _map_height;
	buffer.clear();
	buffer.str(line.substr(findIndex+1));
	buffer >> _map_width;
	buffer.clear();
	std::getline(fileMap, line);
	while(!fileMap.eof()) {
		string_matrix.insert(string_matrix.begin(),vector<std::string>());

		for(i=2;i<line.size();i+=4) {
			if(i!=2 && line[i-3]!=' ') return EXIT_FAILURE;
			tileString = line.substr(i-2,3);
			if(tileString[0]<'a' || tileString[0]>'z') {
				if(tileString[0]>='A' && tileString[0]<='Z') {
					tileString[0]+='a'-'A';
				}
				else return EXIT_FAILURE;
			}
			for(j=1;j<3;j++) {
				if(tileString[j]<'0' || tileString[j]>'9') return EXIT_FAILURE;
			}
			string_matrix[0].push_back(tileString);
		}

		if(string_matrix[0].size()!=_map_width) return EXIT_FAILURE;

		nombreLigne++;
		std::getline(fileMap, line);
	}
	if(nombreLigne!=_map_height) return EXIT_FAILURE;
	
	
	// --- BACKGROUND ---
	
	//Création d'une matrice remplie de Tiles identiques. A l'avenir, les données seront chargées à partir du fichier map et du fichier xml associant identifiant de Tile et toutes ses données
	
	for(j=0;j<_map_height;j++)
	{
		_background_layer->get_map_displayable_matrix().push_back(vector<MapDisplayable *>());
		for(i=0;i<_map_width;i++)
		{
			//Faut-il donner le chemin vers l'image ou seulement le nom de fichier de l'image ?
			x = (1/COEFF)*_tile_size*i; //128 = _tile_size => créer cet attribut dans TileLayer ?
			y = (1/COEFF)*_tile_size*j;
			_background_layer->get_map_displayable_matrix()[j].push_back(new MapDisplayable(x,y,"tiles/000.png",get_game(),_background_layer)); //Cela marche-t-il ?
		}
	}
	//_background_layer->addChild(new MapTile(0,0,"000.png"));
	//_background_layer->addChild(new MapTile(500,500,"000.png"));
	//_background_layer->addChild(new MapTile(150,50,"000.png"));
	
	// --- OPACITY ---
	
	//Initilisation de la couche mobile d'opacité variable
		
	//Initialisation de la couche des Tiles
	//Tile temporaire qui est changé tout le temps et se rajoute en Child
	//Hmm, si on modifie cet attribut, le child va-t-il changer ?
	//Il vaut mieux stocker tous les Tiles dans une matrice de Tiles
	
	
	// ATTENTION : faut bien ajouter ça au Tile layer, mais les autres (opacity et background) sont dans d'autres layer et il faut les addChild() ailleurs
	// Comment récupérer le parent ?
	
	// => Réglé : on est dans DisplayLayer maintenant
	
	// --- TILES ---
	
	for(j=0;j<_map_height;j++)
	{
		_tile_layer->get_map_tile_matrix().push_back(vector<MapTile *>());
		for(i=0;i<_map_width;i++)
		{
			//Faut-il donner le chemin vers l'image ou seulement le nom de fichier de l'image ?
			img_filename = sprite_map[string_matrix[j][i]].sprite;
			crossUp = sprite_map[string_matrix[j][i]].crossUp && j!=_map_height-1;
			crossDown = sprite_map[string_matrix[j][i]].crossDown && j!=0;
			crossRight = sprite_map[string_matrix[j][i]].crossRight && i!=_map_width-1;
			crossLeft = sprite_map[string_matrix[j][i]].crossLeft && i!=0;
			
			coordonate_tile_to_cocos2dx(i,j,x,y);
			
			_tile_layer->get_map_tile_matrix()[j].push_back(new MapTile(x,y,img_filename.c_str(),get_game(),_tile_layer,crossUp,crossDown,crossRight,crossLeft)); //Cela marche-t-il ?
		}
	}

	//On aurait également besoin de quelque chose semblable à un dictionnaire en Python; associant un identifiant à un élément stocké.
	//Par exemple id = 1 renvoie un Tile avec l'image 01.png, son type de collisions etc.

	for(j=0;j<_map_height;j++)
	{
		_fog_of_war_layer->get_map_fog_matrix().push_back(vector<FogOfWarDisplayable *>());
		for(i=0;i<_map_width;i++)
		{
			coordonate_tile_to_cocos2dx(i,j,x,y);

			_fog_of_war_layer->get_map_fog_matrix()[j].push_back(new FogOfWarDisplayable(x,y,get_game(),_fog_of_war_layer,FogOfWarDisplayable::undiscovered));
		}
	}
	
	return EXIT_SUCCESS;
}



