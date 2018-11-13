#ifndef tile_h
#define tile_h
typedef enum{
	Wall,
	Floor
}TileType;

typedef struct Tile
{
	TileType type;
}Tile;

typedef struct Wall
{
	Tile base;
	int HP;
}Wall;

#endif