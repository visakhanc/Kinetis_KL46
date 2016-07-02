/*
 * gps_parse.h
 *
 *  Created on: Jun 27, 2015
 *      Author: Visakhan
 */

#include <stdint.h>
#include <stdbool.h>


#ifndef SOURCES_GPS_PARSE_H_
#define SOURCES_GPS_PARSE_H_

typedef struct _gps_time
{
	uint8_t date;
	uint8_t month;
	uint8_t year;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;

} gps_time_struct, *gps_time_struct_ptr;

typedef enum _gps_fix
{
	NO_FIX = 0,
	GPS_FIX = 1,
	DGPS_FIX = 2
} gps_fix_type;

typedef struct _gps_info
{
	/* Time */
	gps_time_struct time;

	/* Position */
	char noth_south;
	char east_west;
	float latitude;
	float longitude;

	/* Horizontal DOP */
	float hdop;

	/* Velocity (kph) */
	int velocity;

	/* Course (degrees) */
	int course;

	/* MSL Altitude (meters) */
	int altitude;

	/* fix type */
	gps_fix_type fix;

	/* used satellites */
	int sat_used;

} gps_info_struct, *gps_info_struct_ptr;



extern int gps_parse_gga(const char *buf, gps_info_struct_ptr gps_info_ptr);
extern int gps_parse_rmc(const char *buf, gps_info_struct_ptr gps_info_ptr);
extern void gps_time_to_ist(gps_time_struct *gps_time, gps_time_struct *ist_time);

#endif /* SOURCES_GPS_PARSE_H_ */
