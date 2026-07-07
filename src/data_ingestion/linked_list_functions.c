#include "../../includes/data_ingestion.h"
#include <stdlib.h>
#include <string.h>

t_plane	*new_plane(char *icao24)
{
	t_plane	*new;

	new = NULL;
	if (!icao24)
		return (NULL);
	new = calloc(1, sizeof(t_plane));//Sets everything to 0/null/false
	if (!new)
		return (NULL);
	strncpy(new->identity.icao24, icao24, 7);
	return (new);
}

void	add_plane_back(t_plane **list, t_plane *node)
{
	t_plane *tmp;

	tmp = NULL;
	if (!list || !node)
		return ;
	if (!*list)
	{
		*list = node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	free_planes(t_plane *list)
{
	t_plane *tmp;

	while (list)
	{
		tmp = list->next;
		custom_free(list);
		list = tmp;
	}
}
