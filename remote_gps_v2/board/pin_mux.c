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

#include "fsl_common.h"
#include "fsl_port.h"

/* configuration for push button switch (for SW1 and SW3) */
port_pin_config_t switch_pin_config = {
	kPORT_PullUp,
	kPORT_SlowSlewRate,
	kPORT_PassiveFilterEnable,
	kPORT_LowDriveStrength,
	kPORT_MuxAsGpio
};

static void configure_lcd_pins(uint32_t instance);

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Function Name : BOARD_InitPins */
void BOARD_InitPins(void)
{
    /* Ungate the port clocks (XTAL pins are in PORTA) */
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortE);

	/* LPSCI (UART0) Pins */
    /* Affects PORTA_PCR1 register */
    PORT_SetPinMux(PORTA, 1u, kPORT_MuxAlt2);
    /* Affects PORTA_PCR2 register */
    PORT_SetPinMux(PORTA, 2u, kPORT_MuxAlt2);

    /* UART1 pins */
    /* PORTE_PCR0 */
    PORT_SetPinMux(PORTE, 0, kPORT_MuxAlt3);
    /* PORTE_PCR1 */
    PORT_SetPinMux(PORTE, 1, kPORT_MuxAlt3);

    /* UART2 pins */
    /* PTE16 */
	PORT_SetPinMux(PORTE, 16, kPORT_MuxAlt3);
	/* PTE17 */
	PORT_SetPinMux(PORTE, 17, kPORT_MuxAlt3);

	/*LED pins*/
	PORT_SetPinMux(PORTD, 5, kPORT_MuxAsGpio);  	// GREEN
	PORT_SetPinMux(PORTE, 29, kPORT_MuxAsGpio);		// RED

	/* SW1 Pin */
	PORT_SetPinMux(PORTC, 3, kPORT_MuxAsGpio);
	PORT_SetPinConfig(PORTC, 3, &switch_pin_config);
	PORT_SetPinInterruptConfig(PORTC, 3, kPORT_InterruptRisingEdge);
	PORT_ClearPinsInterruptFlags(PORTC, (1 << 3));

	/* SW3 Pin */
	PORT_SetPinMux(PORTC, 12, kPORT_MuxAsGpio);
	PORT_SetPinConfig(PORTC, 12, &switch_pin_config);
	PORT_SetPinInterruptConfig(PORTC, 12, kPORT_InterruptRisingEdge);
	PORT_ClearPinsInterruptFlags(PORTC, (1 << 12));

	/* SLCD pins */
	configure_lcd_pins(0);
}


static void configure_lcd_pins(uint32_t instance)
{
    PORT_SetPinMux(PORTE, 4u, kPORT_MuxAlt7);
    PORT_SetPinMux(PORTE, 5u, kPORT_MuxAlt7);

    PORT_SetPinMux(PORTB, 7u, kPORT_MuxAlt7);
    PORT_SetPinMux(PORTB, 8u, kPORT_MuxAlt7);
    PORT_SetPinMux(PORTB, 10u, kPORT_MuxAlt7);
    PORT_SetPinMux(PORTB, 11u, kPORT_MuxAlt7);
    PORT_SetPinMux(PORTB, 21u, kPORT_MuxAlt7);
    PORT_SetPinMux(PORTB, 22u, kPORT_MuxAlt7);
    PORT_SetPinMux(PORTB, 23u, kPORT_MuxAlt7);

    PORT_SetPinMux(PORTC, 17u, kPORT_MuxAlt7);
    PORT_SetPinMux(PORTC, 18u, kPORT_MuxAlt7);

    PORT_SetPinMux(PORTD, 0u, kPORT_MuxAlt7);
}
