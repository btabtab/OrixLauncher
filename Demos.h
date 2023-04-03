#ifndef DEMOS
#define DEMOS
#include <raylib.h>

#include "EngineCode/Rendering.h"
#include "EngineCode/GenericStructs.h"
#include "EngineCode/RealVecOperations.h"
#include "RaylibHandling.h"
#include "EngineCode/UI.h"
#include "EngineCode/KettleRenderer.h"
#include "EngineCode/KettleString.h"

Light* getLight()
{
	static Light light = {(RealVec){0, 1, 0}, 1, (Color){0, 0, 0, 255}};
	return &light;
}

void VertexLightingDemo()
{
	Camera camera;
	startup("Kettle renderer 1.0 Demo", 600, 600, &camera, 60);

	// Environment environment = initEnvironment();
	Polygon p[2] = {testPolygon(6.f), testPolygon(6.f)};

	for(int i = 0; i != 3; i++)
	{
		p[1].verts[i].pnt = addRealVecs(p[1].verts[i].pnt, (RealVec){-6, 0, 0});
	}

	Light light = testLight();

	while (!WindowShouldClose())
	{
		UpdateCamera(&camera);
			BeginDrawing();

			ClearBackground(BLACK);
			BeginMode3D(camera);

			// renderEnvironment(&environment);
			drawPolygonWireFrame(&p[0]);
			drawPolygonWireFrame(&p[1]);

			// renderPolygonSubSet(getTriSubPolygonSet(p));
			renderPolygonSubSetWithLighting(getTriSubPolygonSet(p[0]), light);
			renderPolygonSubSetWithLighting(getTriSubPolygonSet(p[1]), light);
			// renderPolygonSubSet(getTriSubPolygonSet(p));
			renderLight(&light);
			EndMode3D();

			DrawText("Hold either the R, G or B keys to change the light colour.", 10, 30, 20, WHITE);
			DrawText("Press space to reset the light.", 10, 50, 20, WHITE);
			DrawText("Hold J or U to change the lights position.", 10, 70, 20, WHITE);

			DrawFPS(10, 10);
			// char* buffer;
			// sprintf(buffer, "%f", distanceBetweenRealVecs(light.position, findMiddleOfPolygon(p)));
			// DrawText(buffer, 10, 50, 20, GREEN);


		EndDrawing();
		
		{
			light.position.y += IsKeyDown(KEY_U);
			light.position.y -= IsKeyDown(KEY_J);

			{
				light.tinge.r += IsKeyDown(KEY_R);
				light.tinge.g += IsKeyDown(KEY_G);
				light.tinge.b += IsKeyDown(KEY_B);
				if(IsKeyPressed(KEY_SPACE))
				{
					light = testLight();
				}
				light.strength += (IsKeyDown(KEY_S) * .0002f);
			}

		}
	}

	CloseWindow();

}

Light global_light;

void UIDrawToDemo(Camera cam)
{
	Polygon p[2] = {testPolygon(6.f), testPolygon(6.f)};

	for(int i = 0; i != 3; i++)
	{
		p[1].verts[i].pnt = addRealVecs(p[1].verts[i].pnt, (RealVec){-6, 0, 0});
	}

	global_light = testLight();

	// UpdateCamera(&cam);
	ClearBackground(BLACK);
	BeginMode3D(cam);
	{
		// renderEnvironment(&environment);
		drawPolygonWireFrame(&p[0]);
		drawPolygonWireFrame(&p[1]);
		// renderPolygonSubSet(getTriSubPolygonSet(p));
		renderPolygonWithLighting(&p[0], global_light);
		renderPolygonWithLighting(&p[1], global_light);
		// renderPolygonSubSet(getTriSubPolygonSet(p));
		renderLight(&global_light);
	}
	EndMode3D();
	DrawFPS(10, 10);
}

void UIDemo()
{
	Camera cam;
	startup("UI demo", 600, 600, &cam, 60);
	
	SetCameraMode(cam, CAMERA_ORBITAL);

	UIElement small_ui = generateUIElement(150, 150, 20, 20, newKettleString("A"), UI_CAMERA, NULL, J_RED);

	UIElement big_ui = generateUIElement(400, 400, 170, 20, newKettleString("B"), UI_CAMERA, NULL, J_RED);

	while(!WindowShouldClose())
	{
		updateMainCursor();
		checkUIInteraction(&small_ui, getMainCursor());

		checkUIInteraction(&big_ui, getMainCursor());

		draw3DWorldToUIElement(&small_ui, cam, UIDrawToDemo);
		draw3DWorldToUIElement(&big_ui, cam, UIDrawToDemo);

		BeginDrawing();
		{
			ClearBackground(WHITE);
			renderUIElement(&small_ui);
			renderUIElement(&big_ui);
		}
		renderCursor(getMainCursor());
		DrawFPS(10, 10);
		EndDrawing();
	}
}

void UIDemoMovableElement()
{
	Camera cam;
	startup("UI demo", 600, 600, &cam, 60);
	
	UIDrawToDemo(cam);
	SetCameraMode(cam, CAMERA_ORBITAL);

	UIElement element_arr[3] =
	{
		generateUIElement(150, 150, 20, 20, newKettleString("A"), UI_CAMERA, NULL, J_WHITE),
		generateUIElement(400, 400, 170, 20, newKettleString("B"), UI_CAMERA, NULL, J_WHITE),
		generateUIElement(70, 70, 600, 170, newKettleString("C"), UI_TOKEN, NULL, J_WHITE),
	};


	while(!WindowShouldClose())
	{
		updateMainCursor();


		checkMultipleElements(element_arr, sizeof(element_arr) / sizeof(*element_arr), getMainCursor());
		updateUIElements(element_arr, sizeof(element_arr) / sizeof(*element_arr), getMainCursor());

		draw3DWorldToUIElement(&element_arr[0], cam, UIDrawToDemo);
		draw3DWorldToUIElement(&element_arr[1], cam, UIDrawToDemo);
		grabUIElement(getMainCursor());
		BeginDrawing();
		{
			ClearBackground(WHITE);
			renderMultipleUIElements(element_arr, sizeof(element_arr) / sizeof(*element_arr));
		}
		renderCursor(getMainCursor());
		DrawFPS(10, 10);
		EndDrawing();
	}
}

void renderPolygonScene(Camera cam)
{
	Polygon p[2] = {testPolygon(6.f), testPolygon(6.f)};

	// setPolygonsToTestSquare(10.f, p);

	for(int i = 0; i != 3; i++)
	{
		p[1].verts[i].pnt = addRealVecs(p[1].verts[i].pnt, (RealVec){-6, 0, 0});
	}

	// UpdateCamera(&cam);
	// SetCameraMode(cam, CAMERA_ORBITAL + ((IsKeyDown(KEY_R)) * 2));
	ClearBackground(BLACK);
	BeginMode3D(cam);
	{
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

void polygonLightingUITest()
{
	Camera cam;
	startup("Kettle renderer 2.0 Demo", 800, 800, &cam, 60);

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
	};

	while(!WindowShouldClose())
	{

		checkMultipleElements(element_arr, sizeof(element_arr) / sizeof(*element_arr), getMainCursor());
		updateUIElements(element_arr, sizeof(element_arr) / sizeof(*element_arr), getMainCursor());
		updateMainCursor();

		draw3DWorldToUIElement(&element_arr[0], cam, renderPolygonScene);

		grabUIElement(getMainCursor());

		getLight()->position.z = ((joystick_center_x - (element_arr[1].position.x)) / 100);
		getLight()->position.x = -((joystick_center_y - (element_arr[1].position.y)) / 100);

		getLight()->tinge.r = (limitRangeByte((joystick_center_y) - (element_arr[2].position.y), 0, 255));
		getLight()->tinge.g = (limitRangeByte((joystick_center_y) - (element_arr[3].position.y), 0, 255));
		getLight()->tinge.b = (limitRangeByte((joystick_center_y) - (element_arr[4].position.y), 0, 255));

		if(getMainCursor()->state != CURSOR_CLICK)
		{
			element_arr[1].position.x = joystick_center_x;
			element_arr[1].position.y = joystick_center_y;

			element_arr[2].position.x = joystick_center_x + 180;
			element_arr[3].position.x = joystick_center_x + 270;
			element_arr[4].position.x = joystick_center_x + 360;

			
		}

		BeginDrawing();
		{
			ClearBackground(WHITE);
			renderMultipleUIElements(element_arr, sizeof(element_arr) / sizeof(*element_arr));

			renderByte(getLight()->tinge.r, element_arr[2].position.x, element_arr[2].position.y, 30, (Color){255, 255, 255, 255});
			renderByte(getLight()->tinge.g, element_arr[3].position.x, element_arr[3].position.y, 30, (Color){255, 255, 255, 255});
			renderByte(getLight()->tinge.b, element_arr[4].position.x, element_arr[4].position.y, 30, (Color){255, 255, 255, 255});
		}
		renderCursor(getMainCursor());
		DrawFPS(10, 10);
		EndDrawing();
	}
}

#endif