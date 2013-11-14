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
	unsigned int i, nombreLigne=0;
	int findIndex;
	istringstream buffer_height, buffer_width;
	string line;

	_int_matrix.clear();
	
	ifstream fileMap;
	fileMap.open(filename.c_str());

	if(!fileMap.is_open()) return EXIT_FAILURE;

	if(fileMap.eof()) return EXIT_FAILURE;
	fileMap >> line;
	findIndex=line.find(',');
	if(findIndex==-1) return EXIT_FAILURE;
	buffer_height.str(line.substr(0,findIndex));
	buffer_height >> _height;
	buffer_width.str(line.substr(findIndex+1));
	buffer_width >> _width;
	fileMap >> line;
	while(!fileMap.eof()) {
		if(line.size()!=_width) return EXIT_FAILURE;
		_int_matrix.push_back(vector<int>());
		for(i=0;i<_width;i++) {
			_int_matrix[nombreLigne].push_back(line[i]);
		}
		nombreLigne++;
		fileMap >> line;
	}
	if(nombreLigne!=_height) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

