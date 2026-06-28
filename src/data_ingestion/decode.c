#include "../../includes/data_ingestion.h"
#include "../../includes/utils.h"

//We save the API result at the t_memory struct. We need to create a function that
//initialise the main struct and have a pointer to the t_memory and the new t_plane
//linked list. The API returns 17 fields of informatiion. Not everything is needed.
//Example of output of the OpenSky API
//{
//  "time": 1624567890,
//  "states": [
//    ["39de4f", "TVF38EU", "France", 1624567890, ...], 
//    ["4b1815", "SWR123", "Switzerland", 1624567885, ...],
//    ["a89b21", "DAL456", "United States", 1624567889, ...]
//  ]
//}
//The API can return null for some fields so we have to be carefull of that.
//We will create a cJSON struct to avoid having 40 cJSON variables.
//Is there a better way to do that?
//To do->Create a function that will check if any cJSON is null/string/numbers etc.
void	parse_opensky_data(const char *json_string, t_central *central) {
	t_cJSON	cJSON_struct;
	int	nbr_of_planes;

	cJSON_struct.root = cJSON_Parse(json_string);
	if (!cJSON_struct.root)
		return (custom_write("Error Parsing JSON\n"));
	cJSON_struct.states_array = cJSON_GetObjectItemCaseSensitive(cJSON_struct.root, "states");
	if (!cJSON_struct.states_array || !cJSON_IsArray(cJSON_struct.states_array))
		return (cJSON_Delete(cJSON_struct.root));

	nbr_of_planes = cJSON_GetArraySize(cJSON_struct.states_array);
	for (int i = 0; i < nbr_of_planes; i++)
	{
		cJSON_struct.flight = cJSON_GetArrayItem(cJSON_struct.states_array, i);
		cJSON_struct.icao24 = cJSON_GetArrayItem(cJSON_struct.flight, 0);
		cJSON_struct.callsign = cJSON_GetArrayItem(cJSON_struct.flight, 1);
		if (cJSON_struct.icao24 != NULL && cJSON_IsString(cJSON_struct.icao24) &&
			cJSON_struct.callsign != NULL && cJSON_IsString(cJSON_struct.callsign)) {
			t_plane *node = new_plane(cJSON_struct.icao24->valuestring);
			if (!node)
				continue ;
			strncpy(node->identity.icao24, cJSON_struct.icao24->valuestring, 6);
			strncpy(node->identity.callsign, cJSON_struct.callsign->valuestring, 8);
			node->identity.callsign[8] = '\0';
			add_plane_back(&central->planes, node);
		}
	}
	cJSON_Delete(cJSON_struct.root);
}

/*static void	print_things(t_central *central)
{
	t_plane	*tmp;

	tmp = central->planes;
	while (tmp)
	{
		printf("icao24-> %s				callsign-> %s\n", tmp->identity.icao24, tmp->identity.callsign);
		tmp = tmp->next;
	}
}*/

static void	free_planes(t_plane *plane)
{
	t_plane *tmp = plane;
	while (tmp)
	{
		plane = tmp->next;
		free(tmp);
		tmp = plane;
	}
}


int	main(void)
{
	char	*data;
	t_central	central;

	central.planes = NULL;
	data = webscrape();
	parse_opensky_data(data, &central);
	//print_things(&central);
	free_planes(central.planes);
	free(data);
	return (0);
}
