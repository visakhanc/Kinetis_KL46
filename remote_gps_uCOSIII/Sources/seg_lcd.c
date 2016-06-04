/*
 * seg_lcd.c
 *
 *  Created on: Jun 3, 2016
 *      Author: Visakhan
 */

#include "seg_lcd.h"
#include "board.h"
#include "MKL46Z4.h"

/* LCD front plane pin numbers for each LCD digits on FRDM-KL46 board */
static uint8_t lcd_fp_pins[4][2] = {
		{37, 17}, /* Digit 1 pins in order */
		{7, 8},   /* Digit 2 pins in order*/
		{53, 38}, /* DIgit 3 pins in order */
		{10 ,11}
	};

/* This function initialize the Segment LCD on FRDM-KL46Z board */
void slcd_init(void)
{
	/* Enable SLCD and Port clocks */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_SLCD_MASK;

	LCD->GCR |= LCD_GCR_PADSAFE_MASK; 	/* disable LCD pins while configuring */
	LCD->GCR &= ~LCD_GCR_LCDEN_MASK; 	/* disable driving LCD  */

	configure_lcd_pins(0); /* Pin muxing for slcd on FRDM-KL46 board */

	/* LCD control register */
	LCD->GCR = 	LCD_GCR_CPSEL_MASK | /* use capacitor charge pump */
				LCD_GCR_SOURCE(0) | /* Use default clock source */
				LCD_GCR_ALTSOURCE(0) | /* Dont use alternate clock */
				//LCD_GCR_ALTDIV(0) |
				LCD_GCR_DUTY(3) | /* 1/4 duty cycle */
				LCD_GCR_LADJ(3) | /* slowest clock source for capacitor charge pump */
				LCD_GCR_FFR(0) | /* standard frame rate */
				LCD_GCR_LCDDOZE(0) | /* allow running in stop mode */
				LCD_GCR_LCLK(4); /* for getting frame freq = 32, assuming LCD clock = 32kHz */

	LCD->AR = 0; /* default blink rate */

	/* Enable LCD pins for FRDM-KL46 board */
	LCD->PEN[0] = 	(1 << 7) | /* LCD_P7 = FP Digit 2 (D,E,G,F) */
					(1 << 8) | /* LCD_P8  = FP Digit 2 (DP,C,B,A)*/
					(1 << 10) | /* LCD_P10 = FP Digit 4 (D,E,G,F)*/
					(1 << 11) | /* LCD_P11 = FP Digit 4 (COL,C,B,A) */
					(1 << 17) | /* LCD_P17 = FP Digit 1 (DP,C,B,A) */
					(1 << 18) | /* LCD_P18 = BP 4 */
					(1 << 19); /* LCD_P19 = BP 3 */

	LCD_PEN[1] = 	(1 << 5) |	/* LCD_P37 = FP Digit 1 (D,E,G,F) */
					(1 << 6) |  /* LCD_P38  = FP Digist 3 (DP,C,B,A) */
					(1 << 8) |  /* LCD_P40 = BP 1 */
					(1 << 20) | /* LCD_P52 = BP 2 */
					(1 << 21); /* LCD_P53 = FP Digit 3 (D,E,G,F)*/

	/* Configure backplane and frontplane pins for FRDM-KL46 board */
	LCD->BPEN[0] = 	(1 << 18) | (1 << 19);	/* LCD_P18 and LCD_P19 are back plane pins */
	LCD->BPEN[1] = (1 << 8) | (1 << 20); /* LCD_P40 and LCD_P52 are backplane pins */

	/* Initalize waveform registers to show a blank display */
	LCD->WF[0] =	0; /* Pins 3 to 0 not used */
	LCD->WF[1] = 	LCD_WF_WF7(0x0); /* LCD_P7 off */
	LCD->WF[2] = 	LCD_WF_WF8(0x0) | /* LCD_P8 off */
					LCD_WF_WF10(0x0)| /* LCD_P10 off */
					LCD_WF_WF11(0x0); /* LCD_P11 off */
	LCD->WF[3] =	0; /* Pins 12 to 15 not used */
	LCD->WF[4] = 	LCD_WF_WF17(0x0) | /* LCD_P17 off */
					LCD_WF_WF18(0x88) | /* Backplane pin LCD_P18(BP4) active during H and D phases */
					LCD_WF_WF19(0x44); /* Backplane pin LCD_P19(BP3) active during G and C phases */
	LCD->WF[5] = 	0; /* Pins 20 to 23 not used */
	LCD->WF[6] = 	0; /* Pins 24 to 27 not used */
	LCD->WF[7] = 	0; /* Pins 28 to 31 not used */
	LCD->WF[8] = 	0; /* Pins 32 to 35 not used */
	LCD->WF[9] = 	LCD_WF_WF37(0x0) | /* LCD_P37 off */
					LCD_WF_WF38(0x0); /* LCD_P38 off */
	LCD->WF[10] = 	LCD_WF_WF40(0x11); /* BP pin LCD_P40 drives A and E phases */
	LCD->WF[11] = 	0; /* pins 44 to 47 not used */
	LCD->WF[12] = 	0; /* pins 48 to 51 not used */
	LCD->WF[13] = 	LCD_WF_WF52(0x22) | /* BP pin PCD_P52 drives B and F phases */
					LCD_WF_WF53(0); 	/* LCD_P53 off */
	LCD->WF[14] = 	0; /* Pins 56 to 59 not used */
	LCD->WF[15] = 	0; /* Pins 60 to 63 not used */

	/* Disable Pad safe bit and enable LCD driver */
	LCD->GCR &= ~LCD_GCR_PADSAFE_MASK;
	LCD->GCR |= LCD_GCR_LCDEN_MASK;

}

/* Functions to drive a digit to a particular value
 *
 * 	Digit: 0 - 3
 * 	Value: 0x0 to 0xF
 */
void slcd_set_digit(uint32_t digit, uint32_t val)
{
	if((digit > 3) || (val > 0xF)) return;

	switch(val)
	{
		case 0x0: 	LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D|SEG_E|SEG_F;
					LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A|SEG_B|SEG_C;
					break;

		case 0x1:	LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_NONE;
					LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_B|SEG_C;
					break;

		case 0x2:	LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D|SEG_G|SEG_E;
					LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A|SEG_B;
					break;

		case 0x3:	LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D|SEG_G;
					LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A|SEG_B|SEG_C;
					break;

		case 0x4:	LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_F|SEG_G;
					LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_B|SEG_C;
					break;

		case 0x5:	LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_F|SEG_G|SEG_D;
					LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A|SEG_C;
					break;

		case 0x6:	LCD->WF8B[lcd_fp_pins[digit][0]] =

	}
}
