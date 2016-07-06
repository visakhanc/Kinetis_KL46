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

/* Macros */
#define EVENT_START_LOGGING  	(1 << 0)
#define EVENT_STOP_LOGGING		(1 << 1)

/* Globals */
extern gps_info_struct gps_info;

//static char log_api_url[150] = "embeddedworld.co.nf/save_loc.php?";
/* position in the URL to place parameters */
//#define LOG_URL_OFFSET 33

static char log_api_url[150] = "positioning.hol.es/save_loc.php?";
#define LOG_URL_OFFSET 32

static TaskHandle_t xLogTaskHandle;
volatile static bool logEnabled = false;

void log_task(void *pvParameters)
{
	float cur_lat = 9.620093;
	float cur_lon = 76.618476;
	int offset;
	volatile int count = 0;
	uint32_t notifValue = 0;
	uint8_t log_reply_buf[20];

	xLogTaskHandle = xTaskGetCurrentTaskHandle();
	do {
		/* Wait until GSM module get registered */
		vTaskDelay(1000);
	} while (gsm_status.registerd != true);

	while(1)
	{

		/* Wait for Notification to start/stop logging */
		if(pdTRUE == xTaskNotifyWait(0, -1UL, &notifValue, 6000)) {
			if(notifValue & EVENT_START_LOGGING) {
				PRINTF("\r\nLogging started");
				if(gprs_configure() != 0) {
					PRINTF("\r\nError: gprs_configure");
				}
			}
			if(notifValue & EVENT_STOP_LOGGING) {
				if(0 != gsm_uart_acquire()) { PRINTF("\r\nlog: uart acquire fail"); }
				// TODO: disable logging on server too?
				http_terminate();
				http_close_context();
				if(0 != gsm_uart_release()) { PRINTF("\r\nlog: uart release fail"); }
				PRINTF("\r\nLogging stopped");
			}
		}

		if((!count) || (true == logEnabled)) {

			/* Log only if position is reasonably accurate */
			if((gps_info.fix > NO_FIX) && (gps_info.hdop < 2.0)) {
				
				cur_lat = gps_info.latitude;
				cur_lon = gps_info.longitude;

				offset = LOG_URL_OFFSET;
				offset += sprintf(&log_api_url[offset], "lat=");
				offset += float_to_string(&cur_lat, 6, (uint8_t *)&log_api_url[offset]);
				offset += sprintf(&log_api_url[offset], "&long=");
				offset += float_to_string(&cur_lon, 6, (uint8_t *)&log_api_url[offset]);
				offset += sprintf(&log_api_url[offset], "&speed=%d&dir=%d&hdop=%d", gps_info.velocity, gps_info.course, (int)(gps_info.hdop*10.0));
				offset += sprintf(&log_api_url[offset], "&date=%d-%02d-%02d&time=%02d:%02d:%02d", gps_info.time.year+2000, gps_info.time.month, gps_info.time.date,
								  gps_info.time.hour, gps_info.time.min, gps_info.time.sec);

				PRINTF("\r\n%s", log_api_url);
				PRINTF("\r\nlen = %d", offset);
				
				/* acquire gsm uart */
				if(0 != gsm_uart_acquire()) { PRINTF("\r\nlog: uart acquire fail"); }

				if(0 == http_open_context()) {
					if(0 == http_init()) {
						/* Send location to server using HTTP GET method */
						if(0 == http_get(log_api_url)) {
							PRINTF("\r\nlog: GET success (response: %d B )", gsm_status.http_recv_len);
							LED_RED_ON();
							/* Read HTTP response */
							if(gsm_status.http_recv_len < sizeof(log_reply_buf)) {
								if(0 == http_read(log_reply_buf, 0, gsm_status.http_recv_len)) {
									log_reply_buf[gsm_status.http_recv_len] = '\0';
									/* Check whether to continue logging */
									if(strstr((char *)log_reply_buf, "Cont") != NULL) {
										logEnabled = true;
									}
									else {
										logEnabled = false;
										http_terminate();
										http_close_context();
									}
								}
							}
							vTaskDelay(100);
							LED_RED_OFF();

							//http_terminate();
							count++;
							PRINTF("Total: %d\r\n", count);
						}
						else {
							PRINTF("\r\nlog: GET failed");
							//http_terminate(); // try closing the stack
						}
					}
					else {
						PRINTF("\r\nlog: http init error");
					}

				}
				else {
					PRINTF("\r\nlog: http_open_context error");
				}

				/* Release gsm uart */
				if(0 != gsm_uart_release()) { PRINTF("\r\nlog: uart release fail"); }

			}

		}

	} /* while(1) */

}


/* Called externally to start/stop logging */
void log_task_switch(void)
{
	uint32_t	notifValue;

	if(true == logEnabled) {
		logEnabled = false;
		/* Set task notification value to stop logging */
		notifValue = EVENT_STOP_LOGGING;
	}
	else {
		logEnabled = true;
		/* Set task notification value to start logging */
		notifValue = EVENT_START_LOGGING;
	}

	xTaskNotify(xLogTaskHandle, notifValue, eSetBits);
}
