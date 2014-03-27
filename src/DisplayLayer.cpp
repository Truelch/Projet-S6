#include "DisplayLayer.h"

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <tinyxml.h>
#include <set>
#include <algorithm>

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

float DisplayLayer::get_tile_size_cocos() { return (float)_tile_size/CCDirector::sharedDirector()->getContentScaleFactor(); }

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
		removeChild(_fog_of_war_layer);
	}
	else if(!debug_mode && _debug_mode) {
		_debug_mode=false;
		addChild(_black_layer);
		addChild(_background_layer);
		addChild(_opacity_layer);
		addChild(_tile_layer);
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

	_sprite_map["s00"]= {"tiles/ground/000.png",{none,none,none,none,none,none,none,none},0,ccc4(3,56,100,255)};
										   //Up    Down  Right Left
	_sprite_map["f00"]= {"tiles/cliff/00.png",{collision,collision,collision,collision,collision,collision,collision,collision},1,ccc4(150,255,255,255)};
	_sprite_map["f01"]= {"tiles/cliff/01.png",{none,collision,collision,collision,collision,collision,none,none},1,ccc4(150,255,255,255)};
	_sprite_map["f02"]= {"tiles/cliff/02.png",{none,none,none,collision,collision,collision,collision,collision},1,ccc4(150,255,255,255)};
	_sprite_map["f03"]= {"tiles/cliff/03.png",{collision,collision,none,none,none,collision,collision,collision},1,ccc4(150,255,255,255)};
	_sprite_map["f04"]= {"tiles/cliff/04.png",{collision,collision,collision,collision,none,none,none,collision},1,ccc4(150,255,255,255)};
	_sprite_map["f05"]= {"tiles/cliff/05.png",{none,collision,collision,collision,none,none,none,none},1,ccc4(150,255,255,255)};
	_sprite_map["f06"]= {"tiles/cliff/06.png",{none,none,none,collision,collision,collision,none,none},1,ccc4(150,255,255,255)};
	_sprite_map["f07"]= {"tiles/cliff/07.png",{none,none,none,none,none,collision,collision,collision},1,ccc4(150,255,255,255)};
	_sprite_map["f08"]= {"tiles/cliff/08.png",{collision,collision,none,none,none,none,none,collision},1,ccc4(150,255,255,255)};
	_sprite_map["f09"]= {"tiles/cliff/09.png",{none,none,none,collision,none,none,none,none},1,ccc4(150,255,255,255)};
	_sprite_map["f10"]= {"tiles/cliff/10.png",{none,none,none,none,none,collision,none,none},1,ccc4(150,255,255,255)};
	_sprite_map["f11"]= {"tiles/cliff/11.png",{none,none,none,none,none,none,none,collision},1,ccc4(150,255,255,255)};
	_sprite_map["f12"]= {"tiles/cliff/12.png",{none,collision,none,none,none,none,none,none},1,ccc4(150,255,255,255)};
	_sprite_map["f13"]= {"tiles/cliff/13.png",{none,none,none,none,none,none,none,none},1,ccc4(150,255,255,255)};
	_sprite_map["f14"]= {"tiles/cliff/14.png",{none,gradient,gradient,gradient,none,none,none,none},1,ccc4(150,255,255,255)};
	_sprite_map["f15"]= {"tiles/cliff/15.png",{none,none,none,gradient,gradient,gradient,none,none},1,ccc4(150,255,255,255)};
	_sprite_map["f16"]= {"tiles/cliff/16.png",{none,none,none,none,none,gradient,gradient,gradient},1,ccc4(150,255,255,255)};
	_sprite_map["f17"]= {"tiles/cliff/17.png",{gradient,gradient,none,none,none,none,none,gradient},1,ccc4(150,255,255,255)};
	
}

void DisplayLayer::coordonate_tile_to_cocos2dx(int x, int y, float& cocos_x, float& cocos_y) {
	cocos_x = (_tile_size*x)/CCDirector::sharedDirector()->getContentScaleFactor();
	cocos_y = (_tile_size*y)/CCDirector::sharedDirector()->getContentScaleFactor();
}

void DisplayLayer::coordonate_cocos2dx_to_tile(float cocos_x, float cocos_y, int& x, int& y) {
	x = (int)floor((cocos_x*CCDirector::sharedDirector()->getContentScaleFactor()+_tile_size/2)/_tile_size);
	y = (int)floor((cocos_y*CCDirector::sharedDirector()->getContentScaleFactor()+_tile_size/2)/_tile_size);
}

char DisplayLayer::read_plain_text_file(string filename, StringMatrix& string_matrix) {
	ifstream fileMap;
	istringstream buffer;
	int findIndex;
	std::string line, tileString;
	unsigned int i,j, nombreLigne=0;

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

	return EXIT_SUCCESS;
}

char DisplayLayer::read_tmx_file(string filename, StringMatrix& string_matrix) {
	map<string,string> map_gid_sprite;
	int i,j; 
	const char * gid;
	TiXmlDocument doc(filename);
	TiXmlHandle docHandle(&doc);

	if(!doc.LoadFile()) {
		return EXIT_FAILURE;
	}
	if(!docHandle.FirstChild("map").ToElement()) return EXIT_FAILURE;
	if(!docHandle.FirstChild("map").ToElement()->Attribute("width")) return EXIT_FAILURE;
	if(!docHandle.FirstChild("map").ToElement()->Attribute("height")) return EXIT_FAILURE;
	
	_map_width = atoi(docHandle.FirstChild("map").ToElement()->Attribute("width"));
	if(_map_width<1) return EXIT_FAILURE;
	_map_height = atoi(docHandle.FirstChild("map").ToElement()->Attribute("height"));
	if(_map_height<1) return EXIT_FAILURE;

	i=0;
	while(true)	{
		if(!docHandle.FirstChild( "map" ).Child( "tileset", i ).ToElement()) break;
		gid = docHandle.FirstChild("map").Child("tileset",i).ToElement()->Attribute("firstgid");
		if(!gid) return 0;

		j=0;
		while(true) {
			if(!docHandle.FirstChild("map").Child("tileset",i).FirstChild("tile").FirstChild("properties").Child("property",j).ToElement())
				break;
			if(docHandle.FirstChild("map").Child("tileset",i).FirstChild("tile").FirstChild("properties").Child("property",j).ToElement()->Attribute("name") && strcmp(docHandle.FirstChild("map").Child("tileset",i).FirstChild("tile").FirstChild("properties").Child("property",j).ToElement()->Attribute("name"),"sprite")==0 && docHandle.FirstChild("map").Child("tileset",i).FirstChild("tile").FirstChild("properties").Child("property",j).ToElement()->Attribute("value")) {
				map_gid_sprite[string(gid)] = string(docHandle.FirstChild("map").Child("tileset",i).FirstChild("tile").FirstChild("properties").Child("property",j).ToElement()->Attribute("value"));
				break;
			}
			j++;
		}

		++i;
	}

	if(!docHandle.FirstChild("map").FirstChild("layer").ToElement()) return EXIT_FAILURE;
	if(!docHandle.FirstChild("map").FirstChild("layer").FirstChild("data").ToElement()) return EXIT_FAILURE;

	i=-1;
	j=0;
	while(true)	{
		i++;
		if(!docHandle.FirstChild("map").FirstChild("layer").FirstChild("data").Child("tile",i).ToElement())
			break;
		if(!docHandle.FirstChild("map").FirstChild("layer").FirstChild("data").Child("tile",i).ToElement()->Attribute("gid")) continue;
		if(map_gid_sprite.find(docHandle.FirstChild("map").FirstChild("layer").FirstChild("data").Child("tile",i).ToElement()->Attribute("gid"))==map_gid_sprite.end()) continue;

		if(j%_map_width==0) string_matrix.insert(string_matrix.begin(),vector<std::string>());
		string_matrix[0].push_back(map_gid_sprite[docHandle.FirstChild("map").FirstChild("layer").FirstChild("data").Child("tile",i).ToElement()->Attribute("gid")]);

		j++;
	}

	if(string_matrix.size()!=_map_height) return EXIT_FAILURE;
	for(i=0;i<(int)_map_height;i++) {
		if(string_matrix[i].size()!=_map_width) return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

std::string DisplayLayer::search_sprite(JointSet jointSet, int level) {

	std::map<std::string,TileID>::iterator it;
	std::string result;
	Joint *jointTest, *jointIt;
	jointTest = &jointSet.up;
	int i;

	for(it=_sprite_map.begin(); it!=_sprite_map.end(); it++) {
		if(it->second.level!=level) continue;
		jointIt = &(it->second.jointSet.up);
		for(i=0;i<8;i++) {
			if( (*(jointIt+i)) != (*(jointTest+i)) ) break;
		}
		if(i==8) return it->first;
	}
	return result;
}

void DisplayLayer::check_string_tile(const StringMatrix& string_matrix, unsigned int i, unsigned int j, std::string& new_sprite, int& falsity) {

	JointSet jointSet = {none,none,none,none,none,none,none,none};
	Joint joint,jointAdj;
	unsigned int k,l, i_adj, j_adj;
	TileID * tileID;
	TileID * tileAdjID[3];

	new_sprite.clear();
	falsity=0;
	tileID = &(_sprite_map[string_matrix[i][j]]);
	
	for(k=0;k<8;k+=2) {
		if(k&2) {
			i_adj=i;
			j_adj=k&4?j-1:j+1;
		}
		else {
			i_adj=k&4?i-1:i+1;
			j_adj=j;
		}

		if(i_adj>=0 && i_adj<_map_height && j_adj>=0 && j_adj<_map_width) {
			joint = *(&tileID->jointSet.up+k);
			tileAdjID[0]=&(_sprite_map[string_matrix[i_adj][j_adj]]);
			jointAdj = *(&tileAdjID[0]->jointSet.up+(k^4));
			if( ( joint==gradient &&
				  tileID->level-1!=tileAdjID[0]->level ) ||
				( joint==none &&
				  ( tileID->level>tileAdjID[0]->level ||
				    ( tileID->level==tileAdjID[0]->level &&
					  jointAdj!=none ) ) ) )
			{
				falsity++;
				*(&jointSet.up+k)=collision;
			}
			else *(&jointSet.up+k)=*(&tileID->jointSet.up+k);
		}
		else {
			*(&jointSet.up+k)=*(&tileID->jointSet.up+k);
		}
	}
	for(k=1;k<8;k+=2) {
		i_adj=(((k&4)>>1)^(k&2))?i-1:i+1;
		j_adj=k&4?j-1:j+1;

		joint = *(&tileID->jointSet.up+k);
		if(i_adj>=0 && i_adj<_map_height && j_adj>=0 && j_adj<_map_width)
			tileAdjID[0]=&(_sprite_map[string_matrix[i_adj][j_adj]]);
		else tileAdjID[0]=NULL;
		if(j_adj>=0 && j_adj<_map_width)
			tileAdjID[1]=&(_sprite_map[string_matrix[i][j_adj]]);
		else tileAdjID[1]=NULL;
		if(i_adj>=0 && i_adj<_map_height)
			tileAdjID[2]=&(_sprite_map[string_matrix[i_adj][j]]);
		else tileAdjID[2]=NULL;

		if(joint==gradient) {
			for(l=0;l<3;l++) {
				if(tileAdjID[l] && tileID->level-1==tileAdjID[l]->level) break;
			}
			if(l!=3) *(&jointSet.up+k)=*(&tileID->jointSet.up+k);
			else {
				falsity++;
				*(&jointSet.up+k)=collision;
			}
		}
		else if(joint==none) {
			for(l=0;l<3;l++) {
				if(tileAdjID[l] && tileID->level>tileAdjID[l]->level )
					break;
			}
			if(l!=3) {
				falsity++;
				*(&jointSet.up+k)=collision;
			}
			else *(&jointSet.up+k)=*(&tileID->jointSet.up+k);
		}
		else *(&jointSet.up+k)=*(&tileID->jointSet.up+k);

	}

	if(falsity) {
		//std::cout << i << "," << j << " " << new_sprite << " ";
		//for(k=0;k<8;k++) std::cout << *(&jointSet.up+k);
		//std::cout << std::endl;
		new_sprite=search_sprite(jointSet,tileID->level);
		if(new_sprite.empty()) {
			for(k=0;k<8;k++) {
				if(*(&jointSet.up+k)==gradient) *(&jointSet.up+k)=collision;
			}
			new_sprite=search_sprite(jointSet,tileID->level);
			if(new_sprite.empty()) {
				for(k=0;k<8;k++) {
					if(*(&jointSet.up+k)==none) *(&jointSet.up+k)=collision;
				}
				new_sprite=search_sprite(jointSet,tileID->level);
			}
		}
	}
}

void DisplayLayer::check_string_matrix(StringMatrix& string_matrix) {
	bool change_map=false;
	int falsity;
	unsigned int i,j;
	int k,l;
	std::string new_sprite;
	std::set<TileSetItem> tileSet;
	std::set<TileSetItem>::iterator it;

	(void)change_map;
	
	for(i=0; i<_map_height; i++) {
		for(j=0; j<_map_width; j++) {
			check_string_tile(string_matrix, i,j, new_sprite, falsity);
			if(falsity) {
				tileSet.insert(TileSetItem(i,j,new_sprite,falsity));
			}
		}
	}

	while(!tileSet.empty()) {
		i=tileSet.rbegin()->_i;
		j=tileSet.rbegin()->_j;
		string_matrix[i][j]=(--tileSet.end())->_sprite;
		tileSet.erase(--tileSet.end());
		for(k=-1;k<2;k++) {
			for(l=-1;l<2;l++) {
				if(i+k<0 || i+k>=_map_height || j+l<0 || j+l>=_map_width || ( k==0 && l==0 ) )
					continue;
				it = std::find(tileSet.begin(),tileSet.end(),TileSetItem(i+k,j+l));
				if(it!=tileSet.end()) tileSet.erase(it);
				check_string_tile(string_matrix, i+k,j+l, new_sprite, falsity);
				if(falsity) {
					tileSet.insert(TileSetItem(i+k,j+l,new_sprite,falsity));
				}
			}
		}
	}
}

char DisplayLayer::init_file(string filename)
{
	/*
	 * Ne vaut-il pas mieux mettre toutes les initialisations du terrain directement dans le parent ? => DisplayLayer
	 * 
	 */
	unsigned int i,j;
	float x,y;
	std::string img_filename;
	bool crossUp, crossDown, crossRight, crossLeft;
	StringMatrix string_matrix;
	string extension;

	string_matrix.clear();

	i = filename.rfind("/");
	if(i!=filename.size()-1 && i!=string::npos) extension = filename.substr(i+1);
	else extension = filename;

	i = extension.rfind(".");
	if(i!=0 && i!=extension.size()-1 && i!=string::npos) extension = extension.substr(i+1);
	else extension=string();

	if(extension=="tmx") {
		if(read_tmx_file(filename,string_matrix)==EXIT_FAILURE) return EXIT_FAILURE;
	}
	else if(read_plain_text_file(filename,string_matrix)==EXIT_FAILURE) return EXIT_FAILURE;

	check_string_matrix(string_matrix);
	
	// --- BACKGROUND ---
	
	//Création d'une matrice remplie de Tiles identiques. A l'avenir, les données seront chargées à partir du fichier map et du fichier xml associant identifiant de Tile et toutes ses données
	
	for(j=0;j<_map_height;j++)
	{
		_background_layer->get_map_displayable_matrix().push_back(vector<MapDisplayable *>());
		for(i=0;i<_map_width;i++)
		{
			//Faut-il donner le chemin vers l'image ou seulement le nom de fichier de l'image ?
			x = (1/CCDirector::sharedDirector()->getContentScaleFactor())*_tile_size*i; //128 = _tile_size => créer cet attribut dans TileLayer ?
			y = (1/CCDirector::sharedDirector()->getContentScaleFactor())*_tile_size*j;
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
			img_filename = _sprite_map[string_matrix[j][i]].sprite;
			crossUp = _sprite_map[string_matrix[j][i]].jointSet.up!=collision && j!=_map_height-1;
			crossDown = _sprite_map[string_matrix[j][i]].jointSet.down!=collision && j!=0;
			crossRight = _sprite_map[string_matrix[j][i]].jointSet.right!=collision && i!=_map_width-1;
			crossLeft = _sprite_map[string_matrix[j][i]].jointSet.left!=collision && i!=0;
			
			coordonate_tile_to_cocos2dx(i,j,x,y);
			
			_tile_layer->get_map_tile_matrix()[j].push_back(new MapTile(string_matrix[j][i],x,y,img_filename.c_str(),get_game(),_tile_layer,crossUp,crossDown,crossRight,crossLeft)); //Cela marche-t-il ?
		}
	}

	//On aurait également besoin de quelque chose semblable à un dictionnaire en Python; associant un identifiant à un élément stocké.
	//Par exemple id = 1 renvoie un Tile avec l'image 01.png, son type de collisions etc.

	for(j=0;j<_map_height;j++)
	{
		_fog_of_war_layer->get_map_fog_matrix().push_back(vector<FogOfWarDisplayable *>());
		for(i=0;i<_map_width;i++)
		{
			_fog_of_war_layer->get_map_fog_matrix()[j].push_back(new FogOfWarDisplayable(i,j,get_game(),_fog_of_war_layer,FogOfWarDisplayable::undiscovered));
		}
	}
	
	return EXIT_SUCCESS;
}



