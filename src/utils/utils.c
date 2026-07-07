#include "../../includes/core.h"
#include <stdlib.h>

void	custom_write(char *str)
{
	while (*str)
		write(2, str++, 1);
	write(2, "\n", 1);
}

void	custom_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
