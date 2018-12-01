#include "dungeon.h"
#include "../object/types.h"
#include <stdlib.h>




bool add_object(Dungeon* dungeon, GameObject* object, int y, int x) {
	if (object == NULL || dungeon == NULL || y >= DUNGEON_HEIGHT || y < 0 || x >= DUNGEON_WIDTH || x < 0) return false;
	int objtype = object->type;

	if (TypeEntity&objtype){

	}else if (TypeCharacter&objtype) {
		if (dungeon->squares[y][x].character != NULL)
			return false;
	}else if (TypeTile&objtype) {
		if (dungeon->squares[y][x].tile != NULL)
			return false;
	}

	//dungeon->squares[][]

	return true;
}