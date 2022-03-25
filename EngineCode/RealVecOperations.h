#ifndef REALVECOPERATIONS
#define REALVECOPERATIONS
#include "GenericStructs.h"

RealVec addRealVecs(RealVec a, RealVec b)
{
	return (RealVec){a.x + b.x, a.y + b.y, a.z + b.z};
}

RealVec multiplyRealVecs(RealVec a, RealVec b)
{
	return (RealVec){a.x * b.x, a.y * b.y, a.z * b.z};
}

RealVec subtractRealVecs(RealVec a, RealVec b)
{
	return (RealVec){a.x - b.x, a.y - b.y, a.z - b.z};
}

RealVec divideRealVecs(RealVec a, RealVec b)
{
	return (RealVec){a.x / b.x, a.y / b.y, a.z / b.z};
}

RealVec findMidPointRealVec(RealVec a, RealVec b)
{
	return (RealVec){(a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2};
}
#include <math.h>
float distanceBetweenRealVecs(RealVec a, RealVec b)
{
	return sqrt((pow(subtractRealVecs(a, b).x, 2)) + (pow(subtractRealVecs(a, b).y, 2)) + (pow(subtractRealVecs(a, b).z, 2)));
}
	// polys.sub_polygons[0] = lightPolygon(&polys.sub_polygons[0], &light);ooo
#endif