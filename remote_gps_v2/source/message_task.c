/*
 * message_task.c
 *
 *	This task is responsible for reporting details of current location by
 *	sending SMS message to the user, whenever requested
 *
 *  Created on: Jun 17, 2016
 *      Author: Visakhan
 */

#include "gsm_common.h"
#include "http_utils.h"
#include "num_utils.h"
#include "gps_parse.h"
#include "fsl_debug_console.h"

static int message_update_gpsdata(void);
static int message_update_location(int offset);
static int message_update_error(const char *err, int len);
static void print_tx_data(void);


/* Globals */
extern gps_info_struct gps_info;
extern gsm_status_struct gsm_status;

static float cur_lat;
static float cur_lon;
static char page_buf[256];
static uint8_t gsm_tx_buf[200];
static char maps_api_url[100] = "http://maps.googleapis.com/maps/api/geocode/json?latlng=12.92736,77.60729";
#define URL_OFFSET  56


void message_task(void *pArg)
{
	uint32_t len;
	EventBits_t ev;

	vTaskDelay(1000);

	/* Get access to GSM UART */
	if(gsm_uart_acquire() != 0) {
		PRINTF("\r\nError: gsm_uart_acquire()");
	}

	do {
		gsm_send_command("AT");
		ev = gsm_wait_for_event(EVENT_GSM_OK, 1000); // TODO: change to 100 ticks
	} while (!(ev & EVENT_GSM_OK));

	/* Disable AT echo */
	gsm_send_command("ATE0");
	ev = gsm_wait_for_event(EVENT_GSM_OK, 1000);

	/* Registration complete? */
	do {
		gsm_send_command("AT+CREG?");
		ev = gsm_wait_for_event(EVENT_GSM_OK, 1000);
	} while (!(ev & EVENT_GSM_CREG));

	PRINTF("\nRegistered\r\n");

	/* Enable CLIP */
	gsm_send_command("AT+CLIP=1");
	ev = gsm_wait_for_event(EVENT_GSM_OK, 1000);

	/* Release GSM UART */
	gsm_uart_release();

	while (1) {
		/* Waiting for the call */
		ev = gsm_wait_for_event(EVENT_GSM_RING, 0);
		if(ev & EVENT_GSM_RING) {

			ev = gsm_wait_for_event(EVENT_GSM_CLIP, 1000);
			if (ev & EVENT_GSM_CLIP) {
				PRINTF("\nCall from %s\r\n", gsm_status.caller);

				/* Get access to GSM UART */
				if(gsm_uart_acquire() != 0) {
					PRINTF("\r\ncontrol_task: gsm_uart_acquire() failed");
					/* Wait again for call */
					continue;
				}

				/* Disconnect call */
				gsm_send_command("ATH");

				/*  Ignore if number is not registered */
				if (0 != strcmp((char *)gsm_status.caller, "+919961601261")) {
					gsm_uart_release();
					continue;
				}

				// Convert to +/- according to N/S
				cur_lat = gps_info.latitude;
				cur_lon = gps_info.longitude;
				len = float_to_string(&cur_lat, 6, (uint8_t *)&maps_api_url[URL_OFFSET]);
				maps_api_url[URL_OFFSET + len] = ',';
				len++;
				float_to_string(&cur_lon, 6, (uint8_t *)&maps_api_url[URL_OFFSET + len]);

				/* Update message text with gps data */
				len = message_update_gpsdata();

				/* Lookup reverse geocoding url only if resonably accurate */
				if ((gps_info.fix > NO_FIX) && (gps_info.hdop < 2.0)) {
					if (0 == http_open_context()) {
						if (0 == http_init()) {
							if (0 == http_get(maps_api_url)) {
								PRINTF("\nget success: %d\r\n", gsm_status.http_recv_len);
								if (0 == http_find_string("formatted_address", (uint8_t *)page_buf, sizeof(page_buf))) {
									PRINTF("\nFound :)\n\r");
									len = message_update_location(len);
									PRINTF("%s", gsm_tx_buf);
									if (0 != gsm_send_sms((char *)gsm_tx_buf, len, (char *)gsm_status.caller)) {
										PRINTF("\nSMS failed\r\n");
									}
								}
								else {
									PRINTF("\nNot found :(\n\r");
									PRINTF("\n%s\r\n", maps_api_url);
								}
							}
							else {
								PRINTF("\nLookup failed\n\r");
								/* update error detail in message and send message */
								len = message_update_error("Lookup failed\r\n", len);
								if (0 != gsm_send_sms((char *)gsm_tx_buf, len, (char *)gsm_status.caller)) {
									PRINTF("\nSMS failed!\r\n");
								}
							}

							http_terminate();
						}

						http_close_context();

					}
				}
				else {
					PRINTF("\nSending message to %s...\n\r", gsm_status.caller);
					if (0 != gsm_send_sms((char *)gsm_tx_buf, len, (char *)gsm_status.caller)) {
						PRINTF("\nSMS failed\r\n");
					}
				}

				/* Release GSM UART */
				gsm_uart_release();

			}

		}

	}

}




static int message_update_gpsdata(void)
{
	int offset = 0;
	uint8_t str[16];

	offset = sprintf((char *)&gsm_tx_buf[offset], "LatLon:");
	float_to_string(&cur_lat, 6, str);
	offset += sprintf((char *)&gsm_tx_buf[offset], "%s,", str);
	float_to_string(&cur_lon, 6, str);
	offset += sprintf((char *)&gsm_tx_buf[offset], "%s\r\n", str);
	offset += sprintf((char *)&gsm_tx_buf[offset], "Dir:%d deg\r\n", gps_info.course);
	offset += sprintf((char *)&gsm_tx_buf[offset], "Speed:%d kph\r\n", gps_info.velocity);
	offset += sprintf((char *)&gsm_tx_buf[offset], "HDOP:%d\r\n", (int) (gps_info.hdop * 10.0));

	return offset;
}

static int message_update_location(int offset)
{
	int components = 0;
	char *ptr = page_buf;

	while (*ptr != ':')
		ptr++;

	ptr += 3;
	while (components < 5) {
		gsm_tx_buf[offset++] = *ptr++;
		if (',' == *ptr) {
			components++;
		}

		if ('\"' == *ptr) {
			break;
		}
	}

	gsm_tx_buf[offset] = '\0';

	return offset;
}


static int message_update_error(const char *err, int len)
{
	int offset = len;
	offset += sprintf((char *)&gsm_tx_buf[len], "%s", err);
	return offset;
}


static void print_tx_data(void)
{
	PRINTF("\n\r");
	PRINTF("%s", gsm_tx_buf);
	PRINTF("\n\r");
}


