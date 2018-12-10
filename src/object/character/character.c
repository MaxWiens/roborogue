#include "character.h"
#include "../types.h"
#include "../gameobject.h"
#include "../../dungeon/dungeon.h"
#include <stdlib.h>


struct Character
{
	GameObject base;
	int power;
	int maxPower;
	int speed;
	int procSpeed;
	int armor;
	Dungeon* dungeon;
	Component* cpu;
	Component* chassis;
	Component* powerSupply;
	Component* comp1;
	Component* comp2;
	Component* comp3;
	Component* comp4;
	Component* comp5;
};

void update(Character* character){

	if(character->cpu->passive != NULL)
		character->cpu->passive(character->cpu);
	if(character->chassis->passive != NULL)
		character->chassis->passive(character->chassis);
	if(character->powerSupply->passive != NULL)
		character->powerSupply->passive(character->powerSupply);

	if(character->comp1 != NULL && character->comp1->passive != NULL)
		character->comp1->passive(character->comp1);
	if(character->comp2 != NULL && character->comp1->passive != NULL)
		character->comp2->passive(character->comp2);
	if(character->comp3 != NULL && character->comp1->passive != NULL)
		character->comp3->passive(character->comp3);
	if(character->comp4 != NULL && character->comp1->passive != NULL)
		character->comp4->passive(character->comp4);
	if(character->comp5 != NULL && character->comp1->passive != NULL)
		character->comp5->passive(character->comp5);
}

void evaluate_stats(Character* character){
	int maxHP = 0;
	int hp = 0;
	int powerUse = 0;
	int maxPower = 0;
	int speed = 0;
	int procSpeed = 0;
	int armor = 0;

	maxHP += ((GameObject*)character->cpu)->maxHP;
	powerUse += character->cpu->powerUse;
	maxPower += character->cpu->power;
	armor += character->cpu->armor;
	procSpeed += character->cpu->procSpeed;
	speed += character->cpu->speed;

	maxHP += ((GameObject*)character->chassis)->maxHP;
	powerUse += character->chassis->powerUse;
	maxPower += character->chassis->power;
	armor += character->chassis->armor;
	procSpeed += character->chassis->procSpeed;
	speed += character->chassis->speed;

	maxHP += ((GameObject*)character->powerSupply)->maxHP;
	powerUse += character->powerSupply->powerUse;
	maxPower += character->powerSupply->power;
	armor += character->powerSupply->armor;
	procSpeed += character->powerSupply->procSpeed;
	speed += character->powerSupply->speed;

	if(character->comp1 != NULL){
		powerUse += character->comp1->powerUse;
		maxPower += character->comp1->power;
		armor += character->comp1->armor;
		procSpeed += character->comp1->procSpeed;
		speed += character->comp1->speed;
	}
	if(character->comp2 != NULL){
		powerUse += character->comp2->powerUse;
		maxPower += character->comp2->power;
		armor += character->comp2->armor;
		procSpeed += character->comp2->procSpeed;
		speed += character->comp2->speed;
	}
	if(character->comp3 != NULL){
		powerUse += character->comp3->powerUse;
		maxPower += character->comp3->power;
		armor += character->comp3->armor;
		procSpeed += character->comp3->procSpeed;
		speed += character->comp3->speed;
	}
	if(character->comp4 != NULL){
		powerUse += character->comp4->powerUse;
		maxPower += character->comp4->power;
		armor += character->comp4->armor;
		procSpeed += character->comp4->procSpeed;
		speed += character->comp4->speed;
	}
	if(character->comp5 != NULL){
		powerUse += character->comp5->powerUse;
		maxPower += character->comp5->power;
		armor += character->comp5->armor;
		procSpeed += character->comp5->procSpeed;
		speed += character->comp5->speed;
	}

	character->base.maxHP = maxHP;
	character->power = maxPower - powerUse;
	character->maxPower = maxPower;
	character->speed = speed;
	character->procSpeed = procSpeed;
	character->armor = armor;
}