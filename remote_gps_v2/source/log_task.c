/*
 * log_task.c
 *
 *	This task is responsible for, sending location data to a web server
 *	at regular intervals
 *
 *  Created on: Jun 17, 2016
 *      Author: Visakhan
 */


#include "gsm_common.h"
#include "http_utils.h"
#include "gps_parse.h"
#include "num_utils.h"
#include "fsl_debug_console.h"
#include "board.h"

/* Globals */
extern gps_info_struct gps_info;

static char log_api_url[150] = "embeddedworld.co.nf/save_loc.php?";
/* position in the URL to place parameters */
#define LOG_URL_OFFSET 33

void log_task(void *pvParameters)
{
	float cur_lat = 9.610436;
	float cur_lon = 76.606838;
	int vel = 14;

	int offset;


	do {
		/* Wait until GSM module get registered */
		vTaskDelay(1000);
	} while (gsm_status.registerd != true);

	while(1)
	{
//		if(gps_info.hdop < 2.0)
		if (1)
		{
			vTaskDelay(6000);

//			cur_lat = gps_info.latitude;
//			cur_lon = gps_info.longitude;
			cur_lat += 0.0009;
			cur_lon += 0.0009;
			vel++;

			offset = LOG_URL_OFFSET;
			offset += sprintf(&log_api_url[offset], "lat=");
			offset += float_to_string(&cur_lat, 6, (uint8_t *)&log_api_url[offset]);
			offset += sprintf(&log_api_url[offset], "&long=");
			offset += float_to_string(&cur_lon, 6, (uint8_t *)&log_api_url[offset]);
			offset += sprintf(&log_api_url[offset], "&speed=%d&dir=%d&hdop=%d", vel, gps_info.course, (int)gps_info.hdop*10);
			offset += sprintf(&log_api_url[offset], "&date=%d-%02d-%02d&time=%02d:%02d:%02d", gps_info.time.year+2000, gps_info.time.month, gps_info.time.date,
							  gps_info.time.hour, gps_info.time.min, gps_info.time.sec);

			PRINTF("\r\n%s", log_api_url);
			PRINTF("\r\nlen = %d", offset);
#if 1
			if(0 == http_open_context()) {
				if(0 == http_init()) {
					/* Send location to server using HTTP GET method */
					if(0 == http_get(log_api_url)) {
						PRINTF("\r\nlog: GET success (response: %d B )", gsm_status.http_recv_len);
						LED_RED_ON();
						vTaskDelay(100);
						LED_RED_OFF();
					}
					else {
						PRINTF("\r\nlog: GET failed");
						http_terminate(); // try closing the stack
					}
				}
				else {
					PRINTF("\r\nlog: http init error");
				}
			}
			else {
				PRINTF("\r\nlog: http_open_context error");
			}

			http_terminate();
#endif
		}

		vTaskDelay(1000);
	}

}
