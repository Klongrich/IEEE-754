#include "IEEE_754.h"

unsigned int	*convert_to_binary(void *ptr, size_t size) {
	ssize_t i;
	int16_t j;
	uint32_t l;
	unsigned char *holder;
	unsigned int *res;

	holder = (unsigned char *)ptr;
	res = (unsigned int *)malloc(sizeof(unsigned int) * 65);	
	i = size - 1;
	j = 7;
	l = 0;
	while (i >= 0) {
		j = 7;
		while (j >= 0) {
			res[l++] = (holder[i] >> j--) & 1 ? 1 : 0;
		}
		i--;
	}
	res[l] = '\0';
	return(res);
}
