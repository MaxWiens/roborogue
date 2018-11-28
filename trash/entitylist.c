#include "object/entity/entity.h"
#include <stdlib.h>
#include "util/bool.h"

typedef struct EntityList {
	Entity * list;
	int size;
	int maxSize;
}EntityList;


EntityList* new_entity_list(int initSize) {
	int maxSize = 1;
	if (initSize >=1) {
		maxSize = initSize;
	}
	Entity* entityptr = malloc(sizeof(Entity));
	EntityList* newEntityListPtr = malloc(sizeof(EntityList));

	EntityList newEntityList = {
		entityptr,
		-1,
		maxSize
	};
	*newEntityListPtr = newEntityList;
	return newEntityListPtr;
}

void free_entity_list(EntityList* list) {
	free(list->list);
	free(list);
}

void add_entity(EntityList* list, Entity* entity) {
	// checks if the list is full and allocates more memory if needed
	list->size++;
	if (list->size == list->maxSize) {
		list->maxSize *= 2;
		list->list = realloc(list->list, list->maxSize*sizeof(Entity));
	}
	*(list->list+list->size) = *entity;
}

int count_entity_list(EntityList* list){
	return list->size+1;
}

Entity* get_entity_list(EntityList* list, int index) {
	if (index < 0 || index > list->size) return NULL;
	return list->list+index;
}

bool remove_entity_index(EntityList* list, int index) {
	return true;
}