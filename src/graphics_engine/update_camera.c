#include "../../includes/graphics_engine.h"

void	update_camera(Camera3D *camera)
{
	Vector3	movement = {0.0f, 0.0f, 0.0f};
	Vector3 rotation = {0.0f, 0.0f, 0.0f};
	float	zoom = 0.0f;
	float	rot_speed = 0.2f;
	float	pan_speed = 0.5f;

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		Vector2	mouseDelta = GetMouseDelta();
		rotation.x = mouseDelta.x * rot_speed;
		rotation.y = mouseDelta.y * rot_speed;
	}
	if (IsKeyDown(KEY_W))
		movement.x = pan_speed;
	if (IsKeyDown(KEY_S))
		movement.x = -pan_speed;
	if (IsKeyDown(KEY_A))
		movement.y = -pan_speed;
	if (IsKeyDown(KEY_D))
		movement.y = pan_speed;
	if (IsKeyDown(KEY_UP))
		movement.z = pan_speed;
	if (IsKeyDown(KEY_DOWN))
		movement.z = -pan_speed;
	zoom = GetMouseWheelMove() * (-1.5f);
	UpdateCameraPro(camera, movement, rotation, zoom);
}
		
