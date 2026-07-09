#include "../../includes/core.h"
#include "../../includes/graphics_engine.h"

void	graph_setup(Camera3D *camera)
{
	InitWindow(800, 450, "Argus");
	SetTargetFPS(60);
	camera->position = (Vector3){0.0f, 0.0f, 10.0f};
	camera->target = (Vector3){0.0f, 0.0f, 0.0f};
	camera->up = (Vector3){0.0f, 1.0f, 0.0f};
	camera->fovy = 45.0f;
	camera->projection = CAMERA_PERSPECTIVE;
}

void	draw_planes(t_plane *first_plane)
{
	t_plane *tmp = first_plane;

	while (tmp)
	{
		Vector3 plane_pos = convertGPSinto3D((Vector3){
				tmp->position.latitude,
				tmp->position.longitude,
				tmp->position.geo_altitude});
		if (!tmp->movement.on_ground)
			DrawSphere(plane_pos, 0.01f, RED);
		tmp = tmp->next;
	}
}

void	place_dot_on_map(Vector3 position, Color color)
{
	Vector3 place = convertGPSinto3D(position);
	DrawSphere(place, 0.2f, color);
}
