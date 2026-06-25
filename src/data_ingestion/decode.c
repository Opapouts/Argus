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

void	parse_opensky_data(const char *json_string, t_central *central) {
	cJSON	*root;
	cJSON	*states_array;
	int	nbr_of_planes;

	root = cJSON_Parse(json_string);
	if (!root)
		return (custom_write("Error Parsing JSON\n"));
	states_array = cJSON_GetObjectItemCaseSensitive(root, "states");
	if (cJSON_IsArray(states_array))
	{
		nbr_of_planes = cJSON_GetArraySize(states_array);
		for (int i = 0; i < nbr_of_planes; i++) {
			cJSON	*flight = cJSON_GetArrayItem(states_array, i);
			cJSON	*icao24 = cJSON_GetArrayItem(flight, 0);
			cJSON	*callsign = cJSON_GetArrayItem(flight, 1);
			if (icao24 != NULL && cJSON_IsString(icao24) &&
				callsign != NULL && cJSON_IsString(callsign)) {
				t_plane *new_plane = malloc(sizeof(t_plane));//add securities
				strncpy(new_plane->identity.icao24, icao24->valuestring, 6);
				new_plane->identity.icao24[6] = '\0';
				strncpy(new_plane->identity.callsign, callsign->valuestring, 8);
				new_plane->identity.callsign[8] = '\0';
				//We need the linked lists functions




