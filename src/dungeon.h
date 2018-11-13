#ifndef dungeon_h
#define dungeon_h

typedef struct Dungeon
{
	int level,
	Tile* tiles,
	Entity* entities
}Dungeon;

generate(int seed, int level, int width, int height);

#endif // dungeon_h