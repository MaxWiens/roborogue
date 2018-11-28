#ifndef component_h
#define component_h

#include "../entity.h"
#include "../../../util/bool.h"
typedef struct Component
{
	Entity base;
	int powerUse;
	bool (*use)(struct Component*);
	bool (*passive)(struct Component*);
}Component;

#endif//component_h