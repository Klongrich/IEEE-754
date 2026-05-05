#include <unistd.h>
#include <stdio.h>
#include <float.h>

void	print_arry(unsigned int *arr, int n) {
	int i;

	i = 0;
	while (i < n) {
		printf("%u", arr[i]);
		i++;
	}
	printf("\n");
}
	

int	get_decimal_value(int i) {
	int value;

	value = 1;
	while (i > 0) {
		value *= 2;
		i--;	
	}
	return (value);
}

int	get_exp_value(int top_value, unsigned int *bits, int bias) {
	int j;
	int i;
	int value;

	value = 0;
	i = top_value;
	j = 0;
	while (i > -1) {		
		if (bits[j] == 1) {
			value += get_decimal_value(i);
		}
		i--;
		j++;
	}
	return (value - bias);
}

double	get_mantissa_bit_value(int i) {
	double value;

	value = 1.0;
	while (i >= 0) {
		value *= 2.0;
		i--;	
	}
	return (1.0 / value);
}

double	get_mantissa_value(int top_value, unsigned int *bits) {
	int j;
	int i;
	double value;

	value = 0.0;
	i = 0;
	j = 0;
	while (i < top_value) {		
		if (bits[j] == 1) 
			value += get_mantissa_bit_value(i);
		i++;
		j++;
	}
	return (value);
}

void	print_64bit_binary(void *ptr, size_t size) {
	int i;
	int j;
	int bit_pos;
	unsigned char bit;
	unsigned char *b;
	int sign;
	unsigned int exp[12];
	unsigned int mantissa[60];
	int k;
	int l;

	
	k = 0;
	l = 0;
	b = (unsigned char *)ptr;
	i = size - 1;
	j = 7;
	while (i >= 0) {
		j = 7;
		while (j >= 0) {
			bit_pos = (i * 8) + j;
			bit = (b[i] >> j) & 1;
			if (bit_pos == 63)
				sign = bit;
			if (bit_pos <= 62 && bit_pos > 51) 
				exp[k++] = bit;
			if (bit_pos <= 51) 
				mantissa[l++] = bit;
			printf("%u", bit);
			if (bit_pos == 63 || bit_pos == 52)
				printf(" ");
			j--;
		}
		i--;
	}


	int exp_value;
	double mantissa_value;
	int decimal_value_of_exp;

	exp_value = get_exp_value(10, exp, 1023);
	mantissa_value = get_mantissa_value(51, mantissa);
	decimal_value_of_exp =  get_decimal_value(exp_value);

	double final_val;
	
	final_val = (1 + mantissa_value) * (double)decimal_value_of_exp;
	printf(" -> IEEE 754: -> %f\n", final_val);
}

int	main() {
	double value;
	int d_bias = 1023;

	value = 123.956948;

	//IEEE 754
	print_64bit_binary(&value, sizeof(value));
	return (0);
}
