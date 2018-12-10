#ifndef gameobject_h
#define gameobject_h

#include "types.h"

typedef struct GameObject
{
	Types type;
	char sprite;
	int x;
	int y;
	int hp;
	char* name;
	char* description;
}GameObject;

#endif//gameobject_h