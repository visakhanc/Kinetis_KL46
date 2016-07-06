/*
 * gsm_task.c
 *
 *  Created on: Jul 5, 2015
 *      Author: Visakhan
 */

#include <stdio.h>
#include "common.h"
#include "gsm_common.h"
#include "string.h"
#include "fsl_uart.h"
#include "fsl_debug_console.h"
#include "gps_parse.h"
#include "num_utils.h"
#include "board.h"




/* Provate Functions */
static void gsm_uart_rx_handler(UART_Type *base, uart_handle_t *handle, status_t status, void *userData);

/***** Globals ******/
extern gps_info_struct gps_info;
gsm_status_struct gsm_status;
char http_buf[HTTP_BUF_SIZE];


/* FreeRTOS resources */
static TaskHandle_t xGsmTaskHandle;
static SemaphoreHandle_t xGsmTxSem;
static SemaphoreHandle_t xGsmTxSyncSem;
static EventGroupHandle_t xGsmEvent;

static uart_handle_t gsm_uart_handle;
static volatile bool http_buf_switch = false;
static volatile int http_buf_count;
static uint8_t gsm_rx_isr_buf[2];
static uint8_t gsm_rx_buf[100];
static int gsm_rx_len;

static const uart_config_t gsm_uart_config = {
								.baudRate_Bps = GSM_UART_BAUDRATE,
								.parityMode = kUART_ParityDisabled,
								.stopBitCount = kUART_OneStopBit,
								.enableRx = true,
								.enableTx = true
							};


#if GSM_DEBUG
/*
 *  Task for testing GSM module through a command prompt.
 *
 *  Console UART is used to receive command from a Test PC
 *  and the received command is sent to GSM module. The response
 *  from GSM module is printed out to the console
 *
 *  Note: Set GSM_DEBUG macro to 1 for enabling this task
 */

void gsm_debug_task(void *pArg)
{

	uint32_t len, i;
	char text[100];

	if(0 != gsm_init()) {
		PRINTF("\r\ngsm_init error");
	}
	PRINTF("\r\ngsm_term_tx_task");

	while(1)
	{
		/* Get input from debug port and send to SIM900 */
		PRINTF("\r\nSIM900>");
		i = 0;
		while(i < sizeof(text)) {
			text[i] = DbgConsole_Getchar();
			DbgConsole_Putchar(text[i]);
			if((text[i] == '\r') || (text[i] == '\n')) {
				text[i] = '\r';
				DbgConsole_Putchar('\n');
				break;
			}
			i++;
		}

		len = i+1;

		gsm_uart_acquire();
		gsm_uart_send(text, len);
		gsm_uart_release();
	}

}
#endif



/*
 *  Initializes GSM UART and associated FreeRTOS resources
 */
int gsm_init(void)
{

	/* Create Mutex for GSM UART Tx */
	if((xGsmTxSem = xSemaphoreCreateMutex()) == NULL) {
		PRINTF("ERROR: xGsmTxSem creation\r\n");
		return 1;
	}

	/* Create binary semaphore for GSM UART synchronization */
	if((xGsmTxSyncSem = xSemaphoreCreateBinary()) == NULL) {
		PRINTF("ERROR: xGsmTxSyncSem creation\n\r");
		return 1;
	}

	/* Create Event for communicating various GSM responses */
	if((xGsmEvent = xEventGroupCreate()) == NULL) {
		PRINTF("ERROR: xGsmEvent creation\n\r");
		return 1;
	}

	/* Initialize UART driver with given parameters */
	UART_Init(GSM_UART_BASE, &gsm_uart_config, GSM_UART_SRCCLK);

	/* Install our own handler for UART Rx data, which is called by the ISR */
	UART_TransferCreateHandle(GSM_UART_BASE, &gsm_uart_handle, gsm_uart_rx_handler, NULL);
	gsm_uart_handle.rxData = gsm_rx_isr_buf;
	gsm_uart_handle.rxDataSize = 1;
	/* Enable UART Receive interrupt */
	UART_EnableInterrupts(GSM_UART_BASE, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);

	return 0;
}

/* Sends the GSM AT command 'cmd' through UART
 * NOTE: cmd should be null terminated
 *
 * Return: 0 - success; 1 - failure
 */
int gsm_send_command(const char *cmd)
{
	int ret = 0;

	/* Send command */
	if(gsm_uart_send(cmd, strlen(cmd)) != 0) {
		ret = 1;
	}

	/* Send carriage return */
	if(gsm_uart_send("\r\n", 2) != 0) {
		ret = 1;
	}

	return ret;
}


/*
 *  Get access to GSM UART by acquiring semaphore
 *
 *  NOTE: Tasks which communicate to GSM module will call this before
 *  the section of code which deals with all communication with the module.
 *  After this the Task releases the access by gsm_uart_release()
 *
 *  After this call the task would block indefinitely until acquiring the semaphore
 *  Return:
 *  	0 - Acquire successful
 *  	1 - Something went wrong
 */
int gsm_uart_acquire(void)
{
	/* Take Mutex for GSM UART Tx */
	if(pdTRUE != xSemaphoreTake(xGsmTxSem, portMAX_DELAY)) {
		return 1;
	}

	return 0;
}

/*
 *  Releases the access to GSM UART acquired by calling gsm_uart_acquire()
 *
 *  Return:
 *  	0 - Success
 *  	1 - Error
 */
int gsm_uart_release(void)
{
	/* Release Tx Mutex */
	if(pdTRUE != xSemaphoreGive(xGsmTxSem)) {
		return 1;
	}

	return 0;
}


/*
 * Transmit data to GSM UART
 * 	1. Calls UART driver API
 * 	2. Waits for TaskNotification from UART Handler
 *
 * 	Return: 0 - success; 1 - error
 */
int gsm_uart_send(const char *data, uint32_t len)
{
	uart_transfer_t		tx_xfer;
	tx_xfer.data = (uint8_t *)data;
	tx_xfer.dataSize = len;

	/* Initiate UART driver to send the data */
	UART_TransferSendNonBlocking(GSM_UART_BASE, &gsm_uart_handle, &tx_xfer);

	/* Block until UART handler signalling completion of Tx */
	xSemaphoreTake(xGsmTxSyncSem, portMAX_DELAY);

	return 0;

}

/*
 * Send SMS message to number given in 'address'
 * 	length of message should be less than 160
 * 	Message should be null terminated
 * Returns: 0 - success; 1 - error
 */
int gsm_send_sms(const char *buf, int length, const char *address)
{
	int ret = 0;
	uint8_t ctrl_z = 0x1A;
	uint8_t sms_buf[25];
	EventBits_t ev;

	/* Message content too long */
	if (length > 160) {
		PRINTF("\nSMS too long");
		return 1;
	}

	if (buf[length] != '\0') {
		PRINTF("\nSMS not proper string");
		return 1;
	}

	/* Set text mode */
	gsm_send_command("AT+CMGF=1");
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 1000);
	if (ev & EVENT_GSM_ERROR) {
		PRINTF("\n\rerr:CMGF");
		return 1;
	}

	/* Set GSM character set */
	gsm_send_command("AT+CSCS=\"GSM\"");
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 1000);
	if (ev & EVENT_GSM_ERROR) {
		PRINTF("\n\rerr:CSCS");
		return 1;
	}

	/* Check size of address */
	if (strlen(address) > 15) {
		PRINTF("\naddress too long");
		return 1;
	}

	/* Message address */
	snprintf((char *)sms_buf, sizeof(sms_buf) - 1, "AT+CMGS=\"%s\"", address);
	gsm_send_command((char*)sms_buf);
	vTaskDelay(1000); /* Wait for prompt '>' */

	/* Send message */
	if(gsm_uart_send(buf, length) != 0) {
		ret = 1;
	}

	if(gsm_uart_send((char *)&ctrl_z, 1) != 0) {
		ret = 1;
	}

	/* Wait for OK */
	ev = gsm_wait_for_event(EVENT_GSM_OK|EVENT_GSM_ERROR, 20 * 1000);
	if (ev & EVENT_GSM_ERROR) {
		PRINTF("\r\nERROR: SMS send");
		ret = 1;
	}
	else if(!(ev & EVENT_GSM_OK)) {
		PRINTF("\r\nERROR: SMS timeout");
		ret = 1;
	}

	return ret;
}


/*
 *  Task for handling various response strings received from GSM module
 *  This task waits for signal from UART Rx handler, indicating that a complete string is received
 *  The string is then checked against known response strings, relevant to the application
 *  For each of the identified string, corresping event is signalled or global status is updated
 */
void gsm_rx_task(void *pArg)
{
	char rx_buf[100];
	int len, temp;

	if(gsm_init() != 0) {
		PRINTF("gsm_init() error\r\n");
	}

	/* Use Task Notification to synchronize between UART Rx handler and GSM Rx task */
	xGsmTaskHandle = xTaskGetCurrentTaskHandle();

	while (1) {

		/* Wait for signal from UART Rx handler */
		if(ulTaskNotifyTake(pdTRUE, portMAX_DELAY) == 1) {
			/* Copy GSM response string to local buffer */
			len = gsm_rx_len;
			if(len >= sizeof(rx_buf)) {
				continue;
			}
			memcpy((void *) rx_buf, (const void *) gsm_rx_buf, len);
			rx_buf[len] = '\0';

#if GSM_DEBUG
			PRINTF("%s\r\n", rx_buf);
#endif
			/* Response of 2 characters */
			if (2 == len) {
				if (0 == strcmp((char *)rx_buf, "OK")) { // TODO: use rx_buf to compare
					xEventGroupSetBits(xGsmEvent, EVENT_GSM_OK);
				}
			}
			/* Response of 4 characters */
			else if (4 == len) {
				if (0 == strcmp((char *)rx_buf, "RING")) {
					xEventGroupSetBits(xGsmEvent, EVENT_GSM_RING);
				}
			}
			/* Response of 5 characters */
			else if (5 == len) {
				if (0 == strcmp((char *)rx_buf, "ERROR")) {
					xEventGroupSetBits(xGsmEvent, EVENT_GSM_ERROR);
				}
			}
			/* Others */
			else {
				if (NULL != strstr((char *)rx_buf, "+CLIP")) {
					/* Get the caller number from CLIP line */
					len = get_quoted_string(&rx_buf[7], gsm_status.caller, sizeof(gsm_status.caller));
					if (len > 0) {
						xEventGroupSetBits(xGsmEvent, EVENT_GSM_CLIP);
					}
				}

				if (NULL != strstr((char *)rx_buf, "+CREG")) {
					/* Get and update registration status */
					if ((rx_buf[9] == '1') || (rx_buf[9] == '5')) {
						gsm_status.registerd = true;
						xEventGroupSetBits(xGsmEvent, EVENT_GSM_CREG);
					}
					else {
						gsm_status.registerd = false;
					}
				}

				if (NULL != strstr((char *)rx_buf, "+HTTPACTION")) {
					/* Get HTTP receive status and size of data received */
					parse_decimal(&temp, (char *)&rx_buf[14], 3);
					if (temp == 200) {
						parse_decimal(&gsm_status.http_recv_len, (char *)&rx_buf[18], 5);
					}
					gsm_status.http_status = temp;

					xEventGroupSetBits(xGsmEvent, EVENT_GSM_HTTPACTION);
				}

				if (NULL != strstr((char *)rx_buf, "+HTTPREAD")) {
					/* get number of bytes going to be received */
					parse_decimal(&temp, (char *)&rx_buf[10], 5);
					http_buf_count = temp;

					/* Tell UART Rx handler to receive characters to http buffer */
					http_buf_switch = true;
				}

				if (NULL != strstr((char *)rx_buf, "+SAPBR")) {
					gsm_status.gprs_context = (rx_buf[10] == '1') ? true : false;
				}

			}

		}

	}

}


/*
 * Wait for one or more GSM events, for a duration of 'delay_ticks'
 *
 * delay_ticks: number of ticks to wait (0: wait indefinitely)
 */
uint32_t gsm_wait_for_event(uint32_t events, uint32_t delay_ticks)
{
	TickType_t ticksToWait = (0 == delay_ticks)  ? portMAX_DELAY : delay_ticks;
	EventBits_t eventsToWait = (EventBits_t)events;

	return xEventGroupWaitBits(xGsmEvent, eventsToWait, pdTRUE, pdFALSE, ticksToWait);
}


/*
 * 	UART Rx handler for GSM UART
 * 	Puts character into a buffer, until CR-LF termination is recieved and signals the gsm_rx_task .
 *
 *  Note: This is called from the UART RX ISR
 */
static void gsm_uart_rx_handler(UART_Type *base, uart_handle_t *handle, status_t status, void *userData)
{
	static int buf_n;
	static int http_n;
	static uint8_t prev_ch;
	uint8_t ch;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	/* Rx operation completed */
	if(kStatus_UART_RxIdle == status) {

		/*  The buffer pointer was incremented in UART ISR */
		handle->rxData--;
		/* Get received byte */
		ch = *(handle->rxData);
		/* reset receive size (decremented in UART ISR) */
		handle->rxDataSize = 1;


		if (false == http_buf_switch) {
			if(buf_n < sizeof(gsm_rx_buf)) {
				gsm_rx_buf[buf_n++] = ch;
				if (('\n' == ch) && ('\r' == prev_ch)) {
					gsm_rx_len = buf_n - 2;
					gsm_rx_buf[gsm_rx_len] = '\0';
					buf_n = 0;

					/* Signal only if more than CR-LF*/
					if (gsm_rx_len > 0) {
						vTaskNotifyGiveFromISR(xGsmTaskHandle, &xHigherPriorityTaskWoken);
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
					xEventGroupSetBitsFromISR(xGsmEvent, EVENT_GSM_HTTPREAD, &xHigherPriorityTaskWoken);
					http_buf_switch = false;
					http_n = 0;
				}
			}
		}
	}
	/* Tx operation completed */
	else if (kStatus_UART_TxIdle == status) {
		xSemaphoreGiveFromISR(xGsmTxSyncSem, &xHigherPriorityTaskWoken);
	}
	else {
		/* Error, should be Rx overrun */
	}

	/* If vTaskNotifyGiveFromISR caused a higher priority task to wake up, request for context switch */
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


