#include "../../includes/data_ingestion.h"
#include "../../includes/utils.h"

static void	set_plane_to_null(t_plane *plane)
{
	plane->identity.icao24[0] = '\0';
	plane->identity.callsign[0] = '\0';
	plane->identity.origin_country[0] = '\0';
	plane->time.time_position = 0;
	plane->time.last_contact = 0;
	plane->position.longitude = 0.0;
	plane->position.latitude = 0.0;
	plane->position.baro_altitude = 0.0f;
	plane->position.geo_altitude = 0.0f;
	plane->movement.on_ground = false;
	plane->movement.velocity = 0.0f;
	plane->movement.true_track = 0.0f;
	plane->movement.vertical_rate = 0.0f;
	plane->next = NULL;
}

t_plane	*new_node(char *icao)
{
	t_plane	*new;

	new = NULL;
	if (!icao)
		return (NULL);
	new = malloc(sizeof(t_plane));
	if (!new)
		return (NULL);
	set_plane_to_null(new);
	strncpy(new->identity.icao24, icao, 7);
	return (new);
}

void	add_node_back(t_plane **list, t_plane *node)
{
	t_plane *tmp;

	tmp = NULL;
	if (!list || !node)
		return ;
	if (!*list)
		list = &node;
	while (tmp)
		tmp = (*list)->next;
	tmp = node;
}


