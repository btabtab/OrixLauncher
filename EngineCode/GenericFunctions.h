#ifndef GENERIC_FUNCTIONS
#define GENERIC_FUNCTIONS
#include <stdint.h>
int isInRange(float num, float min, float max)
{
	return (min < num && num < max);
}

float limitRangeFloat(float num, float min, float max)
{
	if(isInRange(num, min, max))
	{
		return num;
	}
	if(num < min)
	{
		return min;
	}
	if(max < num)
	{
		return max;
	}
	return -0.f;
	// exit(0);
}
uint8_t limitRangeByte(uint8_t num, uint8_t min, uint8_t max)
{
	if(isInRange(num, min, max))
	{
		return num;
	}
	if(num < min)
	{
		return min;
	}
	if(max < num)
	{
		return max;
	}
	return num;
}

#endif