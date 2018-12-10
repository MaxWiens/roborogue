#ifndef square_h
#define square_h

#include "../object/tile/tile.h"
#include "../collections/linkedlist.h"
#include "../object/character/character.h"

typedef struct Square
{
	Tile* tile;
	LinkedList* entities;
	Character* character;
}Square;

Square* new_square();
#endif//square_h