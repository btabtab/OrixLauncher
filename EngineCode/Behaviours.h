/*
Behaviours are going to be an easy way to handle functions that will control
certain aspects of the engine, such as behaviours relating to collision spaces,
entities and the like.
*/
#ifndef BEHAVIOURS
#define BEHAVIOURS

#include <stdint.h>
#include "KettleRenderer.h"
#include "GenericStructs.h"

typedef void (*BehaviourFunction)(void*);

typedef struct Behaviour
{
	int ID;
	BehaviourFunction func;
}
Behaviour;

Behaviour generateBehaviour(BehaviourFunction function)
{
	static int ID;
	Behaviour ret;
	ret.ID = ID;
	ID++;
	ret.func = function;
}

#endif