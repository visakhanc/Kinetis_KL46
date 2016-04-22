/*
 * gps_parse.c
 *
 *  Created on: Jun 27, 2015
 *      Author: Visakhan
 */


#include "gps_parse.h"
#include "num_utils.h"


/* Parse a GPGGA senstence */
int gps_parse_gga(const char *buf, gps_info_struct_ptr gps_info_ptr)
{
	char *ptr;
	int num;
	float temp;

	/* 1. Time */
	ptr = (char *)buf;
	if(*ptr != ',')
	{
		parse_decimal(&num, ptr, 2);
		gps_info_ptr->time.hour = num;
		ptr += 2;
		parse_decimal(&num, ptr, 2);
		gps_info_ptr->time.min = num;
		ptr += 2;
		parse_decimal(&num, ptr, 2);
		gps_info_ptr->time.sec = num;
		ptr += 6; // skip fraction of sec
	}

	/* 2. Latitude */
	if(*++ptr != ',')
	{
		parse_decimal(&num, ptr, 2);
		ptr += 2;
		parse_float(&temp, ptr, 7);  //minutes
		ptr += 7;
		temp /= 60;
		gps_info_ptr->latitude = (float)num + temp;
	}

	/* 3.  N/S indicator */
	if(*++ptr != ',')
	{
		gps_info_ptr->noth_south = *ptr;
		ptr++;
	}

	/* 4. Longitude */
	if(*++ptr != ',')
	{
		parse_decimal(&num, ptr, 3);
		ptr += 3;
		parse_float(&temp, ptr, 7); //minutes
		ptr += 7;
		temp /= 60;
		gps_info_ptr->longitude = (float)num + temp;
	}

	/* 5. E/W indicator */
	if(*++ptr != ',')
	{
		gps_info_ptr->east_west = *ptr;
		ptr++;
	}

	/* 6 .Fix indicator */
	if(*++ptr != ',')
	{
		switch(*ptr)
		{
			case '0' : gps_info_ptr->fix = NO_FIX; break;
			case '1' : gps_info_ptr->fix = GPS_FIX; break;
			case '2' : gps_info_ptr->fix = DGPS_FIX; break;
			default	 : gps_info_ptr->fix = NO_FIX; break;
		}
		ptr++;
	}

	/* 7. Satellites used */
	if(*++ptr != ',')
	{
		num = (',' == *(ptr+1)) ? 1 : 2;
		parse_decimal(&gps_info_ptr->sat_used, ptr, num);
		ptr += num;
	}

	/* 8. HDOP */
	if(*++ptr != ',')
	{
		num = 0;
		while(ptr[num] != ',')
		{
			num++;
		}

		parse_float(&gps_info_ptr->hdop, ptr, num);
		ptr += num;
	}

	/* 9. Altitude */
	if(*++ptr != ',')
	{
		num = 0;
		while(ptr[num] != ',')
		{
			num++;
		}

		parse_float(&temp, ptr, num);
		gps_info_ptr->altitude = (int)temp;
		ptr += num;
	}

	return 0;
}

/* Parse a RMC sentence (only get date, speed and course, other parameters are obtained from GPGGA) */
int gps_parse_rmc(const char *buf, gps_info_struct_ptr gps_info_ptr)
{
	int num;
	char *ptr;
	float temp;

	/* Skip first six fields */
	num = 0;
	ptr = (char *)buf;
	while(num < 6)
	{
		if(',' == *ptr)
		{
			num++;
		}
		ptr++;
	}

	/* Speed */
	if(*ptr != ',')
	{

		num = 0;
		while(ptr[num] != ',')
		{
			num++;
		}

		parse_float(&temp, ptr, num);
		gps_info_ptr->velocity = (int)(temp * 1.852);  // convert knots to kph
		ptr += num;
	}

	/* Course */
	if(*++ptr != ',')
	{
		num = 0;
		while(ptr[num] != ',')
		{
			num++;
		}

		parse_float(&temp, ptr, num);
		gps_info_ptr->course = (int)temp;
		ptr += num;
	}

	/* Date */
	if(*++ptr != ',')
	{
		parse_decimal(&num, ptr, 2);
		gps_info_ptr->time.date = num;
		ptr += 2;
		parse_decimal(&num, ptr, 2);
		gps_info_ptr->time.month = num;
		ptr += 2;
		parse_decimal(&num, ptr, 2);
		gps_info_ptr->time.year = num;
	}

	return 0;
}
