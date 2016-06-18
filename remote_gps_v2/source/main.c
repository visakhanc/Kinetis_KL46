/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include <string.h>

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "gps_parse.h"
#include "gsm_common.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"



/* Task functions and properties */
extern void gps_task(void *pvParameters);
#define GPS_TASK_PRIORITY		(configMAX_PRIORITIES - 2)
#define GPS_TASK_STACKSIZE		512

extern void gsm_rx_task(void *pvParameters);
#define GSM_TASK_PRIORITY		(configMAX_PRIORITIES - 1)
#define GSM_TASK_STACKSIZE		512

extern void message_task(void *pvParameters);
#define MESSAGE_TASK_PRIORITY	(configMAX_PRIORITIES - 2)
#define MESSAGE_TASK_STACKSIZE	512

extern void log_task(void *pvParameters);
#define LOG_TASK_PRIORITY		(configMAX_PRIORITIES - 2)
#define LOG_TASK_STACKSIZE		512

#if GSM_DEBUG == 1
extern void gsm_debug_task(void *pvParameters);
#define GSM_DEBUG_TASK_PRIORITY	(configMAX_PRIORITIES - 2)
#define GSM_DEBUG_TASK_STACKSIZE	512
#endif


/* Globals */
extern gps_info_struct gps_info;


static void disp_task(void *pArg);
#define disp_task_PRIORITY 		(configMAX_PRIORITIES - 3)
#define disp_task_STACKSIE		configMINIMAL_STACK_SIZE



/*!
 * @brief Application entry point.
 */
int main(void) {
  /* Init board hardware. */
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();

  /* Initialize LEDs to OFF state */
  LED_RED_INIT(LOGIC_LED_OFF);
  LED_GREEN_INIT(LOGIC_LED_OFF);

  /* Create RTOS tasks */
  //xTaskCreate(disp_task, "DispTask", disp_task_STACKSIE, NULL, disp_task_PRIORITY, NULL);
  xTaskCreate(gps_task, "GpsTask", GPS_TASK_STACKSIZE, NULL, GPS_TASK_PRIORITY, NULL);
  xTaskCreate(gsm_rx_task, "GSMTask", GSM_TASK_STACKSIZE, NULL, GSM_TASK_PRIORITY, NULL);
#if (GSM_DEBUG == 0)
  xTaskCreate(log_task, "LogTask", LOG_TASK_STACKSIZE, NULL, LOG_TASK_PRIORITY, NULL);
  xTaskCreate(message_task, "MessageTask", MESSAGE_TASK_STACKSIZE, NULL, MESSAGE_TASK_PRIORITY, NULL);
#else
  xTaskCreate(gsm_debug_task, "GsmDebug", GSM_DEBUG_TASK_STACKSIZE, NULL, GSM_DEBUG_TASK_PRIORITY, NULL);
#endif

  vTaskStartScheduler();


  for(;;) { /* Infinite loop to avoid leaving the main function */
    __asm("NOP"); /* something to use as a breakpoint stop while looping */
  }
}


/*
 *  Task for displaying some statistics
 */
static void disp_task(void *pArg)
{

	while(1)
	{
		PRINTF("\n\r");
		PRINTF("Time: %02d:%02d:%02d  %d/%d/%d",
				gps_info.time.hour, gps_info.time.min, gps_info.time.sec,
				gps_info.time.date, gps_info.time.month, gps_info.time.year+2000);
		PRINTF("\n\rFix : ");
		switch(gps_info.fix)
		{
			case NO_FIX: PRINTF("No Fix"); break;
			case GPS_FIX: PRINTF("GPS Fix"); break;
			case DGPS_FIX: PRINTF("DGPS Fix"); break;
			default: PRINTF("Invalid data");
		}

		PRINTF("\n\rLatitude: %d.%d %c", (int)gps_info.latitude, (int)((gps_info.latitude * 1000.0) - (int)gps_info.latitude * 1000), gps_info.noth_south);
		PRINTF("\n\rLogitude: %d.%d %c", (int)gps_info.longitude, (int)((gps_info.longitude * 1000.0) - (int)gps_info.longitude * 1000), gps_info.east_west);
		PRINTF("\n\rAltitude: %d m", (int)gps_info.altitude);
		PRINTF("\n\rSpeed:    %d kph", (int)gps_info.velocity);
		PRINTF("\n\rCourse:   %d deg", (int)gps_info.course);
		PRINTF("\n\rHDOP:     %d.%d", (int)gps_info.hdop, (int)((gps_info.hdop * 10.0) - (int)gps_info.hdop * 10));
		PRINTF("\n\rSatellites used: %d\n", gps_info.sat_used);

		vTaskDelay(1000);
	}

	vTaskSuspend(NULL);
}


