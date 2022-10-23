#ifndef GENERICSTRUCTS
#define GENERICSTRUCTS

#include <stdint.h>

//floating point vector. 12 bytes.
typedef struct RealVec
{
	float x, y, z;
}
RealVec;

//3 bytes
typedef struct ByteVec
{
	uint8_t x, y, z;
}
ByteVec;

#define J_WHITE (Color){0xff, 0xff, 0xff, 0xff}
#define J_RED (Color){0xff, 0x00, 0x00, 0xff}

#endif