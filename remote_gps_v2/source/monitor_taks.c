/*
 * monitor_taks.c
 *
 *	This Task wsits for commands from remote user and controls other tasks
 *
 *  Created on: Jun 19, 2016
 *      Author: Visakhan
 */


#include "gsm_common.h"
#include "fsl_debug_console.h"

extern void log_task_switch(void);

void monitor_task(void *pvParameters)
{
	EventBits_t ev;
	while(1) {

		/* Wait for call to begin logging */
		ev = gsm_wait_for_event(EVENT_GSM_RING, 0);
		if(ev & EVENT_GSM_RING) {
			ev = gsm_wait_for_event(EVENT_GSM_CLIP, 1000);
			if (ev & EVENT_GSM_CLIP) {
				PRINTF("\r\nCall from %s", gsm_status.caller);

				/* Get access to GSM UART */
				//if(gsm_uart_acquire() == 0) { // TODO: Cannot acquire uart during HTTP GET session. User has to diconnect himself

					/* Disconnect call */
					gsm_send_command("ATH");
					gsm_wait_for_event(EVENT_GSM_OK, 500);
					
					/* Process only if number is registered */
					if (0 == strcmp((char *)gsm_status.caller, "+919961601261")) {
						/* Start/Stop logging */
						log_task_switch();
					}

					/* Release uart access */
					//if(gsm_uart_release() != 0) {
					//	PRINTF("\r\nmonitor: uart release failed");
					//}

				//}
				//else {
				//	PRINTF("\r\nmonitor: gsm_uart_acquire() failed");
				//}
			}
		}
	}
}

