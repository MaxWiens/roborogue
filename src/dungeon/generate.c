#include "generate.h"

#include "../collections/linkedlist.h"
#include "../collections/tuple.h"
#include <stdlib.h>
#define LEAFING_EDGE_PERCENT 0.25
#define MAX_ROOM_LENGTH 16
#define MAX_LEAF_LENGTH MAX_ROOM_LENGTH+2
typedef struct Box {
	int x;
	int y;
	int width;
	int height;
}Box;

void leafing_algorithm(char tileMap[DUNGEON_HEIGHT][DUNGEON_WIDTH]) {

	// populates tileMap
	for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
		for (int x = 0; x < DUNGEON_WIDTH; ++x){
			tileMap[y][x] = '#';
		}
	}

	LinkedList* list = new_LinkedList();
	LinkedList* q = new_LinkedList();
	Box* init = malloc(sizeof(Box));
	Box b = {0,0,DUNGEON_WIDTH,DUNGEON_HEIGHT};
	*init = b;
	enqueue_item(q, init);

	// creates leaves
	while(get_count(q) != 0){
		Box* super = pop_item(q);

		int s = rand();

		if(super->width > MAX_LEAF_LENGTH && super->height > MAX_LEAF_LENGTH){
			if(s%2 == 1) {
				// horizontal
				int widthLeft = s%((int)(super->width*LEAFING_EDGE_PERCENT))+super->width*(LEAFING_EDGE_PERCENT*0.5);
				int widthRight = super->width-widthLeft;

				Box* subLeft = malloc(sizeof(Box));
				Box* subRight = malloc(sizeof(Box));
				Box lb = {super->x,				super->y, 	widthLeft,	super->height};
				Box rb = {super->x+widthLeft, 	super->y, 	widthRight,	super->height};
				*subLeft = 	lb;
				*subRight = rb;

				enqueue_item(q, subLeft);
				enqueue_item(q, subRight);
			}else{
				// vertical
				int heightUp = s%((int)(super->height*0.25))+super->height*(LEAFING_EDGE_PERCENT*0.5);
				int heightDown = super->height-heightUp;

				Box* subUp = malloc(sizeof(Box));
				Box* subDown = malloc(sizeof(Box));
				Box ub = {super->x,	super->y, 			super->width,	heightUp};
				Box db = {super->x, 	super->y+heightUp, 	super->width,	heightDown};
				*subUp = ub;
				*subDown = ub;

				enqueue_item(q, subUp);
				enqueue_item(q, subDown);
			}
			free(super);
		}else if(super->width > MAX_ROOM_LENGTH){
			//horizontal
			int widthLeft = s%((int)(super->width*LEAFING_EDGE_PERCENT))+super->width*(LEAFING_EDGE_PERCENT*0.5);
			int widthRight = super->width-widthLeft;

			Box* subLeft = malloc(sizeof(Box));
			Box* subRight = malloc(sizeof(Box));
			Box lb = {super->x,	super->y, 	widthLeft,	super->height};
			Box rb = {super->x+widthLeft, 	super->y, 	widthRight,	super->height};
			*subLeft = lb;
			*subRight = rb;

			enqueue_item(q, subLeft);
			enqueue_item(q, subRight);
			free(super);
		}else if(super->height > MAX_ROOM_LENGTH){
			//vertical
			int heightUp = s%((int)(super->height*0.25))+super->height*(LEAFING_EDGE_PERCENT*0.5);
			int heightDown = super->height-heightUp;

			Box* subUp = malloc(sizeof(Box));
			Box* subDown = malloc(sizeof(Box));
			Box ub = {super->x,	super->y, 			super->width,	heightUp};
			Box rb = {super->x, super->y+heightUp, 	super->width,	heightDown};
			*subUp = ub;
			*subDown = rb;

			enqueue_item(q, subUp);
			enqueue_item(q, subDown);
			free(super);
		}else{
			push_item(list, super);
		}
	}

	int leafCount = get_count(list);
	// converts the leaves to rooms
	for (int i = 0; i < leafCount; ++i) {
		Box* leaf = pop_item(list);
		int newWidth = rand()%leaf->width;
		int newHeight = rand()%leaf->height;
		leaf->x += rand()%(leaf->width-newWidth);
		leaf->y += rand()%(leaf->height-newHeight);
		leaf->width = newWidth;
		leaf->height = newHeight;
		for (int y = leaf->y; y < leaf->height+leaf->y; ++y) {
			for(int x = leaf->x; x < leaf->width+leaf->x; ++x) {
				tileMap[y][x] = '.';
			}
		}
		enqueue_item(list,leaf);
	}

	// puts rooms in char array
	/*LinkedListIterator* iter = new_Iterator(list);
	while(!end(iter)) {
		Box* box = next(iter);
		for (int y = box->y; y < box->height+box->y; ++y) {
			for(int x = box->x; x < box->width+box->x; ++x) {
				tileMap[y][x] = '.';
			}
		}
	}
	free_Iterator(iter);*/

	/*
	Box* room1 = pop_item(list);
	// finding where paths between rooms should be
	while(get_count(list) != 0){
		Box* room2 = pop_item(list);

		int center1x = room1->x+room1->width*0.5;
		int center1y = room1->y+room1->height*0.5;

		int center2x = room2->x+room2->width*0.5;
		int center2y = room2->y+room2->height*0.5;
		int diffx = center1x - center2x;
		int diffy = center1y - center2y;

		if(room1->y <= room2->y && room1->y+room1->height >= room2->y){
			// room2 is to the left or right of room1 and below room1 (+y)
			int pathy = rand()%(room2->y-(room1->y+room1->height));

			// places path in tileMap
			for (int i = center1x; i < center1x+diffx; ++i)
				tileMap[pathy][i] = '.';
		}else if (room1->y >= room2->y && room2->y+room2->height >= room1->y){
			// room2 is to the left or right of room1 and above room1 (-y)
			int pathy = rand()%((room2->y+room2->height)-room1->y);
			// places path in tileMap
			for (int i = center1x; i < center1x+diffx; ++i)
				tileMap[pathy][i] = '.';
		}else if(room1->x <= room2->x && room1->x+room1->width >= room2->x){
			// room2 is up or down from room1 and to the right of room1 (+x)
			int pathx = rand()%(room1->x+room1->width-room2->x);
			// places path in tileMap
			for (int i = center1y; i < center1y+diffy; ++i)
				tileMap[i][pathx] = '.';
		}else if(room1->x >= room2->x && room2->x+room2->width >= room1->x){
			// room2 is up or down from room1 and to the left of room1 (+y)
			int pathx = rand()%(room2->x+room2->width-room1->x);
			// places path in tileMap
			for (int i = center1y; i < center1y+diffy; ++i)
				tileMap[i][pathx] = '.';
		}
		else{
			// room2 is diagnal from room 1 hek
			if(rand()%2) {
				// will place vertical first
				for (int i = center1y; i < center1y+diffy; ++i)
					tileMap[i][center1y];
				for (int i = center1y; i < center1y+diffy; ++i)
					tileMap[center2y][i];
			}else{
				//will place horizontal first
				for (int i = center1y; i < center1y+diffy; ++i)
					tileMap[center2y][i];
				for (int i = center1y; i < center1y+diffy; ++i)
					tileMap[i][center1y];
			}
		}
		room1 = room2;
	}
	*/
	free_LinkedList(q);
	free_LinkedList(list);

}