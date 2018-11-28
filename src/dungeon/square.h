#ifndef square_h
#define square_h

#include "../object/tile.h"
#include "../entitylinkedlist.h"
#include "../object/character/character.h"

typedef struct Square
{
	Tile* tile;
	EntityLinkedList* entities;
	Character* character;
}Square;

Square* new_square();
#endif//square_h