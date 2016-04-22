/*
 * gps_task.c
 *
 *  Created on: Jul 5, 2015
 *      Author: Visakhan
 */

#include <stdio.h>

#include "gps_parse.h"
#include "string.h"
#include "fsl_uart_driver.h"
#include "common.h"
#include "fsl_debug_console.h"
#include "fsl_os_abstraction.h"
#include "board.h"

extern void UART1_IRQHandler(void);
static void gps_uart_rx_handler(uint32_t instance, void *state);

static uint8_t 	gps_rx_buf[2], gps_rx_sentence[200];
static uint32_t	gps_rx_len;
static semaphore_t gps_task_sem;
gps_info_struct gps_info;
uart_state_t gps_uart_state;


const uart_user_config_t gps_uart_config =
{
	.baudRate = 9600,
	.bitCountPerChar = kUart8BitsPerChar,
	.parityMode = kUartParityDisabled,
	.stopBitCount = kUartOneStopBit
};


/*
 *  Initialize GPS
 *
 *  Initializes UART driver for GPS
 */
int gps_init(void)
{
	/* Pin muxing of UART */
	configure_uart_pins(GPS_UART);

	/* Install MQX IRQ handler for UART */
	OSA_InstallIntHandler(UART1_IRQn, UART1_IRQHandler);

	/* Create semaphore for synchronization between UART Rx handler and GPS task */
	OSA_SemaCreate(&gps_task_sem, 0);

	/* Initialize UART driver with given parameters */
	UART_DRV_Init(GPS_UART, &gps_uart_state, &gps_uart_config);

	/* Install our own handler for UART Rx data, which is called by the ISR */
	UART_DRV_InstallRxCallback(GPS_UART, gps_uart_rx_handler, gps_rx_buf, NULL, true);

	return 0;
}




/*TASK*-----------------------------------------------------
*
* Task Name    : gps_task
* Comments     :
*
*
*END*-----------------------------------------------------*/

void gps_task(void *pArg)
{

   char rx_sentence[200];
   char *data_ptr;
   uint32_t len;
   char c;

   debug_printf("from gps task...\r\n");

   /* Initialize GPS */
   gps_init();

   /* Turn on GREEN LED */
   //GPIO_DRV_ClearPinOutput(kGpioLED1);

   while(1)
   {

	   /* Wait for signal from UART Rx handler */
	   if(kStatus_OSA_Success == OSA_SemaWait(&gps_task_sem, OSA_WAIT_FOREVER))
	   {
		   /* Copy the received sentence */
		   len = gps_rx_len;
		   memcpy((void *)rx_sentence, (void *)gps_rx_sentence, len);

		   /* Parse the received sentence to update gps_info structure */
		   if(NULL != strstr(rx_sentence, "GPGGA"))
		   {
			   data_ptr = &rx_sentence[6];
			   gps_parse_gga(data_ptr, &gps_info);
		   }

		   if( (NULL != strstr(rx_sentence, "GPRMC")) || (NULL != strstr(rx_sentence, "GNRMC")) )
		   {
			   data_ptr = &rx_sentence[6];
			   gps_parse_rmc(data_ptr, &gps_info);
		   }
	   }


	   /* Check for GPS Fix */
	   if(NO_FIX != gps_info.fix)
	   {
		   /* Turn on GREEN LED */
		   GPIO_DRV_ClearPinOutput(kGpioLED1);
	   }
	   else
	   {
		   /* Turn off GREEN LED */
		   GPIO_DRV_SetPinOutput(kGpioLED1);
	   }

   }

}


/*
 * 	UART Rx handler for GPS UART
 *
 * 	On getting first '$' character, puts the subsequent character into a buffer.
 * 	When CR-LF termination is recieved, signals the gps task of the new sentence.
 *
 *  Note: This is called from within the UART RX ISR
 */
static void gps_uart_rx_handler(uint32_t instance, void *state)
{
	static uint32_t buf_index;
	static uint8_t  prev_ch;
	uart_state_t * 	u_state = (uart_state_t *)state;
	uint8_t			ch;

	ch = *(u_state->rxBuff);

	if('$' == ch)
	{
		buf_index = 0;
	}
	else
	{
		gps_rx_sentence[buf_index++] = ch;
		if( ('\n' == ch) && (prev_ch == '\r') )
		{
			gps_rx_len = buf_index;
			OSA_SemaPost(&gps_task_sem);
		}
	}

	prev_ch = ch;
}
