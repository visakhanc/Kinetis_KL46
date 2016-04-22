/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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


#include "fsl_device_registers.h"
#include "board.h"
#include "fsl_gpio_driver.h"
#include "fsl_os_abstraction.h"
#include "fsl_debug_console.h"
#include "fsl_clock_manager.h"
#include "fsl_smc_hal.h"
#include "common.h"
#include "gps_parse.h"

#define LED_TASK_STACKSIZE  256
#define LED_TASK_PRIO		4  /* uC-OSIII priority=4+2=6 */

#define GPS_TASK_STACKSIZE	1024
#define GPS_TASK_PRIO		4

#define CONTROL_TASK_STACKSIZE	1024
#define CONTROL_TASK_PRIO		4

#define GSM_RX_TASK_STACKSIZE	1024
#define GSM_RX_TASK_PRIO		3


#define DISP_TASK_STACKSIZE		512
#define DISP_TASK_PRIO			5

/* Define uC-OSIII task resources - stack and TCB */
OSA_TASK_DEFINE(LedTask, LED_TASK_STACKSIZE);
OSA_TASK_DEFINE(gps_task, GPS_TASK_STACKSIZE);
OSA_TASK_DEFINE(gsm_rx_task, GSM_RX_TASK_STACKSIZE);
OSA_TASK_DEFINE(control_task, CONTROL_TASK_STACKSIZE);
#if ENABLE_DISP_TASK
OSA_TASK_DEFINE(disp_task, DISP_TASK_STACKSIZE);
#endif

extern void gps_task(void *pArg);
extern void gsm_rx_task(void *pArg);
extern void control_task(void *pArg);

void hardware_init(void);
void LedTask(void *pArg);
void disp_task(void *pArg);


int main(void)
{
	int err;

	hardware_init();

    // Configure the power mode protection
    SMC_HAL_SetProtection(SMC_BASE_PTR, kAllowPowerModeVlp);

	/* Initialize gpio input and output pins */
	GPIO_DRV_Init(&switchPins, &ledPins);

	PRINTF("Initializing\n\r");

	/* Initialize OS: start tick timer etc. */
	OSA_Init();

	/* Create task */
	err = OSA_TaskCreate(LedTask, "led",
						LED_TASK_STACKSIZE, LedTask_stack, LED_TASK_PRIO,
						0, false, &LedTask_task_handler);
	if(err != kStatus_OSA_Success) {
		PRINTF("Failed to create led task\r\n");
	}
#if 1
	err = OSA_TaskCreate(gps_task, "gps", GPS_TASK_STACKSIZE, gps_task_stack, GPS_TASK_PRIO, (task_param_t)0,
						false, &gps_task_task_handler);
	if(err != kStatus_OSA_Success) {
		PRINTF("Failed to create gps task\r\n");
	}
#endif

	err = OSA_TaskCreate(control_task, "control", CONTROL_TASK_STACKSIZE, control_task_stack, CONTROL_TASK_PRIO, (task_param_t)0,
							false, &control_task_task_handler);
	if(err != kStatus_OSA_Success) {
		PRINTF("Failed to create control task\r\n");
	}

#if 1
	err = OSA_TaskCreate(gsm_rx_task, "gsm_rx", GSM_RX_TASK_STACKSIZE, gsm_rx_task_stack, GSM_RX_TASK_PRIO, (task_param_t)0,
							false, &gsm_rx_task_task_handler);
	if(err != kStatus_OSA_Success) {
		PRINTF("Failed to create gsm_rx task\r\n");
	}
#endif

#if ENABLE_DISP_TASK
	err = OSA_TaskCreate(disp_task, "disp", DISP_TASK_STACKSIZE, disp_task_stack, DISP_TASK_PRIO, (task_param_t)0,
							false, &disp_task_task_handler);
	if(err != kStatus_OSA_Success) {
		PRINTF("Failed to create display task\r\n");
	}
#endif

	PRINTF("Starting...\n\r");

	/* start scheduler */
	OSA_Start();

	for(; ;);
    /* Never leave main */
    return 0;
}


void LedTask(void *pArg)
{
	while(1) {
		GPIO_DRV_SetPinOutput(kGpioLED2);
		OSA_TimeDelay(1000);
		GPIO_DRV_ClearPinOutput(kGpioLED2);
		OSA_TimeDelay(1000);
	}
}

void hardware_init(void) {

  /* enable clock for PORTs */
  CLOCK_SYS_EnablePortClock(PORTA_IDX);
  CLOCK_SYS_EnablePortClock(PORTB_IDX);
  CLOCK_SYS_EnablePortClock(PORTE_IDX);

  /* Init board clock */
  BOARD_ClockInit();
  dbg_uart_init();
}

#if ENABLE_DISP_TASK

extern gps_info_struct gps_info;
void disp_task(void *pArg)
{

	while(1)
	{
		debug_printf("\n\r");
		debug_printf("Time: %02d:%02d:%02d  %d/%d/%d",
				gps_info.time.hour, gps_info.time.min, gps_info.time.sec,
				gps_info.time.date, gps_info.time.month, gps_info.time.year+2000);
		debug_printf("\n\rFix : ");
		switch(gps_info.fix)
		{
			case NO_FIX: debug_printf("No Fix"); break;
			case GPS_FIX: debug_printf("GPS Fix"); break;
			case DGPS_FIX: debug_printf("DGPS Fix"); break;
			default: debug_printf("Invalid data");
		}

		debug_printf("\n\rLatitude: %d.%d %c", (int)gps_info.latitude, (int)((gps_info.latitude * 1000.0) - (int)gps_info.latitude * 1000), gps_info.noth_south);
		debug_printf("\n\rLogitude: %d.%d %c", (int)gps_info.longitude, (int)((gps_info.longitude * 1000.0) - (int)gps_info.longitude * 1000), gps_info.east_west);
		debug_printf("\n\rAltitude: %d m", (int)gps_info.altitude);
		debug_printf("\n\rSpeed:    %d kph", (int)gps_info.velocity);
		debug_printf("\n\rCourse:   %d deg", (int)gps_info.course);
		debug_printf("\n\rHDOP:     %d.%d", (int)gps_info.hdop, (int)((gps_info.hdop * 10.0) - (int)gps_info.hdop * 10));
		debug_printf("\n\rSatellites used: %d", gps_info.sat_used);

		OSA_TimeDelay(1000);
	}
}
#endif


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
