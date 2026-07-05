#include "../../includes/graphics_engine.h"

Vector3	convertGPSinto3D(float lat, float lon, float altitude)
{
	Vector3	pos = { 0 };

	float	latRad = lat * (PI / 180.0f);
	float	lonRad = lon * (PI / 180.0f);

	if (altitude < 0)
		altitude = 0;
	float	r = EARTH_RADIUS + (altitude + ALTITUDE_SCALE);

	pos.y = r * sinf(latRad);
	pos.x = r * cosf(latRad) * cosf(lonRad);
	pos.z = r * cosf(latRad) * sinf(lonRad);

	return (pos);
}
