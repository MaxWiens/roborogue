#ifndef entitylist_h
#define entitylist_h

#include "object/entity/entity.h"
#include "boolian.h"
// EntityList
// A dynamic list of Entity Objects.
typedef struct EntityList {
	Entity* list;
}EntityList;

// new_entity_list(int initSize)
// Creates a new EntityList.
//
// params
// int initSize - intial size of list, min 1
//
// returns
// new EntityList
EntityList* new_entity_list(int initSize);

// free_entity_list(EntityList list)
// Frees memory the EntityList takes up.
//
// params
// EntityList list - Entity list to free
void free_entity_list(EntityList*);

// add_entity(EntityList list, Entity entity)
// Adds an entity to the list. expands memory if needed.
//
// params
// EntityList list - EntityList to add to
// Entity entity - Entity which to add to the list
void add_entity(EntityList* list, Entity* entity);

// int count_entity_list(EntityList list)
// Counts the number of entities in the EntityList
//
// params
// EntityList list - the list which to count
//
// returns
// Number of entities in the list
int count_entity_list(EntityList* list);

// Entity* get_entity(EntityList list, int index)
// gets a pointer to the Entity at the specified index
//
// param
// EntityList list - list which to get from
// int index - index of the specified Entity
//
// returns
// Entity at the specified index
Entity* get_entity(EntityList* list, int index);

// Entity* remove_entity_index(EntityList list, int index)
// removes an Entity from the EntityList based on the index
//
// param
// EntityList list - list which to remove from
// int index - index of the specified Entity
//
// returns
// true if the removal was successful.
bool remove_entity_index(EntityList* list, int index);

#endif//entitylist_h