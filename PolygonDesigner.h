#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "Demos.h"
#include "EngineCode/VertexLightingEngine.h"

#ifndef POLYGON_DESIGNER_TOOL
#define POLYGON_DESIGNER_TOOL

Polygon* getPolygonDesignerToolPolygon()
{
	static Polygon p = { 0 };
	return &p;
}

int* getSelectedPolygonVertices()
{
	static int selected_poly = 0;
	if(2 < selected_poly)
	{
		selected_poly = 0;
	}
	return &selected_poly;
}

void polygonDesignerTool3DScene(Camera cam)
{
	ClearBackground(BLACK);
	BeginMode3D(cam);
	{		
		drawPolygonWireFrame(getPolygonDesignerToolPolygon());
		PolygonCollection polys = getPolygonCollection(*getPolygonDesignerToolPolygon());
		renderPolygonCollection(&polys, *getLight());
		renderLight(getLight());
		DrawSphere(*((Vector3*)(&getPolygonDesignerToolPolygon()->verts[*getSelectedPolygonVertices()].pnt)), .25f, RED);
	}
	EndMode3D();
	DrawFPS(10, 10);
}

void polygonDesignerTool()
{
	Camera cam;
	startup("Polygone DesignerTool", 800, 800, &cam);
	UIDrawToDemo(cam);
	SetCameraMode(cam, CAMERA_ORBITAL);

	int joystick_center_x = 200;
	int joystick_center_y = 400;

	int joystick_pos_x = 200;
	int joystick_pos_y = 400;

	(*getPolygonDesignerToolPolygon()) = testPolygon(3.f);

	UIElement element_arr[] =
	{
		generateUIElement(500, 300, 20, 20, newKettleString("A"), UI_CAMERA, NULL, J_RED),
		generateUIElement(90, 90, joystick_center_x, joystick_center_y, newKettleString("B"), UI_TOKEN, NULL, J_RED),
		generateUIElement(90, 90, joystick_center_x, joystick_center_y, newKettleString("C"), UI_BUTTON, NULL, J_RED),
		generateUIElement(90, 90, joystick_center_x, joystick_center_y, newKettleString("D"), UI_BUTTON, NULL, J_RED),
		generateUIElement(90, 90, joystick_center_x, joystick_center_y, newKettleString("E"), UI_BUTTON, NULL, J_RED),
		generateUIElement(90, 90, joystick_center_x, joystick_center_y + 90, newKettleString("F"), UI_BUTTON, NULL, J_RED),
	};

	while(!WindowShouldClose())
	{

		checkMultipleElements(element_arr, sizeof(element_arr) / sizeof(*element_arr), getMainCursor());
		updateUIElements(element_arr, sizeof(element_arr) / sizeof(*element_arr), getMainCursor());
		updateMainCursor();

		draw3DWorldToUIElement(&element_arr[0], cam, polygonDesignerTool3DScene);

		grabUIElement(getMainCursor());

		getLight()->tinge.r = (limitRangeByte((joystick_center_y) - (element_arr[2].position.y), 0, 255));
		getLight()->tinge.g = (limitRangeByte((joystick_center_y) - (element_arr[3].position.y), 0, 255));
		getLight()->tinge.b = (limitRangeByte((joystick_center_y) - (element_arr[4].position.y), 0, 255));

		// if(getMainCursor()->selected_element)
		{
			if(IsKeyPressed(KEY_O))
			{
				(*getSelectedPolygonVertices())++;
			}

			if(IsKeyPressed(KEY_S))
			{
				// saveData(getPolygonDesignerToolPolygon(), sizeof(Polygon), "Poly.plygn");
			}

			if(IsKeyPressed(KEY_L))
			{
				// loadData(getPolygonDesignerToolPolygon(), sizeof(Polygon), "Poly.plygn");
			}
		}

		if(getMainCursor()->state != CURSOR_CLICK)
		{
			element_arr[2].position.x = joystick_center_x + 180;
			element_arr[3].position.x = joystick_center_x + 270;
			element_arr[4].position.x = joystick_center_x + 360;
		}
		else
		{

			getPolygonDesignerToolPolygon()->verts[*getSelectedPolygonVertices()].pnt.x = ((joystick_pos_x - (element_arr[1].position.x)) / 100);
			getPolygonDesignerToolPolygon()->verts[*getSelectedPolygonVertices()].pnt.z = -((joystick_pos_y - (element_arr[1].position.y)) / 100);

			if(IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON))
			{
				joystick_pos_x = getMainCursor()->position.x;
				joystick_pos_y = getMainCursor()->position.y;
			}
		}

		BeginDrawing();
		{
			ClearBackground(WHITE);
			renderMultipleUIElements(element_arr, sizeof(element_arr) / sizeof(*element_arr));

			renderByte(getLight()->tinge.r, element_arr[2].position.x, element_arr[2].position.y, 30, (Colour){255, 255, 255, 255});
			renderByte(getLight()->tinge.g, element_arr[3].position.x, element_arr[3].position.y, 30, (Colour){255, 255, 255, 255});
			renderByte(getLight()->tinge.b, element_arr[4].position.x, element_arr[4].position.y, 30, (Colour){255, 255, 255, 255});
		}
		renderCursor(getMainCursor());
		DrawFPS(10, 10);
		EndDrawing();
	}
}
#endif