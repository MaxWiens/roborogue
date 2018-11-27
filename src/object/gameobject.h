#ifndef gameobject_h
#define gameobject_h

#include "types.h"
#include "../math/vector.h"

typedef struct GameObject
{
	Types type;
	char sprite;
	Vector* position;
	int hp;
	char* name;
	char* description;
}GameObject;

#endif//gameobject_h