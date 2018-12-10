#include "tile.h"
#include "../types.h"
#include <stdlib.h>
char* wall_desc = "A wall covered in circuts and metal.";
char* wall_name = "Wall";
char wall_sprite = '#';
Tile* new_wall(int x, int y) {
	Tile* tile = malloc(sizeof(Tile));
	GameObject go = {
		TypeWall,
		wall_sprite,
		x,
		y,
		100,
		100,
		wall_name,
		wall_desc
	};
	tile->base = go;
	tile->solid = true;

	return tile;
}



char* floor_desc = "A floor covered in circuts and metal.";
char* floor_name = "Floor";
char floor_sprite = '.';
Tile* new_floor(int x, int y) {
	Tile* tile = malloc(sizeof(Tile));
	GameObject go = {
		TypeWall,
		floor_sprite,
		x,
		y,
		0,
		0,
		floor_name,
		floor_desc
	};
	tile->base = go;
	tile->solid = false;

	return tile;
}