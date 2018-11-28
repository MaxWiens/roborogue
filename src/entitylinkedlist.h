#ifndef entitylinkedlist_h
#define entitylinkedlist_h

#include "object/entity/entity.h"
#include "util/bool.h"

typedef struct EntityLinkedList {
	Entity* entity;
	struct EntityLinkedList* next;
}EntityLinkedList;

// bool remove_entity(EntityLinkedList* list, Entity entity)
// Removes an entity from an EntityLinkedList
//
// params
// EntityLinkedList* list - list which to remove from
// Entity* entity - entity to remove
//
// returns
// the modified EntityLinkedList
EntityLinkedList* remove_entity(EntityLinkedList* list, Entity* entity);

// bool add_entity(EntityLinkedList* list, Entity entity)
// Adds an entity to the beginning of an EntityLinkedList
//
// params
// EntityLinkedList* list - list which to add to
// Entity* entity - entity to add
//
// returns
// the modified EntityLinkedList
EntityLinkedList* add_entity(EntityLinkedList* list, Entity* entity);

// EntityLinkedList* new_EntityLinkedList(Entity* entity)
// Creates a new EntityLinkedList
//
// params
// Entity* entity
// Entity to create the EntityLinkedList with
EntityLinkedList* new_EntityLinkedList(Entity* entity);
#endif