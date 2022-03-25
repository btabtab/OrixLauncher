#include <raylib.h>
#ifndef RAYLIBHANDLER
#define RAYLIBHANDLER
void startup(const char* name, int width, int height, Camera3D* camera)
{
	InitWindow(width, height, name);
	if(camera)
	{
		(*camera) = (Camera3D){ 0 };
		camera->position = (Vector3){ 10.0f, 10.0f, 8.0f };
		camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };
		camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
		camera->fovy = 60.0f;
		camera->projection = CAMERA_PERSPECTIVE;
		SetCameraMode(*camera, CAMERA_THIRD_PERSON);
	}
	SetTargetFPS(60);
}
#endif