#include "MapDisplayable.h"

//  LA CLASSE TILE EXISTE DEJA DANS COCOS2D 

MapDisplayable::MapDisplayable(): Displayable() {

}

MapDisplayable::MapDisplayable(float x, float y, const char * filename, Game * game, Layer * layer): Displayable(x,y,0,filename,game,layer)
{
	
}
