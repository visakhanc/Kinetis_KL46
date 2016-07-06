/*
 * gsm_common.h
 *
 *  Created on: Jul 5, 2015
 *      Author: Visakhan
 */

#ifndef SOURCES_GSM_COMMON_H_
#define SOURCES_GSM_COMMON_H_

#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"

/* Define to 1 if GSM module need to be tested through command prompt */
#define GSM_DEBUG 0


#define HTTP_BUF_SIZE			256

/* Event flag bits */
#define EVENT_GSM_OK			(1 << 0)
#define EVENT_GSM_ERROR			(1 << 1)
#define EVENT_GSM_RING			(1 << 2)
#define EVENT_GSM_CLIP			(1 << 3)
#define EVENT_GSM_HTTPACTION	(1 << 4)
#define EVENT_GSM_HTTPREAD		(1 << 5)
#define EVENT_GSM_CMTI			(1 << 6)
#define EVENT_GSM_CREG			(1 << 7)
#define EVENT_GSM_CMGS			(1 << 8)
#define EVENT_GSM_CMGR			(1 << 9)


typedef struct _gsm_status
{
	volatile bool registerd;
	volatile bool gprs_context;
	//volatile int cid;
	volatile int http_status;
	volatile int http_recv_len;
	//volatile int http_read_count;
	uint8_t caller[15];
} gsm_status_struct, *gsm_status_struct_ptr;


/* Globals */
extern gsm_status_struct gsm_status;

extern int gsm_init(void);
extern int gsm_send_command(const char *cmd);
extern int gsm_uart_acquire(void);
extern int gsm_uart_release(void);
extern int gsm_uart_send(const char *data, uint32_t len);
extern uint32_t gsm_wait_for_event(uint32_t events, uint32_t delay_ticks);
extern int gsm_send_sms(const char *buf, int length, const char *address);

#endif /* SOURCES_GSM_COMMON_H_ */
