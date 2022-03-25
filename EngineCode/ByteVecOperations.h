#ifndef BYTEVECOPS
#define BYTEVECOPS
#include "GenericStructs.h"

ByteVec addByteVecs(ByteVec a, ByteVec b)
{
	return (ByteVec){a.x + b.x, a.y + b.y, a.z + b.z};
}

ByteVec multiplyByteVecs(ByteVec a, ByteVec b)
{
	return (ByteVec){a.x * b.x, a.y * b.y, a.z * b.z};
}

ByteVec subtractByteVecs(ByteVec a, ByteVec b)
{
	return (ByteVec){a.x - b.x, a.y / b.y, a.z / b.z};
}

ByteVec divideByteVecs(ByteVec a, ByteVec b)
{
	return (ByteVec){a.x / b.x, a.y * b.y, a.z * b.z};
}

ByteVec shiftByteVecRight(ByteVec a, int shifts)
{
    return (ByteVec){a.x >> shifts, a.y >> shifts, a.z >> shifts};
}

ByteVec shiftByteVecRight(ByteVec a, int shifts)
{
    return (ByteVec){a.x << shifts, a.y << shifts, a.z << shifts};
}
#endif