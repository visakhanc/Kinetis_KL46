/*
 * http_utils.c
 *
 *  Created on: Jul 11, 2015
 *      Author: Visakhan
 */

#include <stdio.h>
#include <string.h>
#include "gsm_common.h"
#include "fsl_debug_console.h"

#define URL_MAX_SIZE  170
char url_cmd_buf[200];
extern char http_buf[];

/* Description 	:	Use SIM900 HTTP GET feature to send GET request to given URL
 * Arguments 	: 	url - Null terminated URL string
 * Returns 		: 	0 - HTTP GET status code 200 (OK) received
 * 					-1 - Any error
 * Note			:	Received response is not read from SIM900 module.
 * 					This has to be done seperately, using other functions
 */
int http_get(const char *url)
{
	int ret = 0;
	uint32_t result;
	event_flags_t res_event;

	if(strlen(url) > URL_MAX_SIZE)
	{
		debug_printf("\n\rMax url error");
		return -1;
	}

	if(0 == ret) {
		gsm_send_command("AT+HTTPPARA=\"CID\",1");
		result = OSA_EventWait(&gsm_event, EVENT_GSM_OK|EVENT_GSM_ERROR, false, 2*1000, &res_event);
		if(kStatus_OSA_Success == result) {
			if(res_event & EVENT_GSM_ERROR) {
				debug_printf("\n\rCID error");
				ret = -1;
			}
		}
		else {
			ret = -1;
			debug_printf("\n\rCID error");
		}
	}

	if(0 == ret) {
		strcpy(url_cmd_buf, "AT+HTTPPARA=\"URL\",\"");
		strcat(url_cmd_buf, url);
		strcat(url_cmd_buf, "\"");
		//http://maps.googleapis.com/maps/api/geocode/json?latlng=12.92736,77.60729"12.927281,77.607330

		gsm_send_command(url_cmd_buf);
		result = OSA_EventWait(&gsm_event, EVENT_GSM_OK|EVENT_GSM_ERROR, false, 4*1000, &res_event);
		if(kStatus_OSA_Success == result) {
			if(res_event & EVENT_GSM_ERROR) {
				debug_printf("\n\rURL error");
				debug_printf("\n\r%s", url_cmd_buf);
				ret = -1;
			}
		}
		else {
				debug_printf("\n\rURL timeout");
				ret = -1;
		}
	}

	if(0 == ret) {
		debug_printf("\n\rread http");
		gsm_send_command("AT+HTTPACTION=0");
		result = OSA_EventWait(&gsm_event, EVENT_GSM_OK|EVENT_GSM_ERROR, false, 2*1000, &res_event);
		if(kStatus_OSA_Success == result) {
			if(res_event & EVENT_GSM_ERROR) {
				debug_printf("\n\rAction error");
				ret = -1;
			}
		}
		else {
			debug_printf("\n\rAction timeout");
			ret = -1;
		}
	}

	if(0 == ret) {
		result = OSA_EventWait(&gsm_event, EVENT_GSM_HTTPACTION, false, 30*1000, &res_event);
		if(kStatus_OSA_Success == result) {
			if(200 == gsm_status.http_status)
			{
				debug_printf("\n\rGET ok: revd %d bytes", gsm_status.http_recv_len);
			}
			else {
				debug_printf("\n\rGET error: %d", gsm_status.http_status);
				ret = -1;
			}
		}
		else {
			debug_printf("\n\rGET timeout");
			ret = -1;
		}
	}

	/*
	if(0 == ret) {
		gsm_send_command("AT+HTTPREAD=0,100");
		result = _lwevent_wait_ticks(&gsm_event, EVENT_GSM_HTTPREAD, false, 2*BSP_ALARM_FREQUENCY);
		if(MQX_OK != result)
		{
			ret = -1;
			debug_printf("\nRead error");
		}
		else {

			result = 0;
			while(result < 100)
			{
				putchar(http_buf[result++]);
			}
		}
	}
	*/

	/* Page read successfully */
	return ret;
}


int http_open_context(void)
{

	uint32_t result;
	event_flags_t res_event;

	/* GPRS attach */
	gsm_send_command("AT+CGATT=1");
	result = OSA_EventWait(&gsm_event, EVENT_GSM_OK|EVENT_GSM_ERROR, false, 2*1000, &res_event);
	if(kStatus_OSA_Success != result) {
		debug_printf("\n\rCGATT error");
		return -1;
	}

	gsm_send_command("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
	result = OSA_EventWait(&gsm_event, EVENT_GSM_OK|EVENT_GSM_ERROR, false, 2*1000, &res_event);
	if(kStatus_OSA_Success != result) {
		debug_printf("\n\rCONTYPE error");
		return -1;
	}

	gsm_send_command("AT+SAPBR=3,1,\"APN\",\"www\"");
	result = OSA_EventWait(&gsm_event, EVENT_GSM_OK|EVENT_GSM_ERROR, false, 2*1000, &res_event);
	if(kStatus_OSA_Success != result) {
		debug_printf("\n\rAPN error");
		return -1;
	}

	/* query gprs context */
	gsm_send_command("AT+SAPBR=2,1");
	result = OSA_EventWait(&gsm_event, EVENT_GSM_OK|EVENT_GSM_ERROR, false, 2*1000, &res_event);
	if(kStatus_OSA_Success == result) {
		if(true == gsm_status.gprs_context)
		{
			debug_printf("\n\rUsing already context");
		}
		else {
			debug_printf("\n\ropening context");

			/* open gprs context */
			gsm_send_command("AT+SAPBR=1,1");
			result = OSA_EventWait(&gsm_event, EVENT_GSM_OK|EVENT_GSM_ERROR, false, 15*1000, &res_event);
			if(kStatus_OSA_Success != result) {
				debug_printf("\n\rgprs open timeout");
				return -1;
			}
			else {
				if(res_event & EVENT_GSM_ERROR)
				{
					debug_printf("\n\rgprs open error");
					return -1;
				}
			}
		}
	}
	else {
		debug_printf("\n\rquery timout");
		return -1;
	}

	debug_printf("\n\rgprs opened");

	return 0;
}


int http_close_context(void)
{
	uint32_t result;
	event_flags_t res_event;

	/* close gprs context */
	gsm_send_command("AT+SAPBR=0,1");
	result = OSA_EventWait(&gsm_event, EVENT_GSM_OK|EVENT_GSM_ERROR, false, 2*1000, &res_event);
	if(kStatus_OSA_Success == result) {
		if(res_event & EVENT_GSM_ERROR)
		{
			debug_printf("\n\rgprs close error");
			return -1;
		}
	}

	return 0;
}


int http_init(void)
{
	int ret = 0;
	uint32_t result;
	event_flags_t res_event;

	gsm_send_command("AT+HTTPINIT");
	result = OSA_EventWait(&gsm_event, EVENT_GSM_OK|EVENT_GSM_ERROR, false, 2*1000, &res_event);
	if(kStatus_OSA_Success == result) {
		if(res_event & EVENT_GSM_ERROR) {
			debug_printf("\n\rHTTPINIT error");
			ret = -1;
		}
	}
	else {
		debug_printf("\n\rhttp init timeout");
		ret = -1;
	}

	return ret;
}


int http_terminate(void)
{
	uint32_t result;
	event_flags_t res_event;

	/* close HTTP */
	gsm_send_command("AT+HTTPTERM");
	if(kStatus_OSA_Success == OSA_EventWait(&gsm_event, EVENT_GSM_OK|EVENT_GSM_ERROR, false, 1000, &res_event))
	{
		if(res_event & EVENT_GSM_ERROR)
		{
			debug_printf("\n\rhttp close error");
			return -1;
		}
	}

	return 0;
}


/* Read 'size' bytes from the currently received http page at 'offset' bytes
 * from SIM900 internal buffer, into the given buffer */
int http_read(uint8_t *buf, int offset, int size)
{
	uint32_t result;
	event_flags_t res_event;
	char cmd[25];

	if(size > HTTP_BUF_SIZE) {
		return -1;
	}

	snprintf(cmd, sizeof(cmd), "AT+HTTPREAD=%d,%d", offset, size);
	gsm_send_command(cmd);
	result = OSA_EventWait(&gsm_event, EVENT_GSM_HTTPREAD|EVENT_GSM_ERROR, false, 2*1000, &res_event);
	if(kStatus_OSA_Success != result)
	{
		debug_printf("\n\rRead error");
		return -1;
	}
	else {
		memcpy(buf, http_buf, size);
	}

	OSA_EventWait(&gsm_event, EVENT_GSM_OK, false, 1000, &res_event);

	return 0;
}


/* Look for the given string in the received HTTP page in SIM900 internal buffer
 * If found, 'page_buf is filled with content from the received page, starting with
 * given string upto either end of the page or the size of 'page_buf' ('bufsize')
 */
int http_find_string(const char* str, char *page_buf, int bufsize)
{
	int total_size = gsm_status.http_recv_len;
	int get_size = bufsize - 1;
	int page_offset = 0;
	int i;
	char *ptr, *temp;

	do {

		if(total_size < get_size) {
			get_size = total_size;
		}

		/* get some chars */
		http_read(&page_buf[bufsize - get_size - 1], page_offset, get_size);
		page_buf[bufsize-1] = '\0';
		page_offset += get_size;
		total_size -= get_size;

		/* search for it */
		ptr = strstr(page_buf, str);

		/* found! copy all chars in buffer starting at search string */
		if(NULL != ptr)
		{
			i = 0;
			while(ptr[i] != '\0') {
				page_buf[i] = ptr[i];
				i++;
			}

			/* copy more characters to fill the buffer */
			get_size = (total_size < (bufsize - i)) ? total_size : (bufsize - i);
			http_read(&page_buf[i], page_offset, get_size-1);

			page_buf[i+get_size] = '\0';
			return 0;
		}

		/* move the last few characters in the buffer to start of buffer */
		strncpy(page_buf, &page_buf[bufsize - strlen(str) - 1], strlen(str));

		/* continue searching */
		get_size = bufsize - strlen(str) - 1;

	} while (total_size > 0);

	return -1;
}


