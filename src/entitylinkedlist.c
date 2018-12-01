
#include "entitylinkedlist.h"
#include <stdlib.h>

EntityLinkedList* remove_entity(EntityLinkedList* list, Entity* entity) {
	if (list == NULL) return list;

	EntityLinkedList* current = list;
	EntityLinkedList* next = current->next;

	if(current->entity == entity){
		free(current);
		return next;
	}

	if(next == NULL)
		return list;

	do {
		current = next;
		next = next->next;
		if(next->entity == entity) {
			current->next = next->next;
			free(next);
			return list;
		}
	}while(next != NULL);
	return list;
}

EntityLinkedList* add_entity(EntityLinkedList* list, Entity* entity) {
	EntityLinkedList* nodeptr = malloc(sizeof(EntityLinkedList));
	EntityLinkedList node = {
		entity,
		list
	};
	*nodeptr = node;
	return nodeptr;
}

EntityLinkedList* new_EntityLinkedList(Entity* entity){
	EntityLinkedList* nodeptr = malloc(sizeof(EntityLinkedList));
	EntityLinkedList node = {
		entity,
		NULL
	};
	*nodeptr = node;
	return nodeptr;
}