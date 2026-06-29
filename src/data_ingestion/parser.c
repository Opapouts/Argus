#include "../../includes/data_ingestion.h"
#include "../../vendor/cJSON/cJSON.h"
#include "../../includes/utils.h"
#include "../../vendor/local_curl/include/curl/curl.h"

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

static void	extract_string_safe(cJSON *array, int index, char *dest, int len)
{
	cJSON	*item;

	item = cJSON_GetArrayItem(array, index);
	if (item && !cJSON_IsNull(item) && cJSON_IsString(item))
	{
		strncpy(dest, item->valuestring, len);
		dest[len] = '\0';
	}
}
//fallback_value is the value we will set the fiels if one check fails (e.g 0.0)
static double	extract_double_safe(cJSON *array, int index, double fallback_value)
{
	cJSON	*item;

	item = cJSON_GetArrayItem(array, index);
	if (item && !cJSON_IsNull(item) && cJSON_IsNumber(item))
		return (item->valuedouble);
	return (fallback_value);
}

static void	fill_out_plane_fields(cJSON *flight, t_plane *list)
{
	extract_string_safe(flight, 1, list->identity.callsign, 8);
	extract_string_safe(flight, 2, list->identity.origin_country, 31);
	list->time.time_position = (int64_t)extract_double_safe(flight, 3, 0);
	list->time.last_contact = (int64_t)extract_double_safe(flight, 4, 0);
	cJSON	*on_ground_item = cJSON_GetArrayItem(flight, 8);
	if (!on_ground_item && cJSON_IsBool(on_ground_item))
		list->movement.on_ground = cJSON_IsTrue(on_ground_item);
	list->position.longitude = extract_double_safe(flight, 5, 0.0);
	list->position.latitude = extract_double_safe(flight, 6, 0.0);
	if (list->movement.on_ground)
	{
		list->position.baro_altitude = (float)extract_double_safe(flight, 7, 0.0);
		list->position.geo_altitude = (float)extract_double_safe(flight, 13, 0.0);
	}
	else
	{	
		list->position.baro_altitude = (float)extract_double_safe(flight, 7, DEFAULT_PLANE_ALTITUDE);
		list->position.geo_altitude = (float)extract_double_safe(flight, 13, DEFAULT_PLANE_ALTITUDE);
	}
	list->movement.velocity = (float)extract_double_safe(flight, 9, 0.0);
	list->movement.true_track = (float)extract_double_safe(flight, 10, 0.0);
	list->movement.vertical_rate = (float)extract_double_safe(flight, 11, 0.0);
}

void	parse_opensky_data(const char *json_string, t_central *central)
{
	cJSON	*root;

	root = cJSON_Parse(json_string);
	if (!root)
		return (custom_write("Error Parsing JSON\n"));

	cJSON	*states_array = cJSON_GetObjectItemCaseSensitive(root, "states");
	if (!states_array || !cJSON_IsArray(states_array))
		return (cJSON_Delete(root));

	int	nbr_of_planes = cJSON_GetArraySize(states_array);
	for (int i = 0; i < nbr_of_planes; i++)
	{
		cJSON	*flight = cJSON_GetArrayItem(states_array, i);
		if (!cJSON_IsArray(flight) || cJSON_GetArraySize(flight) < 17)
			continue ;
		cJSON	*icao24 = cJSON_GetArrayItem(flight, 0);
		if (!icao24 || cJSON_IsNull(icao24) || !cJSON_IsString(icao24))
			continue ;

		t_plane	*new_node = new_plane(icao24->valuestring);
		if (!new_node)
			continue ;
		fill_out_plane_fields(flight, new_node);
		add_plane_back(&(central->planes), new_node);
	}
	cJSON_Delete(root);
}

/*static void	print_things(t_central *central)
{
	t_plane	*tmp;

	tmp = central->planes;
	while (tmp)
	{
		printf("icao24-> %s ||| callsign-> %s ||| velocity-> %f\n", tmp->identity.icao24, tmp->identity.callsign, tmp->movement.velocity);
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
	curl_global_init(CURL_GLOBAL_DEFAULT);
	data = webscrape();
	parse_opensky_data(data, &central);
	//print_things(&central);
	free_planes(central.planes);
	free(data);
	curl_global_cleanup();
	return (0);
}
