#ifndef DATA_INGESTION_H
#define DATA_INGESTION_H

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef	struct	s_memory
{
	char	*data;
	size_t	size;
}		t_memory;

void	webscrape(void);

//Random functions, maybe should move them out from here
void	custom_write(char *str);

#endif
