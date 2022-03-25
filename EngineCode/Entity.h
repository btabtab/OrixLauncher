#ifndef ENTITY_H
#define ENTITY_H

#include "GenericStructs.h"
#include "GenericFunctions.h"
#include "KettleRenderer.h"
#include "Saving.h"

typedef struct Entity
{
	Texture* texture;
	RealVec position;
	RealVec move_direction;
	void* data;
}
Entity;

Entity initEntity()
{
	Entity ret;
	ret.data = NULL;
	ret.move_direction = (RealVec){0, 0, 0};
	ret.position = (RealVec){0, 0, 0};
	ret.texture = NULL;
	return ret;
}

void renderEntity(Entity* ent, Camera cam, Light light)
{
	if(!ent->texture)
	{
		char errorDump[] = "No texture for entity.";
		saveData(errorDump, sizeof(errorDump), "ENTITYERROR");
		exit(0);
	}
	renderBillboardWithLighting(cam, *ent->texture, ent->position, 1, light);
	// DrawBillboard(cam, *ent->texture, ent->position, 1, RAYWHITE);
	renderLine3D(ent->position, addRealVecs(ent->position, ent->move_direction), (Colour){255, 0, 255});
	RealVec pos = addRealVecs(ent->position, ent->move_direction);
	DrawSphere(*((Vector3*)(&pos)), .25f, RED);
}

#endif