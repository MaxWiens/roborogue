#include <stdlib.h>
#include "linkedlist.h"

struct LinkedListNode {
	void* item;
	LinkedListNode* next;
};

struct LinkedList {
	LinkedListNode* head;
	LinkedListNode* tail;
	int count;
};

LinkedList* new_LinkedList() {
	LinkedList* list = malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
	return list;
}

void free_LinkedList(LinkedList* list) {
	while(list->count != 0){
		pop_item(list);
	}
	free(list);
}

bool enqueue_item(LinkedList* list, void* item) {
	if(list == NULL || item == NULL) return false;

	LinkedListNode* newNode = malloc(sizeof(LinkedListNode));
	newNode->item = item;
	newNode->next = NULL;
	if(list->count == 0)
		list->head = newNode; // sets the head node if the list is empty
	else
		list->tail->next = newNode; // makes the tail node point to the new node
	list->tail = newNode;
	list->count++;
	return true;
}


void* pop_item(LinkedList* list) {
	if(list == NULL || list->count == 0) return NULL;

	void* item = list->head->item;
	LinkedListNode* next = list->head->next;
	free(list->head);
	list->head = next;
	list->count--;

	return item;
}

bool push_item(LinkedList* list, void* item) {
	if(list == NULL || item == NULL) return false;

	LinkedListNode* newNode = malloc(sizeof(LinkedListNode));
	newNode->item = item;

	if(list->count == 0){
		newNode->next = NULL;
		list->tail = newNode; // sets the tail node if the list is empty
	}else{
		newNode->next = list->head;
	}
	list->head = newNode; // points the head to the new node

	list->count++;
	return true;
}

int get_count(LinkedList* list) {
	return list->count;
}

void* get_item(LinkedList* list, int index) {
	if(index>=list->count) return NULL;
	LinkedListNode* cur = list->head;
	for (int i = 0; i < index; ++i){
		cur = cur->next;
	}
	return cur->item;
}


bool remove_item(LinkedList* list, void* item) {
	if (list == NULL || list->count == 0 || item == NULL) return false;

	LinkedListNode* prev = list->head;
	LinkedListNode* cur = prev;

	// checks if the first node contains the item
	if(cur->item == item) {
		list->head = cur->next;
		free(cur);
		return true;
	}

	cur = cur->next;
	while(cur != NULL) {
		if(cur->item == item) {
			if(prev == NULL || prev->next == NULL || cur == NULL || cur->next == NULL) return true;
			prev->next = cur->next;// this line breaks things
			free(cur);
			return true;
		}
		prev = cur;
		cur = cur->next;
	}
	return false;
}






struct LinkedListIterator {
	LinkedList* list;
	LinkedListNode* cur;
	int index;
};

bool end(LinkedListIterator* iterator){
	if(iterator->cur == NULL) return true;
	return false;
}

void* next(LinkedListIterator* iterator) {
	if(iterator->cur == NULL){
		iterator->cur = iterator->cur->next;
		iterator->index++;
		return iterator->cur->item;
	}
	return NULL;
}

LinkedListIterator* new_Iterator(LinkedList* list) {
	if(list == NULL) return NULL;
	LinkedListIterator* iterator_ptr = malloc(sizeof(LinkedListIterator));
	LinkedListIterator iterator ={
		list,
		list->head,
		0
	};
	*iterator_ptr = iterator;
	return iterator_ptr;
}


void free_Iterator(LinkedListIterator* iterator) {
	free(iterator);
}