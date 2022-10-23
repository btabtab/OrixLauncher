/*
Alternative names include:
PolyX renderer.

This is the main 3D renderer behind the engine. It sits on top of raylib
and handles many bits of functionality such as:
Vertex lighting (Currently complete),
Reflections (Not added yet),
Water Surfaces (Not added yet),
Shadows.
*/
#ifndef RENDERING
#define RENDERING

#include <stdlib.h>
#include <stdio.h>
#include "GenericStructs.h"
#include "RealVecOperations.h"
#include "../RaylibHandling.h"

#ifndef RENDERING_STRUCTS
#define RENDERING_STRUCTS

typedef struct Vertices
{
	//point
	RealVec pnt;
}
Vertices;

typedef struct Polygon
{
	Vertices verts[3];
	Color col;
	int ID;
}
Polygon;

uint64_t getNewPolygonID()
{
	static uint64_t ID = 0;
	return ID++;
}

typedef struct PolygonSubSet
{
	Polygon sub_polygons[4];
}
PolygonSubSet;

typedef struct Light
{
	RealVec position;
	float strength;
	Color tinge;
}
Light;

typedef struct PolygonCollection
{
	Polygon polygons[16];
}
PolygonCollection;

typedef struct Environment
{
	int polygon_count;
	Polygon* polygons;
}
Environment;

#endif
/*
These function declarations will be used for the sake of
helping with porting to other libraries and platforms,
this will be a massive help for when I decide to port
the kettle renderer to the arduino to help with any future
arduino projects I have.
*/
#ifndef KETTLE_RENDERER_FUNC_DEFINITIONS
#define KETTLE_RENDERER_FUNC_DEFINITIONS
//Renders a line that goes from point A to point B.
void renderLine3D(RealVec a, RealVec b, Color col);

//Renders a ball / sphere in 3D space at point "a" and with a radius of "radius".
void renderSphere(RealVec a, float radius, Color col);
#endif
/*
This is to help meet the end goal of replacing Raylib.
This section of functions will help to start the
gap of implementing my own functions to overwrite
the RAYLIB functions.

They will all be defined at the top of this file
as templates that can be redefined using other
#ifndef and #ifdef directives so that it can ease porting with
other libraries and platforms
*/
#ifndef RAYLIB_OVERRIDES
#define RAYLIB_OVERRIDES

void renderLine3D(RealVec a, RealVec b, Color col)
{
	DrawLine3D(*((Vector3*)&a), *((Vector3*)&b), *((Color*)&col));
}

void renderSphere(RealVec a, float radius, Color col)
{
	DrawSphere(*((Vector3*)&a), radius, *((Color*)&col));
}

#endif
#ifndef SCREEN_PRINTING
#define SCREEN_PRINTING

void renderFloat(float num, int x, int y, int size, Color col)
{
	char buffer[30];
	sprintf(buffer, "%f", num);
	DrawText(buffer, x, y, size, *((Color*)(&col)));
}

void renderByte(uint8_t num, int x, int y, int size, Color col)
{
	char buffer[30];
	sprintf(buffer, "%u", num);
	DrawText(buffer, x, y, size, *((Color*)(&col)));
}

#endif
#ifndef KETTLE_GET_FUNCTIONS
#define KETTLE_GET_FUNCTIONS
float* getCubeSize()
{
	static float cube_size;
	return &cube_size;
}

Light testLight()
{
	return (Light){(RealVec){0, 1, 0}, 1, (Color){0, 0, 0, 255}};
}

float getPercent(float num, float percent)
{
	return (num / 100) * percent;
}
#endif
#ifndef KETTLE_OPERATIONS
#define KETTLE_OPERATIONS

Color averageColours(Color a, Color b)
{
	Color ret = {0, 0, 0, 0};
	ret.r = (a.r + b.r) / 2;
	ret.g = (a.g + b.g) / 2;
	ret.b = (a.b + b.b) / 2;
	return ret;
}

Polygon operateOnPolygonAddition(Polygon p, RealVec operation_value);
Polygon operateOnPolygonSubtraction(Polygon p, RealVec operation_value);
Polygon operateOnPolygonMultiplications(Polygon p, RealVec operation_value);
Polygon operateOnPolygonDivision(Polygon p, RealVec operation_value);
RealVec findMiddleOfPolygon(Polygon p);
Polygon lightPolygon(Polygon* p, Light* light);

Polygon testPolygon(float size)
{
	Polygon poly;
	poly.ID = getNewPolygonID();
	poly.verts[0].pnt = (RealVec){-0.f, -0.f, -size};
	poly.verts[1].pnt = (RealVec){-0.f, -0.f, +size};
	poly.verts[2].pnt = (RealVec){+size, -0.f, -0.f};
	
	poly.col = (Color){255, 255, 255, 255};
	poly.col = (Color){255, 255, 255, 255};
	poly.col = (Color){255, 255, 255, 255};
	return poly;
}
void setPolygonsToTestSquare(float size, Polygon* polygons)
{
	polygons[0].verts[0].pnt = (RealVec){+size, 0, +size};
	polygons[0].verts[1].pnt = (RealVec){+size, 0, -size};
	polygons[0].verts[2].pnt = (RealVec){-size, 0, -size};

	polygons[1].verts[0].pnt = (RealVec){-size, 0, +size};
	polygons[1].verts[1].pnt = (RealVec){+size, 0, +size};
	polygons[1].verts[2].pnt = (RealVec){-size, 0, -size};

	polygons[0] = testPolygon(*(getCubeSize()));
	polygons[1] = operateOnPolygonAddition(polygons[0], (RealVec){0, (-*getCubeSize()) * 2, 0});
}
Polygon invertPolygon(Polygon p)
{
	RealVec inversion = (RealVec){-1, -1, -1};

	multiplyRealVecs(p.verts[0].pnt, inversion);
	multiplyRealVecs(p.verts[1].pnt, inversion);
	multiplyRealVecs(p.verts[2].pnt, inversion);
	return p;
}
Color averagePolygonColour(Polygon p)
{
	Color ret;
	ret.r = (p.col.r + p.col.r + p.col.r) / 3;
	ret.g = (p.col.g + p.col.g + p.col.g) / 3;
	ret.b = (p.col.b + p.col.b + p.col.b) / 3;
	ret.a = (p.col.a + p.col.a + p.col.a) / 3;
	return ret;
}
PolygonSubSet getQuadSubPolyGonSet(Polygon p);
#endif
#ifndef RENDERING_FUNCTIONS
#define RENDERING_FUNCTIONS
void drawPolygonWireFrame(Polygon* poly)
{
}
void renderPolygon(Polygon* p)
{
	Color avg = averagePolygonColour(*p);
	RealVec points[3] = {p->verts[0].pnt, p->verts[1].pnt, p->verts[2].pnt};
	DrawTriangleStrip3D(((Vector3*)points), 3, *((Color*)&avg));

	if(IsKeyDown(KEY_P))
	{
		RealVec new_pts[3];
		for(int i = 0; i != 3; i++)
		{
			new_pts[i] = points[2 - i];
		}
		{
			DrawTriangleStrip3D(((Vector3*)new_pts), 3, *((Color*)&avg));
		}
	}

}
void renderPolygonWithLighting(Polygon* p, Light light)
{
	PolygonSubSet polygon_subset = getQuadSubPolyGonSet(*p);
	polygon_subset.sub_polygons[0] = lightPolygon(&polygon_subset.sub_polygons[0], &light);
	polygon_subset.sub_polygons[1] = lightPolygon(&polygon_subset.sub_polygons[1], &light);
	polygon_subset.sub_polygons[2] = lightPolygon(&polygon_subset.sub_polygons[2], &light);
	polygon_subset.sub_polygons[3] = lightPolygon(&polygon_subset.sub_polygons[3], &light);
	renderPolygon(&polygon_subset.sub_polygons[0]);
	renderPolygon(&polygon_subset.sub_polygons[1]);
	renderPolygon(&polygon_subset.sub_polygons[2]);
	renderPolygon(&polygon_subset.sub_polygons[3]);
}
void renderPolygonCollection(PolygonCollection* polys, Light light)
{
	for(int i = 0; i != 16; i++)
	{
		renderPolygonWithLighting(&polys->polygons[i], light);
	}
}
void renderPolygonSubSetWithLighting(PolygonSubSet ps, Light light)
{
	for(int i = 0; i != 3; i++)
	{
		if(!IsKeyDown(KEY_SPACE))
		{
			renderPolygonWithLighting(&ps.sub_polygons[i], light);
		}
		else
		{
			drawPolygonWireFrame(&ps.sub_polygons[i]);
		}
	}
}

void renderBillboardWithLighting(Camera3D cam, Texture texture, RealVec pos, float size, Light light)
{
	uint8_t distance = distanceBetweenRealVecs((RealVec){pos.x, pos.y, pos.z}, light.position);

	Color col = RAYWHITE;

	col.r += (255 - light.tinge.r) / (sqrt(distance));
	col.g += (255 - light.tinge.g) / (sqrt(distance));
	col.b += (255 - light.tinge.b) / (sqrt(distance));

	pos.y = 0.1 + (texture.height / 40);// + (texture.height / 2);
	// DrawLine3D(pos, (Vector3){0, 0, 0}, WHITE);
	DrawBillboard(cam, texture, *((Vector3*)&pos), size, col);
}

#endif
#ifndef POLYGON_SUBSET_FUNCTIONS
#define POLYGON_SUBSET_FUNCTIONS
PolygonSubSet getSubPolygonSetOld(Polygon p)
{
	PolygonSubSet ret;
	ret.sub_polygons[0] = p;
	ret.sub_polygons[1] = p;
	ret.sub_polygons[2] = p;

	ret.sub_polygons[0].verts[0].pnt = findMiddleOfPolygon(p);
	ret.sub_polygons[1].verts[1].pnt = findMiddleOfPolygon(p);
	ret.sub_polygons[2].verts[2].pnt = findMiddleOfPolygon(p);

	// updateColourToNext(&ret.sub_polygons[0].col, 1);
	// updateColourToNext(&ret.sub_polygons[1].col, 2);
	// updateColourToNext(&ret.sub_polygons[2].col, 3);

	return ret;
}
PolygonSubSet getQuadSubPolyGonSet(Polygon p)
{
	PolygonSubSet ret = { 0 };

	RealVec outer_points[3];
	RealVec midpoints[3];

	for(int i = 0; i != 3; i++)
	{
		outer_points[i] = p.verts[i].pnt;
	}

	midpoints[0] = findMidPointRealVec(outer_points[0], outer_points[1]);
	midpoints[1] = findMidPointRealVec(outer_points[1], outer_points[2]);
	midpoints[2] = findMidPointRealVec(outer_points[2], outer_points[0]);

	// DrawSphere(*(Vector3*)&midpoints[0], 1, RED);
	// DrawSphere(*(Vector3*)&midpoints[1], 1, RED);
	// DrawSphere(*(Vector3*)&midpoints[2], 1, RED);

	ret.sub_polygons[0] = (Polygon)
	{
		(Vertices){midpoints[0]},
		(Vertices){midpoints[1]},
		(Vertices){midpoints[2]},
		p.col
	};

	ret.sub_polygons[1] = (Polygon)
	{
		(Vertices){midpoints[0]},
		(Vertices){midpoints[2]},
		(Vertices){p.verts[0].pnt},
		p.col
	};

	ret.sub_polygons[2] = (Polygon)
	{
		(Vertices){midpoints[1]},
		(Vertices){midpoints[0]},
		(Vertices){p.verts[1].pnt},
		p.col
	};

	ret.sub_polygons[3] = (Polygon)
	{
		(Vertices){midpoints[2]},
		(Vertices){midpoints[1]},
		(Vertices){p.verts[2].pnt},
		p.col
	};

	return ret;

}
PolygonCollection getPolygonCollection(Polygon p)
{
	PolygonCollection ret;
	PolygonSubSet base = getQuadSubPolyGonSet(p);
	// PolygonSubSet top = getQuadSubPolyGonSet(base.sub_polygons[0]);
	// PolygonSubSet center = getQuadSubPolyGonSet(base.sub_polygons[1]);
	// PolygonSubSet left = getQuadSubPolyGonSet(base.sub_polygons[2]);
	// PolygonSubSet right = getQuadSubPolyGonSet(base.sub_polygons[3]);

	PolygonSubSet compiled_polys[4] =
	{
		getQuadSubPolyGonSet(base.sub_polygons[0]),
		getQuadSubPolyGonSet(base.sub_polygons[1]),
		getQuadSubPolyGonSet(base.sub_polygons[2]),
		getQuadSubPolyGonSet(base.sub_polygons[3]),
	};

	for(int i = 0; i != 4; i++)
	{
		for(int o = 0; o != 4; o++)
		{
			ret.polygons[(i * 4) + o] = compiled_polys[i].sub_polygons[o];
		}
	}

	return ret;
}
PolygonSubSet getTriSubPolygonSet(Polygon p)
{
	PolygonSubSet ret;
	ret.sub_polygons[0] = p;
	ret.sub_polygons[1] = p;
	ret.sub_polygons[2] = p;

	ret.sub_polygons[0].verts[0].pnt = findMiddleOfPolygon(p);
	ret.sub_polygons[1].verts[1].pnt = findMiddleOfPolygon(p);
	ret.sub_polygons[2].verts[2].pnt = findMiddleOfPolygon(p);

	return ret;
}
void renderLight(Light* light)
{
	DrawSphere(*(Vector3*)(&light->position), .25, *(Color*)&light->tinge);
}
#endif
#ifndef POLYGON_OPERATIONS
#define POLYGON_OPERATIONS

RealVec findMiddleOfPolygon(Polygon p)
{
	return (RealVec){
		(p.verts[0].pnt.x + p.verts[1].pnt.x + p.verts[2].pnt.x) / 3,
		(p.verts[0].pnt.y + p.verts[1].pnt.y + p.verts[2].pnt.y) / 3,
		(p.verts[0].pnt.z + p.verts[1].pnt.z + p.verts[2].pnt.z) / 3,
		};
}
Polygon operateOnPolygonAddition(Polygon p, RealVec operation_value)
{
	for(int i = 0; i != 3; i++)
	{
		p.verts[i].pnt = addRealVecs(p.verts[i].pnt, operation_value);
	}
	return p;
}
Polygon operateOnPolygonSubtraction(Polygon p, RealVec operation_value)
{
	for(int i = 0; i != 3; i++)
	{
		p.verts[i].pnt = subtractRealVecs(p.verts[i].pnt, operation_value);
	}
	return p;
}
Polygon operateOnPolygonMultiplications(Polygon p, RealVec operation_value)
{
	for(int i = 0; i != 3; i++)
	{
		p.verts[i].pnt = multiplyRealVecs(p.verts[i].pnt, operation_value);
	}
	return p;
}
Polygon operateOnPolygonDivision(Polygon p, RealVec operation_value)
{
	for(int i = 0; i != 3; i++)
	{
		p.verts[i].pnt = divideRealVecs(p.verts[i].pnt, operation_value);
	}
	return p;
}
Polygon lightPolygon(Polygon* p, Light* light)
{
	Polygon result = *p;

	uint8_t distance = distanceBetweenRealVecs(findMiddleOfPolygon(result), light->position);

	// for(int i = 0; i != 3; i++)
	{
		result.col.r += (255 - light->tinge.r) / (sqrt(distance));
		result.col.g += (255 - light->tinge.g) / (sqrt(distance));
		result.col.b += (255 - light->tinge.b) / (sqrt(distance));
	}

	return result;
}

#endif

#endif