#include "../../includes/core.h"
#include "../../vendor/local_curl/include/curl/curl.h"
#include <stdlib.h>
#include <string.h>

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
//We should maybe fix that, to store the char * in the central struct
char	*webscrape(void) {
	CURL	*curl = curl_easy_init();
	if (!curl)
		return (NULL);

	t_memory chunk = {.data = malloc(1)};
	if (!chunk.data)
		return (curl_easy_cleanup(curl), NULL);
	curl_easy_setopt(curl, CURLOPT_URL, "https://opensky-network.org/api/states/all");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	CURLcode res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	if (res != CURLE_OK)
	{
		custom_free(chunk.data);
		fprintf(stderr, "curl_easy_perform() error: %s\n", curl_easy_strerror(res));
		return (NULL);
	}
	return (chunk.data);
}
