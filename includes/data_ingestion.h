#ifndef DATA_INGESTION_H
#define DATA_INGESTION_H
#define DEFAULT_PLANE_ALTITUDE 10000
#include "core.h"

char *webscrape(void);
t_plane	*new_plane(char *icao24);
void	add_plane_back(t_plane **list, t_plane *node);
void	free_planes(t_plane *list);
void	parse_opensky_data(const char *json_string, t_central *central);

#endif
