#ifndef linkedlist_h
#define linkedlist_h

#include "../util/bool.h"
typedef struct LinkedListNode LinkedListNode;

typedef struct LinkedList LinkedList;

// LinkedList* new_LinkedList();
// Creates and allocates a new linked list
//
// returns a pointer to the new linked list.
LinkedList* new_LinkedList();

void free_LinkedList(LinkedList* list);

// bool enqueue_item(LinkedList* list, void* item)
// Adds an item to the back of the list
//
// params
// LinkedList* list - list which to enqueue to
// void* item - pointer to item to add to the list
//
// returns true if successfull
// returns false if list or item are NULL pointers
bool enqueue_item(LinkedList* list, void* item);

// void* pop_item(LinkedList* list)
// Removes and returns the first item in the list
//
// params
// LinkedList* list - list which to pop from
//
// returns the pointer to item popped or NULL if the list is NULL or is empty
void* pop_item(LinkedList* list);

// bool push_item(LinkedList* list, void* item)
// Adds an item ot the front of the list
//
// params
// LinkedList* list - list which to push to
// void* item - item which to add to the list
//
bool push_item(LinkedList* list, void* item);

// int get_count(LinkedList* list)
// returns the count of the items in the list
int get_count(LinkedList* list);


void* get_item(LinkedList* list, int index);

// BROKEN
// bool remove_item(LinkedList* list, void* item)
// removes a given item with an equivilient pointer from the list
//
// params
// LinkedList* list - list which to remove from
// void* item - item which to remove from the list
bool remove_item(LinkedList* list, void* item);





typedef struct LinkedListIterator LinkedListIterator;

LinkedListIterator* new_Iterator(LinkedList* list);

void free_Iterator(LinkedListIterator* iterator);

bool end(LinkedListIterator* iterator);

void* next(LinkedListIterator* iterator);






#endif//linkedlist_h