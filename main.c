#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "VersionData.h"

#include "Demos.h"

void renderDots(float size)
{
	RealVec points[8] =
	{
		(RealVec){-size, -size, -size},
		(RealVec){+size, -size, -size},
		(RealVec){-size, -size, +size},
		(RealVec){+size, -size, +size},

		(RealVec){-size, +size, -size},
		(RealVec){+size, +size, -size},
		(RealVec){-size, +size, +size},
		(RealVec){+size, +size, +size},
	};

	for(int i = 0; i != 8; i++)
	{
		DrawSphere(*(Vector3*)&points[i], 0.5f, WHITE);
	}
}

void setPolyArrToCube(Polygon* p, float size)
{

	p[0] = testPolygon(size);
	p[1] = testPolygon(-size);

}

void cubeScene(Camera cam)
{
	Polygon p[6];
	setPolygonsToTestSquare(*getCubeSize(), p);

	// for(int i = 0; i != 3; i++)
	// {
	// 	p[1].verts[i].pnt = addRealVecs(p[1].verts[i].pnt, (RealVec){-6, 0, 0});
	// }

	// UpdateCamera(&cam);
	// SetCameraMode(cam, CAMERA_ORBITAL + ((IsKeyDown(KEY_R)) * 2));
	ClearBackground(BLACK);
	BeginMode3D(cam);
	{
		renderDots(*getCubeSize());
		// renderEnvironment(&environment);
		drawPolygonWireFrame(&p[0]);
		drawPolygonWireFrame(&p[1]);
		// renderPolygonSubSet(getTriSubPolygonSet(p));
		// renderPolygonWithLighting(&p[0], *getLight());
		PolygonCollection polys[2] = {getPolygonCollection(p[0]), getPolygonCollection(p[1])};
		renderPolygonCollection(&polys[0], *getLight());
		renderPolygonCollection(&polys[1], *getLight());
		// renderPolygonWithLighting_ADV_MODE(&p[1], *getLight());
		// renderPolygonSubSet(getTriSubPolygonSet(p));
		renderLight(getLight());
	}
	EndMode3D();
	DrawFPS(10, 10);
}

void cubeDemo()
{
	Camera cam;
	startup("Kettle renderer 2.0 Cube Demo", 800, 800, &cam);
	UIDrawToDemo(cam);
	SetCameraMode(cam, CAMERA_ORBITAL);

	int joystick_center_x = 200;
	int joystick_center_y = 400;

	UIElement element_arr[] =
	{
		generateUIElement(500, 300, 20, 20, newKettleString("A"), UI_CAMERA, NULL, J_WHITE),
		generateUIElement(90, 90, joystick_center_x, joystick_center_y, newKettleString("B"), UI_TOKEN, NULL, J_WHITE),
		generateUIElement(90, 90, joystick_center_x, joystick_center_y, newKettleString("C"), UI_TOKEN, NULL, J_WHITE),
		generateUIElement(90, 90, joystick_center_x, joystick_center_y, newKettleString("D"), UI_TOKEN, NULL, J_WHITE),
		generateUIElement(90, 90, joystick_center_x, joystick_center_y, newKettleString("E"), UI_TOKEN, NULL, J_WHITE),
		generateUIElement(90, 90, joystick_center_x, joystick_center_y, newKettleString("F"), UI_TOKEN, NULL, J_WHITE),
	};

	while(!WindowShouldClose())
	{

		checkMultipleElements(element_arr, sizeof(element_arr) / sizeof(*element_arr), getMainCursor());
		updateUIElements(element_arr, sizeof(element_arr) / sizeof(*element_arr), getMainCursor());
		updateMainCursor();

		draw3DWorldToUIElement(&element_arr[0], cam, cubeScene);

		grabUIElement(getMainCursor());

		getLight()->position.z = ((joystick_center_x - (element_arr[1].position.x)) / 100);
		getLight()->position.x = -((joystick_center_y - (element_arr[1].position.y)) / 100);

		getLight()->tinge.r = (limitRangeByte((joystick_center_y) - (element_arr[2].position.y), 0, 255));
		getLight()->tinge.g = (limitRangeByte((joystick_center_y) - (element_arr[3].position.y), 0, 255));
		getLight()->tinge.b = (limitRangeByte((joystick_center_y) - (element_arr[4].position.y), 0, 255));
		(*getCubeSize()) = ((element_arr[5].position.y) / 100);

		if(getMainCursor()->state != CURSOR_CLICK)
		{
			element_arr[1].position.x = joystick_center_x;
			element_arr[1].position.y = joystick_center_y;

			element_arr[2].position.x = joystick_center_x + 180;
			element_arr[3].position.x = joystick_center_x + 270;
			element_arr[4].position.x = joystick_center_x + 360;
			element_arr[5].position.x = joystick_center_x + 450;
			
		}

		BeginDrawing();
		{
			ClearBackground(WHITE);
			renderMultipleUIElements(element_arr, sizeof(element_arr) / sizeof(*element_arr));

			renderByte(getLight()->tinge.r, element_arr[2].position.x, element_arr[2].position.y, 20, (Colour){255, 255, 255, 255});
			renderByte(getLight()->tinge.g, element_arr[3].position.x, element_arr[3].position.y, 20, (Colour){255, 255, 255, 255});
			renderByte(getLight()->tinge.b, element_arr[4].position.x, element_arr[4].position.y, 20, (Colour){255, 255, 255, 255});
			renderFloat(*getCubeSize(), element_arr[5].position.x, element_arr[5].position.y, 20, (Colour){255, 255, 255, 255});
		}
		renderCursor(getMainCursor());
		DrawFPS(10, 10);
		EndDrawing();
	}
}
#include "PolygonDesigner.h"
int main()
{
	verifyVersion(0x0001);
	cubeDemo();
	return 0;
}
