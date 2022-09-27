/*
Finish wrapping the function pointers and camera into the UIElement struct as well
as adding button functionality that can carry out a function pointed to by the function pointer.
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <raylib.h>

#include "GenericStructs.h"
#include "Rendering.h"
#include "GenericFunctions.h"
#include "../RaylibHandling.h"
#include "KettleString.h"

#ifndef UI
#define UI

#define UI_BLANK 0x00
#define UI_CAMERA 0x01
#define UI_TOKEN 0x02
#define UI_BUTTON 0x03

#define CURSOR_BLANK 0x00
#define CURSOR_HOVER 0x01
#define CURSOR_CLICK 0x02
#define CURSOR_HELD 0x02

typedef void (*UIRenderFunctionPTR)(Camera);
typedef void (*UIButtonFunctionPTR)();

typedef struct UIElement
{
	KettleString name;
	RealVec position;
	RealVec dimensions;
	int type;
	Colour col;
	Texture* texture;
	RenderTexture r_texture;
	int is_movable;
	void* data;
	bool* flag_to_write_to;
}
UIElement;

typedef struct Cursor
{
	RealVec position;
	int state;
	UIElement* selected_element;
}
Cursor;

// UIElement generateUIElement(int dim_x, int dim_y, int pos_x, int pos_y, char* name, int type);
// void renderUIElement(UIElement* ui);
// Cursor* getMainCursor();
// void updateMainCursor();
// void renderCursor(Cursor* cursor);
// bool isCursorHovering(UIElement* ui, Cursor* cursor);
// bool checkUIInteraction(UIElement* ui, Cursor* cursor);
// void checkMultipleElements(UIElement* ui_arr, int ui_count, Cursor* cursor);
// void grabUIElement(Cursor* cursor);
// void updateUIElement(UIElement* element, Cursor* cursor);
// void updateUIElements(UIElement* ui_arr, int ui_count, Cursor* cursor);
// void renderMultipleUIElements(UIElement* ui_arr, int ui_count);
// void draw3DWorldToUIElement(UIElement* ui, Camera camera, void (*WorldRenderFunction)(Camera cam));

UIElement generateUIElement(int dim_x, int dim_y, int pos_x, int pos_y, KettleString name, int type, bool* flag_ptr, Colour colour)
{
	UIElement ret;
	ret.texture = NULL;
	ret.col = colour;
	ret.dimensions = (RealVec){dim_x, dim_y, 0};
	ret.position = (RealVec){pos_x, pos_y, 0};

	copyKettleString(&ret.name, &name);

	ret.type = type;
	ret.is_movable = false;
	switch (type)
	{
	case UI_CAMERA:
		ret.r_texture = LoadRenderTexture(dim_x - (dim_x / 10), dim_y - (dim_y / 10));
		ret.data = malloc(sizeof(Camera));
		break;

	case UI_TOKEN:
		ret.is_movable = true;
		break;

	case UI_BUTTON:
		ret.flag_to_write_to = flag_ptr;
		break;
	default:
		break;
	}

	return ret;
}

void giveUIElementTexture(UIElement* ui, Texture* texture)
{
	ui->texture = texture;
}

void renderUIElement(UIElement* ui)
{
	if(ui->type == UI_CAMERA)
	{
		Rectangle rec;
		rec.width = +(ui->r_texture.texture.width);
		rec.height = -(ui->r_texture.texture.height);

		rec.x = 0;//ui->position.x;
		rec.y = 0;//ui->position.y;
		DrawTextureRec(ui->r_texture.texture, rec, (Vector2){ui->position.x + ui->dimensions.x / 20, ui->position.y + ui->dimensions.y / 20}, WHITE);
	}
	if(ui->texture)
	{
		Rectangle rec;
		rec.width = (ui->dimensions.x);
		rec.height = (ui->dimensions.y);

		rec.x = 0;//ui->position.x;
		rec.y = 0;//ui->position.y;

		DrawTextureRec(*ui->texture, rec, (Vector2){ui->position.x + ui->dimensions.x / 20, ui->position.y + ui->dimensions.y / 20}, WHITE);
		return;
	}
	DrawRectangle(ui->position.x, ui->position.y, ui->dimensions.x, ui->dimensions.y, *(Color*)(&ui->col));
}
/*
Evolution of:
void renderMultipleUIElements(UIElement* ui_arr, int ui_count)
*/
void renderMultipleUIElements(UIElement* ui_arr, int ui_count)
{
	for(int i = 0; i != ui_count; i++)
	{
		renderUIElement(&ui_arr[i]);
	}
}

Cursor* getMainCursor()
{
	static Cursor cursor;
	return &cursor;
}

void updateMainCursor()
{
	//registered for speed.
	Vector2 vec = GetMousePosition();
	getMainCursor()->position.x = vec.x;
	getMainCursor()->position.y = vec.y;
}

void renderCursor(Cursor* cursor)
{
	Colour cols[] =
	{
		(Colour){255, 20, 20, 255},
		(Colour){255, 160, 160, 255},
		(Colour){255, 255, 255, 255},
		(Colour){0, 155, 255, 255},
	};
	DrawCircle(cursor->position.x, cursor->position.y, 10, *(Color*)(&cols[cursor->state]));
	DrawRing((Vector2){cursor->position.x, cursor->position.y}, 20, 30, 0, 360, 20, *(Color*)(&cols[cursor->state]));
}

bool isCursorHovering(UIElement* ui, Cursor* cursor)
{
	return (isInRange(cursor->position.x, ui->position.x, ui->position.x + ui->dimensions.x)
		&&
		isInRange(cursor->position.y, ui->position.y, ui->position.y + ui->dimensions.y));
}

/*
Evolution of:
bool isCursorHovering(UIElement* ui, Cursor* cursor)
*/
bool checkUIInteraction(UIElement* ui, Cursor* cursor)
{
	if(isCursorHovering(ui, cursor))
	{
		if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			cursor->selected_element = ui;
			cursor->state = CURSOR_CLICK;
			return true;
		}
		return false;
	}
	cursor->selected_element = NULL;
	cursor->state = CURSOR_BLANK;
	return false;
}

void UIButtonPress(UIElement* ui)
{
	(*ui->flag_to_write_to) = !(*ui->flag_to_write_to);
}

void checkMultipleElements(UIElement* ui_arr, int ui_count, Cursor* cursor)
{
	for(int i = 0; i != ui_count; i++)
	{
		if(checkUIInteraction(&ui_arr[i], cursor))
		{
			return;
		}
	}
}

void grabUIElement(Cursor* cursor)
{
	if(!cursor->selected_element)
	{
		return;
	}
	if(cursor->selected_element->is_movable && cursor->state == CURSOR_HELD)
	{
		cursor->selected_element->position.x = cursor->position.x - (cursor->selected_element->dimensions.x / 2);
		cursor->selected_element->position.y = cursor->position.y - (cursor->selected_element->dimensions.y / 2);
	}
}

void updateUIElement(UIElement* element, Cursor* cursor)
{
}

/*
evolution of:
void updateUIElement(UIElement* element, Cursor* cursor)
*/
void updateUIElements(UIElement* ui_arr, int ui_count, Cursor* cursor)
{
	for(int i = 0; i != ui_count; i++)
	{
		updateUIElement(&ui_arr[i], cursor);
	}
}

void draw3DWorldToUIElement(UIElement* ui, Camera camera, UIRenderFunctionPTR render_func)
{
	BeginTextureMode(ui->r_texture);
	{
		render_func(camera);
	}
	EndTextureMode();
}

void draw3DWorldToUIElements(UIElement* ui_arr, int ui_count)
{
	for(int i = 0; i != ui_count; i++)
	{
		if(ui_arr[i].type == UI_CAMERA)
		{
			// draw3DWorldToUIElement(&ui_arr[i], *((Camera*)(ui_arr[i].data)), (UIRenderFunctionPTR)(ui_arr[i].render_function));
		}
	}
}

void checkForUIButtonPress(UIElement* ui_arr, int ui_count, Cursor* cursor)
{
	for(int i = 0; i != ui_count; i++)
	{
		if(ui_arr[i].type == UI_BUTTON)
		{
			if(&ui_arr[i] == cursor->selected_element)
			{
				UIButtonPress(&ui_arr[i]);
			}
		}
	}
}

void UIMenu(UIElement* ui_elements, int amount, bool draw_cursor, bool debug)
{
	if(debug)
	{
		char buffer[60];
		sprintf(buffer, "Mouse X: %i, Mouse Y: %i", (int)GetMousePosition().x, (int)GetMousePosition().y);
		DrawText(buffer, 0, 0, 30, BLACK);
	}

	renderMultipleUIElements(ui_elements, amount);
	updateMainCursor();
	if(!draw_cursor)
	{
		renderCursor(getMainCursor());
	}
	// static bool process_cycle = false;
	// if(process_cycle)
	{
		checkMultipleElements(ui_elements, amount, getMainCursor());
		updateUIElements(ui_elements, amount, getMainCursor());
		checkForUIButtonPress(ui_elements, amount, getMainCursor());
	}
	// process_cycle = !process_cycle;
}

#endif
