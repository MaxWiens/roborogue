#ifndef character_h
#define character_h

#include "../gameobject.h"
#include "../entity/component/component.h"
#include "../entity/component/cpu.h"
#include "../entity/component/powersupply.h"
#include "../entity/component/chassis.h"

typedef struct Character
{
	GameObject base;
	CPU* cpu;
	Chassis* chassis;
	PowerSupply* powerSupply;
	Component* comp1;
	Component* comp2;
	Component* comp3;
	Component* comp4;
	Component* comp5;

}Character;
#endif//character_h