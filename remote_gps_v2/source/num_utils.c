/*
 * num_utils.c
 *
 *  Created on: Jul 9, 2015
 *      Author: Visakhan
 */


#include "num_utils.h"

/* Parse a floating point number from given number of charachers */
void parse_float(float *output, const char *buf, int length)
{
	float result = 0.0;
	int len = length, dotpos = 0, dec = 0;
	char *ptr;
	bool neg = false;

	if('-' == buf[0])
	{
		neg = true;
	}

	/* find decimal point */
	ptr = (char *)buf+neg;
	while(len--)
	{
		if('.' == *ptr++)
			break;
		dotpos++;
	}

	/* Get decimal part */
	if(dotpos > 0)
	{
		ptr = (char *)buf+neg;
		while(*ptr != '.')
		{
			dec = dec*10 + (*ptr - '0');
			ptr++;
		}
	}

	/* get fractional part */
	if(dotpos < length)
	{
		ptr = (char *)&buf[length-1];
		while(*ptr != '.')
		{
			result = (result + (float)(*ptr - '0'))/10.0;
			ptr--;
		}
	}

	result += (float)dec;
	if(true == neg)
		result = -result;

	*output = result;
}


/* Parse a decimal number from a given length of characters */
void parse_decimal(int* output, const char *buf, int length)
{
	int result = 0, len;
	bool neg = false;
	char *ptr;

	if('-' == buf[0])
	{
		neg = true;
	}

	ptr = (char *)buf+neg;
	len = 0;
	while(len < length)
	{
		if((*ptr < '0') || (*ptr > '9'))
			break;

		result = result*10 + (*ptr - '0');
		ptr++;
		len++;
	}

	if(true == neg)
	{
		result = -result;
	}

	*output = result;
}


int get_quoted_string(const uint8_t *source, uint8_t *dest, int limit)
{
	char *ptr = (char *)source;
	int offset = 0;

	if(*ptr != '\"')
	{
		/* Return length */
		return -1;
	}

	while(*++ptr != '\"')
	{
		dest[offset++] = *ptr;
		if(offset >= limit)
		{
			break;
		}
	}

	dest[offset] = '\0';

	/* Return length of string copied */
	return offset;
}



int float_to_string(const float *num, int frac_len, uint8_t *buf)
{

	float real = *num;
	int dec, div, offset = 0;
	uint8_t digit;

	if(real < 0) {
	  real = -real;
	  buf[offset++] = '-';
	}

	/* Decimal part */
	dec = (int)real;
	if(0 == dec)
	{
		buf[offset++] = '0';
	}
	else {
		div = 1;
		while(div <= dec)
			div *= 10;

		do {
			div /= 10;
			digit = (uint8_t)(dec/div);
			dec -= digit*div;
			buf[offset++] = digit + '0';
		} while (dec != 0);
	}

	buf[offset++] = '.';

	/* Fractional part */
	real = real - (int)real;
	while(frac_len > 0) {
		real *= 10;
		digit = (int)real;
		real -= digit;
		buf[offset++] = digit + '0';
		frac_len--;
	}

	buf[offset] = '\0';

	return offset;

}






