#include "generate.h"

#include "../collections/linkedlist.h"
#include "dungeon.h"
#include "square.h"
#include "../object/tile/tile.h"
#include <stdlib.h>
#define LEAFING_EDGE_PERCENT 0.25
#define MIN_ROOM_LENGTH 3
#define MAX_ROOM_LENGTH 16
#define MAX_LEAF_LENGTH MAX_ROOM_LENGTH+2
#define MIN_LEAF_LENGTH 12
typedef struct Box {
	int x;
	int y;
	int width;
	int height;
}Box;

Dungeon* generate(int level) {
	char tileMap[DUNGEON_HEIGHT][DUNGEON_WIDTH];

	// populates tileMap
	for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
		for (int x = 0; x < DUNGEON_WIDTH; ++x){
			tileMap[y][x] = '#';
		}
	}

	LinkedList* list = new_LinkedList();
	LinkedList* q = new_LinkedList();
	Box* init_ptr = malloc(sizeof(Box));
	Box init = {0,0,DUNGEON_WIDTH,DUNGEON_HEIGHT};
	*init_ptr = init;
	enqueue_item(q, init_ptr);
	int flipflop = rand()%2;
	// creates leaves
	while(get_count(q) != 0){
		Box* super = pop_item(q);

		if(super->width > MIN_LEAF_LENGTH && super->height > MIN_LEAF_LENGTH){
			if(flipflop) {
				// horizontal
				int widthLeft = super->width/4+rand()%(super->width/4);//+super->width/8;
				int widthRight = super->width-widthLeft;

				Box* subLeft = malloc(sizeof(Box));
				Box* subRight = malloc(sizeof(Box));
				Box lb = {super->x,	super->y, 	widthLeft,	super->height};
				Box rb = {super->x+widthLeft, 	super->y, 	widthRight,	super->height};
				*subLeft = lb;
				*subRight = rb;

				enqueue_item(q, subLeft);
				enqueue_item(q, subRight);
				flipflop = 0;
			}else{
				// vertical
				int heightUp = super->height/4+rand()%(super->height/4);//+super->height/8;
				int heightDown = super->height-heightUp;

				Box* subUp = malloc(sizeof(Box));
				Box* subDown = malloc(sizeof(Box));
				Box ub = {super->x,	super->y, 			super->width,	heightUp};
				Box db = {super->x, super->y+heightUp, 	super->width,	heightDown};
				*subUp = ub;
				*subDown = db;

				enqueue_item(q, subUp);
				enqueue_item(q, subDown);
				flipflop = 1;
			}
			free(super);
		}else if(super->width > MIN_LEAF_LENGTH){
			//horizontal
			int widthLeft = super->width/4+rand()%(super->width/4);//+super->width/8;
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
		}else if(super->height > MIN_LEAF_LENGTH){
			//vertical
			int heightUp = super->height/4+rand()%(super->height/4);//+super->height/8;
			int heightDown = super->height-heightUp;

			Box* subUp = malloc(sizeof(Box));
			Box* subDown = malloc(sizeof(Box));
			Box ub = {super->x,	super->y, 			super->width,	heightUp};
			Box db = {super->x, super->y+heightUp, 	super->width,	heightDown};
			*subUp = ub;
			*subDown = db;

			enqueue_item(q, subUp);
			enqueue_item(q, subDown);
			free(super);
		}else{
			push_item(list, super);
		}
	}
	free_LinkedList(q);


	int leafCount = get_count(list);
	// converts the leaves to rooms
	for (int i = 0; i < leafCount; ++i) {
		Box* leaf = pop_item(list);
		if(leaf->width < MIN_ROOM_LENGTH || leaf->height < MIN_ROOM_LENGTH){
			free(leaf);
			continue;
		}
		int newWidth = leaf->width;
		int newHeight = leaf->height;
		if(leaf->width > MIN_ROOM_LENGTH){
			newWidth = MIN_ROOM_LENGTH+rand()%(leaf->width-MIN_ROOM_LENGTH);
			leaf->x += rand()%(leaf->width-newWidth);
		}
		if(leaf->height > MIN_ROOM_LENGTH){
			newHeight = MIN_ROOM_LENGTH+rand()%(leaf->height-MIN_ROOM_LENGTH);
			leaf->y += rand()%(leaf->height-newHeight);
		}
		leaf->width = newWidth;
		leaf->height = newHeight;

		// puts rooms in char array
		for (int y = leaf->y; y < leaf->height+leaf->y; ++y) {
			for(int x = leaf->x; x < leaf->width+leaf->x; ++x) {
				tileMap[y][x] = '.';
			}
		}
		enqueue_item(list,leaf);
	}


	Box* room1 = pop_item(list);
	// finding where paths between rooms should be
	while(get_count(list) != 0){
		Box* room2 = pop_item(list);

		int center1x = room1->x+(room1->width/2);
		int center1y = room1->y+(room1->height/2);

		int center2x = room2->x+(room2->width/2);
		int center2y = room2->y+(room2->height/2);
		int diffx = center1x - center2x;
		int diffy = center1y - center2y;

		if(room1->y <= room2->y && room1->y+room1->height >= room2->y){
			// room2 is to the left or right of room1 and below room1 (+y)
			int range = room1->height+room1->y-room2->y;
			int pathy = room2->y;
			if(range != 0) pathy += rand()%range; // adds random modifier for path placement

			// places path in tileMap
			if(diffx > 0){
				for (int i = center2x; i <= center1x; ++i)
					tileMap[pathy][i] = '.';
			}else{
				for (int i = center1x; i <= center2x; ++i)
					tileMap[pathy][i] = '.';
			}
		}else if (room1->y >= room2->y && room2->y+room2->height >= room1->y){
			// room2 is to the left or right of room1 and above room1 (-y)
			int range = (room2->y+room2->height)-room1->y;
			int pathy = room1->y;
			if(range != 0) pathy += rand()%range;

			// places path in tileMap
			if(diffx > 0){
				for (int i = center2x; i <= center1x; ++i)
					tileMap[pathy][i] = '.';
			}else{
				for (int i = center1x; i <= center2x; ++i)
					tileMap[pathy][i] = '.';
			}
		}else if(room1->x <= room2->x && room1->x+room1->width >= room2->x){
			// room2 is up or down from room1 and to the right of room1 (+x)
			int range = room1->width+room1->x-room2->x;
			int pathx = room2->x;
			if(range != 0) pathx += rand()%range;
			// places path in tileMap
			if(diffy > 0){
				for (int i = center2y; i <= center1y; ++i)
					tileMap[i][pathx] = '.';
			}else{
				for (int i = center1y; i <= center2y; ++i)
					tileMap[i][pathx] = '.';
			}
		}else if(room1->x >= room2->x && room2->x+room2->width >= room1->x){
			// room2 is up or down from room1 and to the left of room1 (+y)
			int range = room2->width+room2->x-room1->x;
			int pathx = room1->x;
			if(range != 0) pathx += rand()%range;
			// places path in tileMap
			if(diffy > 0){
				for (int i = center2y; i <= center1y; ++i)
					tileMap[i][pathx] = '.';
			}else{
				for (int i = center1y; i <= center2y; ++i)
					tileMap[i][pathx] = '.';
			}
		}
		else{
			// room2 is diagnal from room 1 hek
			if(rand()%2) {
				// will place vertical first
				if(diffy > 0){
					for (int i = center2y; i <= center1y; ++i)
						tileMap[i][center1x] = '.';
				}else{
					for (int i = center1y; i <= center2y; ++i)
						tileMap[i][center1x] = '.';
				}

				if(diffx > 0){
					for (int i = center2x; i <= center1x; ++i)
						tileMap[center2y][i] = '.';
				}else{
					for (int i = center1x; i <= center2x; ++i)
						tileMap[center2y][i] = '.';
				}
			}else{
				//will place horizontal first
				if(diffx > 0){
					for (int i = center2x; i <= center1x; ++i)
						tileMap[center2y][i] = '.';
				}else{
					for (int i = center1x; i <= center2x; ++i)
						tileMap[center2y][i] = '.';
				}

				if(diffy > 0){
					for (int i = center2y; i <= center1y; ++i)
						tileMap[i][center1x] = '.';
				}else{
					for (int i = center1y; i <= center2y; ++i)
						tileMap[i][center1x] = '.';
				}

			}
		}
		room1 = room2;
	}
	free_LinkedList(list);



	// DUNGEON CREATION
	Dungeon* dungeon = malloc(sizeof(Dungeon));

	dungeon->level = level;
	for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
		for (int x = 0; x < DUNGEON_WIDTH; ++x) {

			Tile* tile = NULL;
			switch(tileMap[y][x]) {

				case'#': // wall
					tile = new_wall(x,y);
					break;
				case'.': // floor
				default:
					tile = new_floor(x,y);
					break;
			}

			/* MONSER SPAWN CODE
			if(rand()%){

			}*/
			Character* character = NULL;

			/* ITEM SPAWN CODE
			if(rand()%){

			}*/
			LinkedList* entities = new_LinkedList();

			Square square = {tile, entities, character};

			dungeon->squares[y][x] = square;
		}
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!ENTERENCE AND EXIT CODE!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	return dungeon;
}