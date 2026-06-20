#include "../../includes/data_ingestion.h"

void	custom_write(char *str) {
	while (*str)
		write(2, str++, 1);
	write(2, "\n", 1);
}

/*
 *contents ->the data returned from the request
 *size ->size of one element, and since its always one byte size = 1
 *n -> number of bytes
 * userp (user pointer) -> This gives my callback function access to the
 * memory struct (accumulator struct)
 */

static size_t	callback(void *contents, size_t size, size_t n, void *userp) {
	size_t		real_size;
	t_memory	*mem;
	char		*ptr;

	real_size = n * size;
	mem = (t_memory *)userp;
	ptr = realloc(mem->data, mem->size + real_size + 1);
	if (!ptr)
		return (custom_write("Not enough memory"), 0);
	mem->data = ptr;
	memcpy(&mem->data[mem->size], contents, real_size);
	mem->size += real_size;
	mem->data[mem->size] = 0;
	return (real_size);
}

void	webscrape(void) {
	curl_global_init(CURL_GLOBAL_DEFAULT);
	CURL	*curl = curl_easy_init();

	t_memory chunk = {.data = malloc(1)};
	
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://opensky-network.org/api/states/all");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		else {
			printf("Received %zu bytes:\n", chunk.size);
			printf("%.500s...\n", chunk.data);
		}
		curl_easy_cleanup(curl);
	}
	free(chunk.data);
	curl_global_cleanup();
}
//We receive the information in this format, 
//{"time":1781976265,"states":[["39de4f","TVF38EU ","France",1781976265,1781976265,7.6636,46.0714,11567.16,false,226.27,299.71,0,null,12146.28,"1000",false,0] ...after this there are other flight information

int	main(void)
{
	webscrape();
	return (0);
}
