#ifndef character_h
#define character_h

#include "../gameobject.h"
#include "../entity/component/component.h"
#include "../entity/component/cpu.h"
#include "../entity/component/powersupply.h"
#include "../entity/component/chassis.h"

typedef struct Character Character;

void evaluate_stats(Character* character);
#endif//character_h