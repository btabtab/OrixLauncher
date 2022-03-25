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

typedef struct Colour
{
	uint8_t r, g, b, alpha_channel;
}
Colour;

#endif