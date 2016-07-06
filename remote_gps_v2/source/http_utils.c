/*
 * http_utils.c
 *
 *  Created on: Jul 11, 2015
 *      Author: Visakhan
 */

#include <stdio.h>
#include <string.h>
#include "http_utils.h"
#include "gsm_common.h"
#include "fsl_debug_console.h"


extern char http_buf[];

#define URL_MAX_SIZE  170
static char url_cmd_buf[200];
volatile static bool http_initialized = false;

/* Description 	:	Use SIM900 HTTP GET feature to send GET request to given URL
 * Arguments 	: 	url - Null terminated URL string
 * Returns 		: 	0 - HTTP GET status code 200 (OK) received
 * 					1 - Any error
 * Note			:	Received response is not read from SIM900 module.
 * 					This has to be done seperately, using other functions
 */
int http_get(const char *url)
{
	int ret = 0;
	EventBits_t ev;

	if(strlen(url) > URL_MAX_SIZE)
	{
		PRINTF("\n\rMax url error");
		return 1;
	}

	strcpy(url_cmd_buf, "AT+HTTPPARA=\"URL\",\"");
	strcat(url_cmd_buf, url);
	strcat(url_cmd_buf, "\"");

	gsm_send_command(url_cmd_buf);
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 4*1000);
	if(ev & EVENT_GSM_ERROR) {
		PRINTF("\n\rURL error");
		PRINTF("\n\r%s", url_cmd_buf);
		ret = 1;
	}
	else if(!(ev & EVENT_GSM_OK)){
		PRINTF("\n\rURL timeout");
		ret = 1;
	}

	if(0 == ret) {
		PRINTF("\n\rread http");
		gsm_send_command("AT+HTTPACTION=0");
		ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 2*1000);
		if(ev & EVENT_GSM_ERROR) {
			PRINTF("\n\rHTTPACTION error");
			ret = 1;
		}
		else if(!(ev & EVENT_GSM_OK)) {
			PRINTF("\n\rHTTPACTION timeout");
			ret = 1;
		}
	}

	if(0 == ret) {
		ev = gsm_wait_for_event(EVENT_GSM_HTTPACTION, 30*1000);
		if(ev & EVENT_GSM_HTTPACTION) {
			if(200 == gsm_status.http_status)
			{
				PRINTF("\n\rGET ok: %d bytes", gsm_status.http_recv_len);
			}
			else {
				PRINTF("\n\rGET error: %d", gsm_status.http_status);
				ret = 1;
			}
		}
		else {
			PRINTF("\n\rGET timeout");
			ret = 1;
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
	EventBits_t ev;


	/* query gprs context */
	gsm_send_command("AT+SAPBR=2,1");
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 2*1000);
	if(ev & EVENT_GSM_OK) {
		if(true == gsm_status.gprs_context)
		{
			PRINTF("\n\rUsing already context");
		}
		else {
			PRINTF("\n\ropening context");

			/* open gprs context */
			gsm_send_command("AT+SAPBR=1,1");
			ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 15*1000);
			if(ev & EVENT_GSM_ERROR) {
				PRINTF("\n\rgprs open error");
				return 1;
			}
			else if(!(ev & EVENT_GSM_OK)) {
				PRINTF("\n\rgprs open timeout");
				return 1;
			}
		}
	}
	else {
		PRINTF("\n\rquery error/timout");
		return 1;
	}

	PRINTF("\n\rgprs opened");
	return 0;
}


int http_close_context(void)
{
	EventBits_t ev;

	gsm_send_command("AT+SAPBR=2,1");
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 2*1000);
	if(ev & EVENT_GSM_OK) {
		if(true == gsm_status.gprs_context) {
			/* close gprs context */
			gsm_send_command("AT+SAPBR=0,1");
			ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 5*1000);
			if(ev & EVENT_GSM_ERROR)
			{
				PRINTF("\n\rgprs close error");
				return 1;
			}
			else if(!(ev & EVENT_GSM_OK)) {
				PRINTF("\r\ngprs close timeout");
				return 1;
			}
		}
	}
	else {
		PRINTF("\r\ngprs query error");
		return 1;
	}

	return 0;
}


int http_init(void)
{
	int ret = 0;
	EventBits_t ev;

	if(true == http_initialized) {
		return 0;
	}

	gsm_send_command("AT+HTTPINIT");
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 2*1000);
	if(ev & EVENT_GSM_ERROR) {
		PRINTF("\n\rHTTPINIT error");
		ret = 1;
	}
	else if(!(ev & EVENT_GSM_OK)) {
		PRINTF("\n\rhttp init timeout");
		ret = 1;
	}
	else {
		http_initialized = true;
	}

	/* Set context ID */
	gsm_send_command("AT+HTTPPARA=\"CID\",1");
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 2*1000);
	if(ev & EVENT_GSM_ERROR) {
		PRINTF("\n\rERROR: CID error");
		ret = 1;
	}
	else if(!(ev & EVENT_GSM_OK)) {
		ret = 1;
		PRINTF("\n\rERROR: CID timout");
	}

	return ret;
}


int http_terminate(void)
{
	int ret = 0;
	EventBits_t ev;

	if(false == http_initialized) {
		return 0;
	}

	/* close HTTP */
	gsm_send_command("AT+HTTPTERM");
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 2000);
	if(ev & EVENT_GSM_ERROR) {
		PRINTF("\n\rhttpterm error");
		ret = 1;
	}
	else if(!(ev & EVENT_GSM_OK)) {
		PRINTF("\r\nhttpterm timeout");
		ret = 1;
	}
	else {
		http_initialized = false;
	}

	return ret;
}


/* Read 'size' bytes from the currently received http page at 'offset' bytes
 * from SIM900 internal buffer, into the given buffer */
int http_read(uint8_t *buf, int offset, int size)
{
	EventBits_t ev;
	char cmd[25];

	if(size > HTTP_BUF_SIZE) {
		return 1;
	}

	snprintf(cmd, sizeof(cmd), "AT+HTTPREAD=%d,%d", offset, size);
	gsm_send_command(cmd);
	ev = gsm_wait_for_event(EVENT_GSM_HTTPREAD|EVENT_GSM_ERROR, 2*1000);
	if(!(ev & (EVENT_GSM_HTTPREAD|EVENT_GSM_ERROR)))
	{
		PRINTF("\n\rRead error");
		return 1;
	}
	else {
		memcpy(buf, http_buf, size);
	}

	gsm_wait_for_event(EVENT_GSM_OK, 1000);

	return 0;
}


/* Look for the given string in the received HTTP page in SIM900 internal buffer
 * If found, 'page_buf is filled with content from the received page, starting with
 * given string upto either end of the page or the size of page_buf ('bufsize')
 */
int http_find_string(const char* str, uint8_t *page_buf, int bufsize)
{
	int total_size = gsm_status.http_recv_len;
	int get_size = bufsize - 1;
	int page_offset = 0;
	int i;
	char *ptr;

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

/*
 * Configure GPRS for first time
 */
int gprs_configure(void)
{
	EventBits_t ev;

	/* GPRS attach */
	gsm_send_command("AT+CGATT=1");
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 2*1000);
	if(ev & EVENT_GSM_ERROR) {
		PRINTF("\n\rCGATT error");
		return 1;
	}
	else if(!(ev & EVENT_GSM_OK)) {
		PRINTF("\r\nCGATT timeout");
	}

	gsm_send_command("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 2*1000);
	if(ev & EVENT_GSM_ERROR) {
		PRINTF("\n\rCONTYPE error");
		return 1;
	}
	else if(!(ev & EVENT_GSM_OK)) {
		PRINTF("\r\nCONTYPE timeout");
	}

	gsm_send_command("AT+SAPBR=3,1,\"APN\",\"www\"");
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 2*1000);
	if(ev & EVENT_GSM_ERROR) {
		PRINTF("\n\rAPN error");
		return 1;
	}
	else if(!(ev & EVENT_GSM_OK)) {
		PRINTF("\n\rAPN timeout");
		return 1;
	}

	return 0;

}
