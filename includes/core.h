#ifndef CORE_H
#define CORE_H
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef	struct	s_memory
{
	char	*data;//All the raw data received from the API
	size_t	size;
}		t_memory;

typedef	struct	s_identity
{
	char		icao24[7];//Plane id 
	char		callsign[9];
	char		origin_country[32];
}		t_identity;//48 bytes

typedef	struct	s_time
{
	int64_t	time_position;//Last time GPS coordinates were received
	int64_t	last_contact;
}		t_time;//16 bytes

typedef	struct	s_position
{
	double	longitude;
	double	latitude;
	float	baro_altitude;//Altitude calculated from the barometric pressure gauge
	float	geo_altitude;
}		t_position;//24 bytes

typedef	struct	s_movement
{
	bool	on_ground;
	float	velocity;
	float	true_track;//0 = North, 90 = East etc
	float	vertical_rate;//How fast the plane is ascending or descending(m/s)
}		t_movement;//16 bytes
//It has to be noted, that a lot of info won't be needed at the end

typedef	struct	s_plane
{
	t_identity	identity;
	t_time		time;
	t_position	position;
	t_movement	movement;
	struct	s_plane	*next;

}		t_plane;//112 bytes (For 10.000 active planes this linked list will consume
			//~1.1 Megabytes of RAM

typedef	struct	s_central
{
	t_plane		*planes;
	t_memory	*memory;//Pas necessaire pour l'instant
}		t_central;

#endif
