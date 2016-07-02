/*
 * pin_interrupts.c
 *
 *	Handles interrupts generated from push buttons
 *
 *  Created on: Jun 18, 2016
 *      Author: Visakhan
 */

#include "board.h"
#include "common.h"
#include "fsl_port.h"

extern void log_task_switch(void);


/* IRQ Handler for user switches */
void PORTC_PORTD_IRQHandler(void)
{
	uint32_t flags;

	/* Get interrupt flags (both buttons are on same port) */
	flags = PORT_GetPinsInterruptFlags(SW1_PORT);

	/* SW1 caused interrupt? */
	if(flags & (1 << SW3_PIN)) {
		//log_task_switch();
		//LED_GREEN_TOGGLE();
	}

	/* SW3 caused interrupt? */
	if(flags & (1 << SW1_PIN)) {
		//LED_RED_TOGGLE();
	}

	/* Clear interrupt flags for both SW1 and SW3 */
	PORT_ClearPinsInterruptFlags(SW1_PORT, (1 << SW3_PIN)|(1 << SW1_PIN));
}




