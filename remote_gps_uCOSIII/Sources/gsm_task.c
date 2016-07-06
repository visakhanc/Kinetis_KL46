/*
 * gsm_task.c
 *
 *  Created on: Jul 5, 2015
 *      Author: Visakhan
 */

#include <stdio.h>
#include "gsm_common.h"
#include "string.h"
#include "fsl_uart_driver.h"
#include "fsl_debug_console.h"
#include "common.h"
#include "gps_parse.h"
#include "num_utils.h"
#include "board.h"

#define GSM_DEBUG 0

extern void UART2_IRQHandler(void);
extern int message_update_gpsdata(void);
extern int message_update_location(int offset);
extern int message_update_error(const char *err, int len);
extern int gsm_send_command(const char *cmd);
extern void print_tx_data(void);
extern int gsm_send_sms(const uint8_t *buf, int length, const char *address);
extern int http_get(const char *url);
extern int http_find_string(const char* str, char *page_buf, int bufsize);

static void gsm_uart_rx_handler(uint32_t instance, void *state);

static char maps_api_url[100] = "http://maps.googleapis.com/maps/api/geocode/json?latlng=12.92736,77.60729";
#define URL_OFFSET  56

extern gps_info_struct gps_info;
event_t gsm_event;
gsm_status_struct gsm_status;
char http_buf[HTTP_BUF_SIZE];
char page_buf[256];
float cur_lat, cur_lon;

static volatile bool http_buf_switch = false;
static volatile int http_buf_count;
static uart_state_t gsm_uart_state;
static semaphore_t gsm_rx_sem, gsm_tx_sem;
static uint8_t gsm_rx_isr_buf[2], gsm_rx_buf[100], gsm_tx_buf[200];
static int gsm_rx_len;

static const uart_user_config_t gsm_uart_config = {
													.baudRate = 9600,
													.bitCountPerChar = kUart8BitsPerChar,
													.parityMode = kUartParityDisabled,
													.stopBitCount = kUartOneStopBit };

/*
 *  Initialize GSM
 *
 *  Initializes UART driver for GSM
 */
int gsm_init(void)
{
	int ret = 0;

	/* Pin muxing of UART */
	configure_uart_pins(GSM_UART);

	/* Install IRQ handler for UART */
	OSA_InstallIntHandler(UART2_IRQn, UART2_IRQHandler);

	/* Create semaphore for synchronization between UART Rx handler and GSM task */
	if (OSA_SemaCreate(&gsm_rx_sem, 0) != kStatus_OSA_Success) {
		ret = 1;
	}

	/* Create semaphore for GSM UART Tx */
	if (OSA_SemaCreate(&gsm_tx_sem, 1) != kStatus_OSA_Success) {
		ret = 1;
	}

	/* Create Event for communicating various responses */
	if (OSA_EventCreate(&gsm_event, kEventAutoClear) != kStatus_OSA_Success) {
		ret = 1;
	}

	/* Initialize UART driver with given parameters */
	if (UART_DRV_Init(GSM_UART, &gsm_uart_state, &gsm_uart_config) != kStatus_UART_Success) {
		ret = 1;
	}

#if !GSM_DEBUG
	/* Install our own handler for UART Rx data, which is called by the ISR; This also enables UART Rx interrupt  */
	UART_DRV_InstallRxCallback(GSM_UART, gsm_uart_rx_handler, gsm_rx_isr_buf, NULL, true);
#endif

	return ret;
}

#if GSM_DEBUG

/*TASK*-----------------------------------------------------
 *
 * Task Name    : gsm_task
 * Comments     :
 *
 *
 *END*-----------------------------------------------------*/
void control_task(void *pArg)
{

	uint32_t len, i;
	char text[100];

	if(0 != gsm_init()) {
		debug_printf("\r\ngsm_init error");
	}
	debug_printf("\r\ngsm_term_tx_task");

	while(1)
	{
		/* Get input from debug port and send to SIM900 */
		debug_printf("\r\nSIM900>");
		i = 0;
		while(i < sizeof(text)) {
			text[i] = debug_getchar();
			debug_putchar(text[i]);
			if((text[i] == '\r') || (text[i] == '\n')) {
				text[i] = '\r';
				debug_putchar('\n');
				break;
			}
			i++;
		}

		len = i+1;
		UART_DRV_SendDataBlocking(GSM_UART, text, len, OSA_WAIT_FOREVER);
	}

}

void gsm_rx_task(void *pArg)
{

	char rx;

	OSA_TimeDelay(1000);

	debug_printf("\r\ngsm_term_rx_task");
	while(1)
	{
		/* Receive reply */
		if(kStatus_UART_Success == UART_DRV_ReceiveDataBlocking(GSM_UART, &rx, 1, OSA_WAIT_FOREVER))
		{
			debug_putchar(rx);
		}
	}
}
#endif

int gsm_send_command(const char *cmd)
{
	int result = 0;

	if (kStatus_OSA_Success != OSA_SemaWait(&gsm_tx_sem, OSA_WAIT_FOREVER)) {
		debug_printf("gsm_tx_sem error");
		result = -1;
	}
	else {
		if (kStatus_UART_Success != UART_DRV_SendDataBlocking(GSM_UART, cmd, strlen(cmd), 100)) {
			result = -1;
		}

		if (kStatus_UART_Success != UART_DRV_SendDataBlocking(GSM_UART, "\r\n", 2, 100)) {
			result = -1;
		}

		if (kStatus_OSA_Success != OSA_SemaPost(&gsm_tx_sem)) {
			debug_printf("gsm_tx_sem error");
			result = -1;
		}
	}

	return result;
}

int gsm_send_sms(const uint8_t *buf, int length, const char *address)
{
	int ret = 0;
	uint32_t result, tx_timeout = 1000;
	event_flags_t res_event;
	uint8_t ctrl_z = 0x1A;
	uint8_t sms_buf[25];

	/* > Message content */
	if (length > 160) {
		debug_printf("\nSMS too long");
		return -1;
	}

	if (buf[length] != '\0') {
		debug_printf("\nSMS not proper string");
		return -1;
	}

	/* Set text mode */
	gsm_send_command("AT+CMGF=1");
	result = OSA_EventWait(&gsm_event, EVENT_GSM_OK | EVENT_GSM_ERROR, false, 1000, &res_event);
	if (res_event & EVENT_GSM_ERROR) {
		debug_printf("\n\rerr:CMGF");
		return -1;
	}

	/* Set GSM character set */
	gsm_send_command("AT+CSCS=\"GSM\"");
	result = OSA_EventWait(&gsm_event, EVENT_GSM_OK | EVENT_GSM_ERROR, false, 1000, &res_event);
	if (res_event & EVENT_GSM_ERROR) {
		debug_printf("\n\rerr:CSCS");
		return -1;
	}

	/* Check size of address */
	if (strlen(address) > 15) {
		debug_printf("\naddress too long");
		return -1;
	}

	/* Message address */
	snprintf(sms_buf, sizeof(sms_buf) - 1, "AT+CMGS=\"%s\"", address);
	gsm_send_command(sms_buf);
	OSA_TimeDelay(1000); /* Wait for prompt '>' */

	/* Send message */
	OSA_SemaWait(&gsm_tx_sem, OSA_WAIT_FOREVER);
	if (kStatus_UART_Success != UART_DRV_SendDataBlocking(GSM_UART, buf, length, tx_timeout)) {
		ret = -1;
	}

	if (kStatus_UART_Success != UART_DRV_SendDataBlocking(GSM_UART, &ctrl_z, 1, tx_timeout)) {
		ret = -1;
	}

	OSA_SemaPost(&gsm_tx_sem);

	/* Wait for OK */
	result = OSA_EventWait(&gsm_event, EVENT_GSM_OK | EVENT_GSM_ERROR, false, 20 * 1000, &res_event);
	if (kStatus_OSA_Success != result) {
		debug_printf("\r\nSMS send timeout? (%08x)", result);
		debug_printf("\r\n%s", gsm_rx_buf);
		ret = -1;
	}
	else {
		if (res_event & EVENT_GSM_ERROR) {
			debug_printf("\r\nSMS send error");
			ret = -1;
		}
	}

	return ret;
}

#if !GSM_DEBUG
void control_task(void *pArg)
{
	uint32_t result;
	uint32_t len, i;
	event_flags_t res_event;

	OSA_TimeDelay(2000);

	do {
		gsm_send_command("AT");
		result = OSA_EventWait(&gsm_event, EVENT_GSM_OK, false, 1000, &res_event);
	} while (result != kStatus_OSA_Success);

	gsm_send_command("ATE0");
	result = OSA_EventWait(&gsm_event, EVENT_GSM_OK, false, 1000, &res_event);

	/* Registration complete? */
	do {
		gsm_send_command("AT+CREG?");
		result = OSA_EventWait(&gsm_event, EVENT_GSM_CREG, false, 1000, &res_event);
	} while (result != kStatus_OSA_Success);

	debug_printf("\nRegistered\r\n");

	/* Enable CLIP */
	gsm_send_command("AT+CLIP=1");
	OSA_EventWait(&gsm_event, EVENT_GSM_OK, false, 1000, &res_event);

	while (1) {
		/* Waiting for the call */
		if (kStatus_OSA_Success == OSA_EventWait(&gsm_event, EVENT_GSM_RING, false, OSA_WAIT_FOREVER, &res_event)) {
			if (kStatus_OSA_Success == OSA_EventWait(&gsm_event, EVENT_GSM_CLIP, false, 1000, &res_event)) {
				debug_printf("\nCall from %s\r\n", gsm_status.caller);

				/* Disconnect call */
				gsm_send_command("ATH");

				if (0 != strcmp(gsm_status.caller, "+919961601261")) {
					continue;
				}

				// Convert to +/- according to N/S
				cur_lat = gps_info.latitude;
				cur_lon = gps_info.longitude;
				len = float_to_string(&cur_lat, 6, &maps_api_url[URL_OFFSET]);
				maps_api_url[URL_OFFSET + len] = ',';
				len++;
				float_to_string(&cur_lon, 6, &maps_api_url[URL_OFFSET + len]);

				/* Update message text with gps data */
				len = message_update_gpsdata();

				/* Lookup reverse geocoding url only if resonably accurate */
				if ((gps_info.fix > NO_FIX) && (gps_info.hdop < 2.0)) {
					if (0 == http_open_context()) {
						if (0 == http_init()) {
							if (0 == http_get(maps_api_url)) {
								debug_printf("\nget success: %d\r\n", gsm_status.http_recv_len);
								if (0 == http_find_string("formatted_address", page_buf, sizeof(page_buf))) {
									debug_printf("\nFound :)\n\r");
									len = message_update_location(len);
									debug_printf("%s", gsm_tx_buf);
									if (0 != gsm_send_sms(gsm_tx_buf, len, gsm_status.caller)) {
										debug_printf("\nSMS failed\r\n");
									}
								}
								else {
									debug_printf("\nNot found :(\n\r");
									debug_printf("\n%s\r\n", maps_api_url);
								}
							}
							else {
								debug_printf("\nLookup failed\n\r");
								/* update error detail in message and send message */
								len = message_update_error("Lookup failed\r\n", len);
								if (0 != gsm_send_sms(gsm_tx_buf, len, gsm_status.caller)) {
									debug_printf("\nSMS failed!\r\n");
								}
							}

							http_terminate();
						}

						http_close_context();

					}
				}
				else {
					debug_printf("\nSending message to %s...\n\r", gsm_status.caller);
					if (0 != gsm_send_sms(gsm_tx_buf, len, gsm_status.caller)) {
						debug_printf("\nSMS failed\r\n");
					}
				}

			}

		}

	}

}



void gsm_rx_task(void *pArg)
{
	char rx_buf[100];
	char *data_ptr;
	int len, temp;

	gsm_init();

	while (1) {
		/* Wait for signal from UART Rx handler */
		if (kStatus_OSA_Success == OSA_SemaWait(&gsm_rx_sem,
		OSA_WAIT_FOREVER)) {
			len = gsm_rx_len;
			memcpy((void *) rx_buf, (const void *) gsm_rx_buf, len);

			/* Response of 2 characters */
			if (2 == len) {
				if (0 == strcmp(gsm_rx_buf, "OK")) {
					OSA_EventSet(&gsm_event, EVENT_GSM_OK);
				}
			}
			else if (4 == len) {
				if (0 == strcmp(gsm_rx_buf, "RING")) {
					OSA_EventSet(&gsm_event, EVENT_GSM_RING);
				}
			}
			else if (5 == len) {
				if (0 == strcmp(gsm_rx_buf, "ERROR")) {
					OSA_EventSet(&gsm_event, EVENT_GSM_ERROR);
				}
			}
			else {
				if (NULL != strstr(gsm_rx_buf, "+CLIP")) {
					/* Get the caller number from CLIP line */
					len = get_quoted_string(&gsm_rx_buf[7], gsm_status.caller, sizeof(gsm_status.caller));
					if (len > 0) {
						OSA_EventSet(&gsm_event, EVENT_GSM_CLIP);
					}
				}

				if (NULL != strstr(gsm_rx_buf, "+CREG")) {
					/* Get and update registration status */
					if ((gsm_rx_buf[9] == '1') || (gsm_rx_buf[9] == '5')) {
						gsm_status.registerd = true;
						OSA_EventSet(&gsm_event, EVENT_GSM_CREG);
					}
					else {
						gsm_status.registerd = false;
					}
				}

				if (NULL != strstr(gsm_rx_buf, "+HTTPACTION")) {
					/* Get HTTP receive status and size of data received */
					parse_decimal(&temp, &gsm_rx_buf[14], 3);
					if (temp == 200) {
						parse_decimal(&gsm_status.http_recv_len, &gsm_rx_buf[18], 5);
					}
					gsm_status.http_status = temp;

					OSA_EventSet(&gsm_event, EVENT_GSM_HTTPACTION);
				}

				if (NULL != strstr(gsm_rx_buf, "+HTTPREAD")) {
					/* get number of bytes going to be received */
					parse_decimal(&temp, &gsm_rx_buf[10], 5);
					http_buf_count = temp;

					/* Tell UART Rx handler to receive characters to http buffer */
					http_buf_switch = true;
				}

				if (NULL != strstr(gsm_rx_buf, "+SAPBR")) {
					if (gsm_rx_buf[10] == '3') {
						gsm_status.gprs_context = false;
					}
					else if (gsm_rx_buf[10] == '1') {
						gsm_status.gprs_context = true;
					}
				}

			}

		}

	}

}


/*
 * 	UART Rx handler for GSM UART
 *
 * 	Puts character into a buffer, until CR-LF termination is recieved and signals the gsm_rx_task .
 *
 *  Note: This is called from within the UART RX ISR
 */
static void gsm_uart_rx_handler(uint32_t instance, void *state)
{
	static int buf_n;
	static int http_n;
	static uint8_t prev_ch;
	uart_state_t * u_state = (uart_state_t *) state;
	uint8_t ch;

	ch = *(u_state->rxBuff);

	if (false == http_buf_switch) {
		if(buf_n < sizeof(gsm_rx_buf)) {
			gsm_rx_buf[buf_n++] = ch;
			if (('\n' == ch) && ('\r' == prev_ch)) {
				gsm_rx_len = buf_n - 2;
				gsm_rx_buf[gsm_rx_len] = '\0';
				buf_n = 0;

				/* If only more than CR-LF */
				if (gsm_rx_len > 0) {
					OSA_SemaPost(&gsm_rx_sem);
				}
			}
			prev_ch = ch;
		}
	}
	else {
		if (http_n < sizeof(http_buf)) {
			/* Receive data into http buffer */
			http_buf[http_n++] = ch;
			if (http_n >= http_buf_count) {
				OSA_EventSet(&gsm_event, EVENT_GSM_HTTPREAD);
				http_buf_switch = false;
				http_n = 0;
			}
		}
	}
}
#endif

int message_update_gpsdata(void)
{
	int offset = 0;
	uint8_t str[16];

	offset = sprintf(&gsm_tx_buf[offset], "LatLon:");
	float_to_string(&cur_lat, 6, str);
	offset += sprintf(&gsm_tx_buf[offset], "%s,", str);
	float_to_string(&cur_lon, 6, str);
	offset += sprintf(&gsm_tx_buf[offset], "%s\r\n", str);
	offset += sprintf(&gsm_tx_buf[offset], "Dir:%d deg\r\n", gps_info.course);
	offset += sprintf(&gsm_tx_buf[offset], "Speed:%d kph\r\n", gps_info.velocity);
	offset += sprintf(&gsm_tx_buf[offset], "HDOP:%d\r\n", (int) (gps_info.hdop * 10.0));

	return offset;
}

int message_update_location(int offset)
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


int message_update_error(const char *err, int len)
{
	int offset = len;
	offset += sprintf(&gsm_tx_buf[len], "%s", err);
	return offset;
}


void print_tx_data(void)
{
	debug_printf("\n\r");
	debug_printf("%s", gsm_tx_buf);
	debug_printf("\n\r");
}
