#ifndef COLLISION
#define COLLISION

#include <stdint.h>
#include "KettleRenderer.h"
#include "GenericStructs.h"

typedef struct CollisionSpace
{
	//The function associated with this collisionspace.
	void* func_ptr;

	RealVec top_bound, bottom_bound;
	int ID;
}
CollisionSpace;

typedef void CollisionFunction;

typedef CollisionFunction (*CollisionFunctionPtr)(void*);

CollisionSpace generateCollisionSpace(RealVec top_bound, RealVec bottom_bound, CollisionFunctionPtr behaviour)
{
	static int next_ID = 0;
	CollisionSpace ret;
	ret.ID = next_ID;
	next_ID++;

	ret.func_ptr = behaviour;

	/*
	This will automatically sort and make
	sure that the top bound is actually higher than the bottom.
	*/
	if(top_bound.x < bottom_bound.x)
	{
		ret.top_bound.x = bottom_bound.x;
		ret.bottom_bound.x = top_bound.x;
	}
	else
	{
		ret.top_bound.x = top_bound.x;
		ret.bottom_bound.x = bottom_bound.x;
	}

	if(top_bound.y < bottom_bound.y)
	{
		ret.top_bound.y = bottom_bound.y;
		ret.bottom_bound.y = top_bound.y;
	}
	else
	{
		ret.top_bound.y = top_bound.y;
		ret.bottom_bound.y = bottom_bound.y;
	}

	if(top_bound.z < bottom_bound.z)
	{
		ret.top_bound.z = bottom_bound.z;
		ret.bottom_bound.z = top_bound.z;
	}
	else
	{
		ret.top_bound.z = top_bound.z;
		ret.bottom_bound.z = bottom_bound.z;
	}

	return ret;
}

void activateCollisionSpaceBehaviour(CollisionSpace* collision_space, void* data)
{
	((CollisionFunctionPtr)(collision_space->func_ptr))(data);
}

//X axis distance between points.
float getCollisionSpaceWidth(CollisionSpace collispace)
{
	return (collispace.top_bound.x - collispace.bottom_bound.x);
}
//Z axis distance between points.
float getCollisionSpaceDepth(CollisionSpace collispace)
{
	return (collispace.top_bound.z - collispace.bottom_bound.z);
}
//Y axis distance between points.
float getCollisionSpaceHeight(CollisionSpace collispace)
{
	return (collispace.top_bound.y - collispace.bottom_bound.y);
}

//draw the collisionspace for 3D rendering.
void renderCollisionSpace(CollisionSpace* collispace, Color a, Color b)
{
	renderSphere(collispace->top_bound, 0.25f, a);
	renderLine3D(collispace->top_bound, collispace->bottom_bound, averageColours(a, b));
	renderSphere(collispace->bottom_bound, 0.25f, b);

	RealVec draw_point = (RealVec){0, 0, 0};
	
	{
		draw_point.x = getCollisionSpaceWidth(*collispace);
		renderSphere(addRealVecs(collispace->bottom_bound, draw_point), 0.25f, b);
	}
	draw_point = (RealVec){0, 0, 0};
	{
		draw_point.y = getCollisionSpaceHeight(*collispace);
		renderSphere(addRealVecs(collispace->bottom_bound, draw_point), 0.25f, b);
	}
	draw_point = (RealVec){0, 0, 0};
	{
		draw_point.z = getCollisionSpaceDepth(*collispace);
		renderSphere(addRealVecs(collispace->bottom_bound, draw_point), 0.25f, b);
	}

	draw_point = (RealVec){0, 0, 0};
	{
		draw_point.x = -getCollisionSpaceDepth(*collispace);
		renderSphere(addRealVecs(collispace->top_bound, draw_point), 0.25f, b);
	}
	draw_point = (RealVec){0, 0, 0};
	{
		draw_point.y = -getCollisionSpaceHeight(*collispace);
		renderSphere(addRealVecs(collispace->top_bound, draw_point), 0.25f, b);
	}
	draw_point = (RealVec){0, 0, 0};
	{
		draw_point.z = -getCollisionSpaceDepth(*collispace);
		renderSphere(addRealVecs(collispace->top_bound, draw_point), 0.25f, b);
	}
}
//draw the collisionspace for 2D drawing.
void drawCollisionSpace(CollisionSpace* collispace, Color a, Color b)
{
}

#endif