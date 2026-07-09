#include "../../includes/graphics_engine.h"
#include <math.h>

Vector3	convertGPSinto3D(Vector3 gps)
{
	Vector3	pos = {0};

	float	latRad = gps.x * (PI / 180.0f);
	float	lonRad = gps.y * (PI / 180.0f);

	if (gps.z < 0)
		gps.z = 0;
	float	r = EARTH_RADIUS + (gps.z * ALTITUDE_SCALE);

	pos.y = r * sinf(latRad);
	pos.x = -r * cosf(latRad) * sinf(lonRad);
	pos.z = -r * cosf(latRad) * cosf(lonRad);

	return (pos);
}
