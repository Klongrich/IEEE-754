#include "IEEE_754.h"

int	main() {
	double value;
	double converted_value;
	unsigned int *binary;

	value = -123.956948;
	binary = convert_to_binary(&value, sizeof(value));
	converted_value = IEEE_754(binary);
	
	printf("converted_value: %f\n", converted_value);	
	free(binary);
	return (0);
}
