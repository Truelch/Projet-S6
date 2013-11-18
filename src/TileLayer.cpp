#include "TileLayer.h"

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;


TileLayer::TileLayer(): Layer()
{
}


TileLayer::TileLayer(Scene * scene): Layer(scene)
{
}


// --- GET ---

// --- SET ---


// --- METHODES ---

int TileLayer::init_file(string filename)
{
	/*
	 * Ne vaut-il pas mieux mettre toutes les initialisations du terrain directement dans le parent ? => DisplayLayer
	 * 
	 */
	/*
	unsigned int i,j,x,y, nombreLigne=0, int_tile;
	int findIndex;
	istringstream buffer;
	string line;

	_int_matrix.clear();
	
	ifstream fileMap;
	fileMap.open(filename.c_str());

	if(!fileMap.is_open()) return EXIT_FAILURE;

	if(fileMap.eof()) return EXIT_FAILURE;
	fileMap >> line;
	findIndex=line.find(',');
	if(findIndex==-1) return EXIT_FAILURE;
	buffer.str(line.substr(0,findIndex));
	buffer >> _height;
	buffer.clear();
	buffer.str(line.substr(findIndex+1));
	buffer >> _width;
	buffer.clear();
	fileMap >> line;
	while(!fileMap.eof()) {
		if(line.size()!=_width) return EXIT_FAILURE;
		_int_matrix.insert(_int_matrix.begin(),vector<int>());
		for(i=0;i<_width;i++) {
			buffer.str(string(1,line[i]));
			buffer >> int_tile;
			buffer.clear();
			_int_matrix[0].push_back(int_tile);
		}
		nombreLigne++;
		fileMap >> line;
	}
	if(nombreLigne!=_height) return EXIT_FAILURE;
	
	//Création d'une matrice remplie de Tiles identiques. A l'avenir, les données seront chargées à partir du fichier map et du fichier xml associant identifiant de Tile et toutes ses données
	for(y=0;y<_height;y++)
	{
		for(x=0;x<_width;x++)
		{
			//Faut-il donner le chemin vers l'image ou seulement le nom de fichier de l'image ?
			x = 128*i; //128 = _tile_size => créer cet attribut dans TileLayer ?
			y = 128*j;
			_map_tile_matrix[y][x] = new MapTile(x,y,"000.png"); //Cela marche-t-il ?
		}
	}
	

	//Initialisation de la couche de Background (composé de Tiles identiques)

	/*
	for(y=0;y<_height;y++)
	{
		for(x=0;x<_width;x++)
		{
			//On créé un Tile et on l'ajoute en tant que child dans le Tile Layer
			addChild(_map_tile[y][x]);
		}
	}	
	*/
	
	//Initilisation de la couche mobile d'opacité variable
		
	//Initialisation de la couche des Tiles
	//Tile temporaire qui est changé tout le temps et se rajoute en Child
	//Hmm, si on modifie cet attribut, le child va-t-il changer ?
	//Il vaut mieux stocker tous les Tiles dans une matrice de Tiles
	
	
	// ATTENTION : faut bien ajouter ça au Tile layer, mais les autres (opacity et background) sont dans d'autres layer et il faut les addChild() ailleurs
	// Comment récupérer le parent ?
	/*
	for(y=0;y<_height;y++)
	{
		for(x=0;x<_width;x++)
		{
			//On créé un Tile et on l'ajoute en tant que child dans le Tile Layer
			addChild(_map_tile[y][x]); // Cela marche-t-il ?
		}
	}
	
	//On aurait également besoin de quelque chose semblable à un dictionnaire en Python; associant un identifiant à un élément stocké.
	//Par exemple id = 1 renvoie un Tile avec l'image 01.png, son type de collisions etc.
	
	return EXIT_SUCCESS;*/
}

