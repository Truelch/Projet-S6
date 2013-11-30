#include "MapDisplayable.h"

//  LA CLASSE TILE EXISTE DEJA DANS COCOS2D 

MapDisplayable::MapDisplayable(): Displayable() {

}

MapDisplayable::MapDisplayable(float x, float y, const char * filename, Scene * scene, Layer * layer): Displayable(x,y,0,filename,scene,layer)
{
	
}
