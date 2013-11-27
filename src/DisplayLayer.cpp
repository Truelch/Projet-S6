#include "DisplayLayer.h"

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

DisplayLayer::DisplayLayer(): Layer()
{
	_tile_size = 124;
	std::cout << "Constructeur de DisplayLayer" << std::endl;
	init2();
	std::cout << "retour init_file : " << init_file("map/map1") << std::endl;
}


DisplayLayer::DisplayLayer(Scene * scene): Layer(scene)
{
	_tile_size = 124;
	std::cout << "Constructeur de DisplayLayer" << std::endl;
	init2();
	std::cout << "retour init_file : " << init_file("map/map1") << std::endl;
	
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
}


void DisplayLayer::draw()
{
	//
	CCLayer::draw();

	//afficher les hitbox
	/*
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	get_scene()->getWorld()->DrawDebugData();
	kmGLPopMatrix();
	*/
}

// --- GET ---
TileLayer * DisplayLayer::get_background_layer()
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


// --- SET ---


// --- METHODES ---

void DisplayLayer::init2()
{
	// --- Layer de Background noir ---
	_black_layer = new LayerRGBA(get_scene());
	_black_layer->setZOrder(0);
	addChild(_black_layer);
		
	// --- Layer de Background avec Tiles ---
	_background_layer = new TileLayer(get_scene());
	_background_layer->setZOrder(1);
	addChild(_background_layer);
	
	// --- Layer d'Opacité ---
	_opacity_layer = new LayerRGBA(get_scene());
	_opacity_layer->setZOrder(2);
	addChild(_opacity_layer);	
	
	// --- Layer des Tiles ---
	_tile_layer = new TileLayer(get_scene());
	_tile_layer->setZOrder(3);
	addChild(_tile_layer);
	
	// --- Layer des Doodads ---
	_doodad_layer = new DoodadLayer(get_scene());
	_doodad_layer->setZOrder(4);
	addChild(_doodad_layer);
	
	// --- Layer des Unités ---
	_building_layer = new BuildingLayer(get_scene());
	_building_layer->setZOrder(5);
	addChild(_building_layer);
	
	// --- Layer des Unités ---
	_unit_layer = new UnitLayer(get_scene());
	_unit_layer->setZOrder(6);
	addChild(_unit_layer);
	
	// --- Layer des Missiles ---
	_missile_layer = new MissileLayer(get_scene());
	_missile_layer->setZOrder(7);
	addChild(_missile_layer);
}

int DisplayLayer::init_file(string filename)
{
	/*
	 * Ne vaut-il pas mieux mettre toutes les initialisations du terrain directement dans le parent ? => DisplayLayer
	 * 
	 */
	
	unsigned int i,j,x,y, nombreLigne=0;
	int findIndex;
	istringstream buffer;
	std::string line, tileString;

	_string_matrix.clear();
	
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
		_string_matrix.insert(_string_matrix.begin(),vector<std::string>());

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
			std::cout << nombreLigne << "," << _string_matrix[0].size() << " " << tileString << std::endl;
			_string_matrix[0].push_back(tileString);
		}

		if(_string_matrix[0].size()!=_map_width) return EXIT_FAILURE;

		nombreLigne++;
		std::getline(fileMap, line);
	}
	if(nombreLigne!=_map_height) return EXIT_FAILURE;
	
	
	// --- BACKGROUND ---
	
	//Création d'une matrice remplie de Tiles identiques. A l'avenir, les données seront chargées à partir du fichier map et du fichier xml associant identifiant de Tile et toutes ses données
	
	for(j=0;j<_map_height;j++)
	{
		_background_map_tile_matrix.push_back(vector<MapTile *>());
		for(i=0;i<_map_width;i++)
		{
			//Faut-il donner le chemin vers l'image ou seulement le nom de fichier de l'image ?
			x = (1/COEFF)*_tile_size*i; //128 = _tile_size => créer cet attribut dans TileLayer ?
			y = (1/COEFF)*_tile_size*j;
			_background_map_tile_matrix[j].push_back(new MapTile(x,y,"tiles/000.png",get_scene(),this)); //Cela marche-t-il ?
			_background_layer->addChild((_background_map_tile_matrix[j][i])->getSprite());
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
	/*
	for(y=0;y<_map_height;y++)
	{
		for(x=0;x<_map_width;x++)
		{
			//On créé un Tile et on l'ajoute en tant que child dans le Tile Layer
			_tile_layer->addChild(_map_tile_matrix[y][x]); // Cela marche-t-il ?
		}
	}
	*/
	//On aurait également besoin de quelque chose semblable à un dictionnaire en Python; associant un identifiant à un élément stocké.
	//Par exemple id = 1 renvoie un Tile avec l'image 01.png, son type de collisions etc.
	
	return EXIT_SUCCESS;
}



