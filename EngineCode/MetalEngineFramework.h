/*
This is the main core of the metal engine framework.
It will carry out information regarding how the
application is to be built on top of the engine and
information on how to implement new features and the like.
- John E2
*/
#ifndef METALENGINE
//also carries the version number.
#define METALENGINE 0
#include <stdio.h>
void printEngineDetails()
{
    printf("Engine version: %d", METALENGINE);
}

#endif