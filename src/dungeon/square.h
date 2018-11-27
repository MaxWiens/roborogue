#ifndef square_h
#define square_h

#include "tile.h"
#include "EntityList.h"

typedef struct Square
{
	Tile tile;
	EntityList entities;
	Character character;
}Square;

Square* new_square
#endif//square_h