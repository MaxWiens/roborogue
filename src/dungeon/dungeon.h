#ifndef dungeon_h
#define dungeon_h

#include "../object/gameobject.h"
#include "../util/bool.h"
const int DUNGEON_WIDTH = 100;
const int DUNGEON_HEIGHT = 20;

typedef struct Dungeon
{
	int level;
	Square squares[DUNGEON_HEIGHT][DUNGEON_WIDTH];
}Dungeon;


bool add_object(Dungeon* dungeon, GameObject* object);

Dungeon* generate(int seed, int level);

#endif//dungeon_h