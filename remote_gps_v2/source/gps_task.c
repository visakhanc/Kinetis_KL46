/*
 * gps_task.c
 *
 *  Created on: Jul 5, 2015
 *      Author: Visakhan
 */

#include <stdio.h>

#include "gps_parse.h"
#include "string.h"
#include "fsl_uart.h"
#include "common.h"
#include "fsl_debug_console.h"
#include "board.h"

/* FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"

static void gps_uart_rx_handler(UART_Type *base, uart_handle_t *handle, status_t status, void *userData);

static uint8_t gps_rx_buf[2], gps_rx_sentence[200];
static uint32_t gps_rx_len;
static TaskHandle_t xGpsTaskHandle;
gps_info_struct gps_info;
uart_handle_t gps_uart_handle;
const uart_config_t gps_uart_config = {
						.baudRate_Bps = GPS_UART_BAUDRATE,
						.parityMode = kUART_ParityDisabled,
						.stopBitCount = kUART_OneStopBit,
						.enableTx = true,
						.enableRx = true
					};


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
	uint32_t notificationValue;

	PRINTF("from gps task...\r\n");

	/* Use Task Notification to sychronize between UART Rx handler and GPS task */
	xGpsTaskHandle = xTaskGetCurrentTaskHandle();

	/* Initialize UART driver with given parameters */
	UART_Init(GPS_UART_BASE, &gps_uart_config, GPS_UART_SRCCLK);

	/* Initialize UART driver and install our own handler for UART Rx data, which is called by the ISR */
	UART_TransferCreateHandle(GPS_UART_BASE, &gps_uart_handle, gps_uart_rx_handler, NULL);

	/* Set receive buffer pointer explicitly for custom handling */
	gps_uart_handle.rxData = gps_rx_buf;
	gps_uart_handle.rxDataSize = 1;

	/* Enable RX interrupt (start reception of bytes from GPS module) */
	UART_EnableInterrupts(GPS_UART_BASE, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);

	/* Turn on RED LED */


	while (1) {

		/* Wait for notification from UART Rx handler */
		if((notificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY)) == 1) {
			/* Copy the received sentence */
			len = gps_rx_len;
			memcpy((void *) rx_sentence, (void *) gps_rx_sentence, len);

			/* Parse the received sentence to update gps_info structure */
			if (NULL != strstr(rx_sentence, "GPGGA")) {
				data_ptr = &rx_sentence[6];
				gps_parse_gga(data_ptr, &gps_info);
			}

			if ((NULL != strstr(rx_sentence, "GPRMC")) || (NULL != strstr(rx_sentence, "GNRMC"))) {
				data_ptr = &rx_sentence[6];
				gps_parse_rmc(data_ptr, &gps_info);
			}
		}

		/* Check for GPS Fix */
		if (NO_FIX != gps_info.fix) {
			/* Turn on GREEN LED */
			LED_GREEN_ON();
		}
		else {
			/* Turn off GREEN LED */
			LED_GREEN_OFF();
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
static void gps_uart_rx_handler(UART_Type *base, uart_handle_t *handle, status_t status, void *userData)
{
	static uint32_t buf_n;
	static uint8_t prev_ch;
	uint8_t ch;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;


	/*  The buffer pointer was incremented in UART ISR */
	handle->rxData--;
	/* Get received byte */
	ch = *(handle->rxData);
	/* Reset Rx size (decremented in UART ISR), otherwise UART driver will disable Rx interrupt! */
	handle->rxDataSize = 1;

	if ('$' == ch) {
		buf_n = 0;
	}
	else {
		if (buf_n < sizeof(gps_rx_sentence)) {
			gps_rx_sentence[buf_n++] = ch;
			if (('\n' == ch) && (prev_ch == '\r')) {
				gps_rx_len = buf_n;
				vTaskNotifyGiveFromISR(xGpsTaskHandle, &xHigherPriorityTaskWoken);
			}
		}
	}

	prev_ch = ch;

	/* Request context switch if vTaskNotifyGiveFromISR() caused a higher priority task ready */
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
