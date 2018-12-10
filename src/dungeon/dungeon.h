#ifndef dungeon_h
#define dungeon_h

#include "../object/gameobject.h"
#include "../util/bool.h"
#include "square.h"


#define DUNGEON_HEIGHT 25
#define DUNGEON_WIDTH 100


typedef struct Dungeon
{
	int level;
	Square squares[DUNGEON_HEIGHT][DUNGEON_WIDTH];

}Dungeon;

// bool add_object(Dungeon* dungeon, GameObject* object, int y, int x);
// adds an object to the dungeon at a specified position
bool add_object(Dungeon* dungeon, GameObject* object, int y, int x);

bool move_object(Dungeon* dungeon, GameObject* object, int y, int x);

void print_dungeon(Dungeon* dungeon, char arr[DUNGEON_HEIGHT][DUNGEON_WIDTH]);

#endif//dungeon_h