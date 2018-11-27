#ifndef component_h
#define component_h

typedef bool (*component_use_function)(Component*);
typedef bool (*component_passive_function)(Component*);

typedef struct Component
{
	Entity base;
	int powerUse;
	component_use_function use;
	component_passive_function passive;
}Component;

#endif//component_h