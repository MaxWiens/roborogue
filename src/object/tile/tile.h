#ifndef tile_h
#define tile_h

#include "../gameobject.h"
#include "../../util/bool.h"

typedef struct Tile
{
	GameObject base;
	bool solid;
}Tile;

Tile* new_wall(int x, int y);

#endif