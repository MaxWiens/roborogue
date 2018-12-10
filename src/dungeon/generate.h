#ifndef generate_h
#define generate_h

#include "dungeon.h"
void leafing_algorithm(char tileMap[DUNGEON_HEIGHT][DUNGEON_WIDTH]);
Dungeon* generate(int level);
#endif//generate_h
