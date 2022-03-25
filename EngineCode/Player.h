#ifndef PLAYER
#define PLAYER
#include <raylib.h>
#include "GenericFunctions.h"
#include "KettleRenderer.h"
#include "UI.h"
#include "Entity.h"

typedef struct Player
{
	Entity ent;
	int exp;
	int health;
	int magic;
	Camera* cam;
}
Player;

Player* getPlayer()
{
	static Player player;
	return &player;
}

void renderPlayer(Camera cam, Light light)
{
	renderEntity(&getPlayer()->ent, cam, light);
}

void updatePlayerPos(Player* player)
{
	// player->ent.position = addRealVecs(player->ent.position, player->ent.move_direction);
	player->ent.position.x += limitRangeFloat(player->ent.move_direction.x, -1, 1);
	player->ent.position.z += limitRangeFloat(player->ent.move_direction.z, -1, 1);
}

void moveCursorDrag(Player* player, int MOVEMENT_SENSITIVITY)
{

	static int x, y;
	float x_diff = x - getMainCursor()->position.x;
	float y_diff = y - getMainCursor()->position.y;

	if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			x = getMainCursor()->position.x;
			y = getMainCursor()->position.y;
		}
		DrawLine(x, y, x - x_diff, y - y_diff, WHITE);
		return;
	}
	else
	{
		player->ent.move_direction = (RealVec){(player->ent.move_direction.x * 1.5) / 2, 0, (player->ent.move_direction.z * 1.5) / 2};
	}
	if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
	{
		player->ent.move_direction = (RealVec){(x_diff / MOVEMENT_SENSITIVITY), 0, (y_diff / MOVEMENT_SENSITIVITY)};
	}
	static bool move_frame = false;
	if(move_frame)
	{
		updatePlayerPos(player);
	}
	move_frame = !move_frame;
	player->cam->position.x = player->ent.position.x;
	player->cam->position.z = player->ent.position.z - 20;
}

#endif