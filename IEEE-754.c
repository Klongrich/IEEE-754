#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

double	get_sign(unsigned int *binary) {
	if (binary[0] == 0)
		return (1.0);
	else
		return (-1.0);
}

double IEEE_754_MATH(unsigned int *exp, unsigned int *mantissa) {
	int exp_value;
	double mantissa_value;
	int decimal_value_of_exp;
	double final_val;
	int d_bais;

	d_bais = 1023;
	exp_value = get_exp_value(10, exp, d_bais);
	mantissa_value = get_mantissa_value(51, mantissa);
	decimal_value_of_exp =  get_decimal_value(exp_value);
	final_val = (1 + mantissa_value) * (double)decimal_value_of_exp;
	free(exp);
	free(mantissa);
	return(final_val);

}

double	IEEE_754(unsigned int *binary) {
	unsigned int *exp;
	unsigned int *mantissa;
	int i;
	int k;
	int l;

	
	k = 0;
	l = 0;
	i = 0;
	exp = (unsigned int *)malloc(sizeof(unsigned int) * 12);
	mantissa = (unsigned int *)malloc(sizeof(unsigned int) * 60);
	while (i < 64) {
		if (i >= 1 && i < 12) 
			exp[k++] = binary[i];
		if (i >= 12) 
			mantissa[l++] = binary[i];
		i++;
	}
	return (IEEE_754_MATH(exp, mantissa) * get_sign(binary));
}

int	main() {
	double value;
	double converted_value;
	unsigned int *binary;

	value = -123.956948;
	binary = convert_to_binary(&value, sizeof(value));
	converted_value = IEEE_754(binary);

	printf(" converted_value: %f\n", converted_value);
	free(binary);
	return (0);
}
