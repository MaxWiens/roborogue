#ifndef component_h
#define component_h

#include "../../gameobject.h"
#include "../../../util/bool.h"
typedef struct Component
{
	GameObject base;
	int powerUse;
	int power;
	int armor;
	int procSpeed;
	int speed;
	bool (*use)(struct Component*);
	bool (*passive)(struct Component*);
}Component;

#endif//component_h