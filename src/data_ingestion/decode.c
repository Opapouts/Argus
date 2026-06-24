#include "../../includes/data_ingestion.h"
#include "../../includes/utils.h"

//We save the API result at the t_memory struct. We need to create a function that
//initialise the main struct and have a pointer to the t_memory and the new t_plane
//linked list. The API returns 17 fields of informatiion. Not everything is needed.
//Example of output of the OpenSky API
//{"time":1781976265,"states":[["39de4f","TVF38EU ","France",1781976265,1781976265,7.6636,46.0714,11567.16,false,
//226.27,299.71,0,null,12146.28,"1000",false,0] ...after this there are other flight information
//The API can return null for some fields so we have to be carefull of that.
//

