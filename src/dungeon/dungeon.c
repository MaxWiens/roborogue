#include "dungeon.h"
#include "../object/types.h"
#include <stdlib.h>
#include "../collections/linkedlist.h"

bool add_object(Dungeon* dungeon, GameObject* object, int y, int x) {
	if (object == NULL || dungeon == NULL || y >= DUNGEON_HEIGHT || y < 0 || x >= DUNGEON_WIDTH || x < 0) return false;
	int objtype = object->type;

	if (TypeEntity&objtype){
		if (dungeon->squares[y][x].entities == NULL)
			dungeon->squares[y][x].entities = new_LinkedList();
		push_item(dungeon->squares[y][x].entities, object);
	}

	if (TypeCharacter&objtype) {
		if (dungeon->squares[y][x].character != NULL)
			return false;
		dungeon->squares[y][x].character = (Character*)object;
		return true;
	}

	if (TypeTile&objtype) {
		if (dungeon->squares[y][x].tile != NULL)
			return false;
		dungeon->squares[y][x].tile = (Tile*)object;
		return true;
	}
	return false;
}

