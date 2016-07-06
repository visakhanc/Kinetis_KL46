/*
 * common.h
 *
 *  Created on: Apr 19, 2016
 *      Author: Visakhan
 */

#include "config_private.h"

#define GPS_UART_BASE 		UART1
#define GPS_UART_BAUDRATE	9600
#define GPS_UART_SRCCLK		CLOCK_GetBusClkFreq()

#define GSM_UART_BASE		UART2
#define GSM_UART_BAUDRATE	9600
#define GSM_UART_SRCCLK		CLOCK_GetBusClkFreq()

/* User button pin definition */
#define SW1_PORT 	PORTC
#define SW1_PIN		3

#define SW3_PORT	PORTC
#define SW3_PIN		12

/* Error enumerations */
enum error_nums {
	/* Driver errors */
	ERR_UART_SENDBLOCKING = 0x1,

	/* OS errors */
	ERR_TASK_CREATION = 0x1001,

	/* GSM errors */
	ERR_GSM_SMS_FAILED = 0x2001,
	ERR_GSM_SMS_TIMOUT,
	ERR_GSM_SMS_LONGADDR,
	ERR_GSM_SMS_CSCS,
	ERR_GSM_SMS_CMGF,
	ERR_GSM_SMS_LONGMSG,
	ERR_GSM_SMS_BADSTRING,

	/* HTTP related errors */
	ERR_HTTP_LOOKUP_FAILED = 0x3001,
	ERR_HTTP_MAX_URL,
	ERR_HTTP_CID_ERROR,
	ERR_HTTP_CID_TIMOUT,
	ERR_HTTP_URL_ERROR,
	ERR_HTTP_URL_TIMOUT,
	ERR_HTTP_ACTION_ERROR,
	ERR_HTTP_ACTION_TIMOUT,
	ERR_HTTP_GET_ERROR,
	ERR_HTTP_GET_TIMEOUT,
	ERR_HTTP_CGATT_ERR,
	ERR_HTTP_CONTYPE_ERR,
	ERR_HTTP_APN_ERR,
	ERR_HTTP_CONTEXT_ERR,
	ERR_HTTP_CONTEXT_TIMEOUT,
	ERR_HTTP_INIT_ERR,
	ERR_HTTP_INIT_TIMEOUT,
	ERR_HTTP_READ_ERROR,

};
