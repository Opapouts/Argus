#include "../../includes/utils.h"

void	custom_write(char *str) {
	while (*str)
		write(2, str++, 1);
	write(2, "\n", 1);
}
