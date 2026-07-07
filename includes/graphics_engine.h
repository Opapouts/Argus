#ifndef GRAPHICS_ENGINE_H

#ifndef PI
#define PI 3.14159265358979323846f
#endif
#define EARTH_RADIUS 4.0f
#define ALTITUDE_SCALE 0.000002f
#define SCRAPE_INTERVAL 10.0
#include "../vendor/raylib/src/raylib.h"
#include "core.h"


void	graph_setup(Camera3D *camera);
void	draw_planes(t_plane *first_plane);
void	update_camera(Camera3D *camera);
Vector3	convertGPSinto3D(float lat, float lon, float altitude);


#endif
