/*
 * seg_lcd.c
 *
 *  Created on: Jun 3, 2016
 *      Author: Visakhan
 */

#include "seg_lcd.h"
#include "board.h"

/* LCD front plane pin numbers for each LCD digits on FRDM-KL46 board */
static uint8_t lcd_fp_pins[4][2] = { { 37, 17 }, /* Digit 1 pins in order (first pin drives D,E,F,G and second pin DP,A,B,C segments) */
										{ 7, 8 }, /* Digit 2 pins in order*/
										{ 53, 38 }, /* DIgit 3 pins in order */
										{ 10, 11 } /* DIgit 3 pins in order */
};

/* This function initialize the Segment LCD on FRDM-KL46Z board */
void slcd_init(void)
{
	/* Enable SLCD and Port clocks */
	SIM->SCGC5 |=
			SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_SLCD_MASK;

	LCD->GCR |= LCD_GCR_PADSAFE_MASK; /* disable LCD pins while configuring */
	LCD->GCR &= ~LCD_GCR_LCDEN_MASK; /* disable driving LCD  */

	configure_lcd_pins(0); /* Pin muxing for slcd on FRDM-KL46 board */

	/* LCD control register */
	LCD->GCR = LCD_GCR_CPSEL_MASK | /* use capacitor charge pump */
				LCD_GCR_SOURCE_MASK | /* Use alternate clock source */
				LCD_GCR_ALTSOURCE(0) | /* Use alternate clock option 0 */
				LCD_GCR_ALTDIV(0) | /* alternate clock divider = 1 */
				LCD_GCR_DUTY(3) | /* 1/4 duty cycle */
				LCD_GCR_LADJ(3) | /* slowest clock source for capacitor charge pump */
				//LCD_GCR_FFR_MASK | /* use fast frame rate */
				LCD_GCR_LCDDOZE(0) | /* allow running in stop mode */
				LCD_GCR_LCLK(4) | /* for getting frame freq = 32, assuming LCD clock = 32kHz */
				LCD_GCR_RVEN_MASK | /* Enable regulated voltage and trim */
				LCD_GCR_RVTRIM(8) |
				LCD_GCR_VSUPPLY_MASK;

	LCD->AR = 	0; /* Disable blink  */

	/* Enable LCD pins for FRDM-KL46 board */
	LCD->PEN[0] = 	(1 << 7) | /* LCD_P7 = FP Digit 2 (D,E,G,F) */
					(1 << 8) | /* LCD_P8  = FP Digit 2 (DP,C,B,A)*/
					(1 << 10) | /* LCD_P10 = FP Digit 4 (D,E,G,F)*/
					(1 << 11) | /* LCD_P11 = FP Digit 4 (COL,C,B,A) */
					(1 << 17) | /* LCD_P17 = FP Digit 1 (DP,C,B,A) */
					(1 << 18) | /* LCD_P18 = BP 4 */
					(1 << 19); /* LCD_P19 = BP 3 */

	LCD->PEN[1] = (1 << 5) | /* LCD_P37 = FP Digit 1 (D,E,G,F) */
					(1 << 6) | /* LCD_P38  = FP Digist 3 (DP,C,B,A) */
					(1 << 8) | /* LCD_P40 = BP 1 */
					(1 << 20) | /* LCD_P52 = BP 2 */
					(1 << 21); /* LCD_P53 = FP Digit 3 (D,E,G,F)*/

	/* Configure backplane and frontplane pins for FRDM-KL46 board */
	LCD->BPEN[0] = (1 << 18) | (1 << 19); /* LCD_P18 and LCD_P19 are back plane pins */
	LCD->BPEN[1] = (1 << 8) | (1 << 20); /* LCD_P40 and LCD_P52 are backplane pins */

	/* Initalize waveform registers to show a blank display */
	LCD->WF[0] = 0; /* Pins 3 to 0 not used */
	LCD->WF[1] = LCD_WF_WF7(0x0); /* LCD_P7 off */
	LCD->WF[2] = LCD_WF_WF8(0x0) | /* LCD_P8 off */
	LCD_WF_WF10(0x0) | /* LCD_P10 off */
	LCD_WF_WF11(0x0); /* LCD_P11 off */
	LCD->WF[3] = 0; /* Pins 12 to 15 not used */
	LCD->WF[4] = LCD_WF_WF17(0x0) | /* LCD_P17 off */
	LCD_WF_WF18(0x88) | /* Backplane pin LCD_P18(BP4) active during H and D phases */
	LCD_WF_WF19(0x44); /* Backplane pin LCD_P19(BP3) active during G and C phases */
	LCD->WF[5] = 0; /* Pins 20 to 23 not used */
	LCD->WF[6] = 0; /* Pins 24 to 27 not used */
	LCD->WF[7] = 0; /* Pins 28 to 31 not used */
	LCD->WF[8] = 0; /* Pins 32 to 35 not used */
	LCD->WF[9] = LCD_WF_WF37(0x0) | /* LCD_P37 off */
	LCD_WF_WF38(0x0); /* LCD_P38 off */
	LCD->WF[10] = LCD_WF_WF40(0x11); /* BP pin LCD_P40 drives A and E phases */
	LCD->WF[11] = 0; /* pins 44 to 47 not used */
	LCD->WF[12] = 0; /* pins 48 to 51 not used */
	LCD->WF[13] = LCD_WF_WF52(0x22) | /* BP pin PCD_P52 drives B and F phases */
	LCD_WF_WF53(0); /* LCD_P53 off */
	LCD->WF[14] = 0; /* Pins 56 to 59 not used */
	LCD->WF[15] = 0; /* Pins 60 to 63 not used */

	/* Disable Pad safe bit and enable LCD driver */
	LCD->GCR &= ~LCD_GCR_PADSAFE_MASK;
	LCD->GCR |= LCD_GCR_LCDEN_MASK;

}

/* Functions to drive a digit to a particular value
 *
 * 	Digit: 0 - 3 position of the digit (0 - leftmost in the display, DIG 1)
 * 	Value: 0x0 to 0xF
 */
void slcd_set_digit(uint32_t digit, uint32_t val)
{
	if ((digit > 3) || (val > 0xF))
		return;

	switch (val) {
		case 0x0:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D | SEG_E | SEG_F;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A | SEG_B | SEG_C;
			break;

		case 0x1:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_NONE;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_B | SEG_C;
			break;

		case 0x2:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D | SEG_G | SEG_E;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A | SEG_B;
			break;

		case 0x3:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D | SEG_G;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A | SEG_B | SEG_C;
			break;

		case 0x4:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_F | SEG_G;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_B | SEG_C;
			break;

		case 0x5:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_F | SEG_G | SEG_D;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A | SEG_C;
			break;

		case 0x6:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D | SEG_E | SEG_F | SEG_G;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A | SEG_C;
			break;

		case 0x7:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_NONE;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A | SEG_B | SEG_C;
			break;

		case 0x8:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D | SEG_E | SEG_F | SEG_G;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A | SEG_B | SEG_C;
			break;

		case 0x9:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D | SEG_F | SEG_G;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A | SEG_B | SEG_C;
			break;

		case 0xA:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_E | SEG_F | SEG_G;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A | SEG_B | SEG_C;
			break;

		case 0xB:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D | SEG_E | SEG_F | SEG_G;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_C;
			break;

		case 0xC:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D | SEG_E | SEG_F;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A;
			break;

		case 0xD:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D | SEG_E | SEG_G;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_B | SEG_C;
			break;

		case 0xE:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_D | SEG_E | SEG_F | SEG_G;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A;
			break;

		case 0xF:
			LCD->WF8B[lcd_fp_pins[digit][0]] = SEG_E | SEG_F | SEG_G;
			LCD->WF8B[lcd_fp_pins[digit][1]] = SEG_A;
			break;

		default:
			break;

	}
}

/* Function to clear a digit at given position
 * 	digit : clear this digit
 * Note: does not clear decimal point or colon
 */
void slcd_clear_digit(uint32_t digit)
{
	if(digit < 4) {
		LCD->WF8B[lcd_fp_pins[digit][0]] = 0x0;
		LCD->WF8B[lcd_fp_pins[digit][1]] &= ~(SEG_A|SEG_B|SEG_C);
	}
}

/* Funtion to set decimal point at given position
 * 	pos: 0 to 2 (0 => leftmost in the diplay, DP 1)
 */
void slcd_set_dp(uint32_t pos)
{
	if (pos < 3) {
		LCD->WF8B[lcd_fp_pins[pos][1]] |= SEG_DP;
	}
}


/* Funtion to clear decimal point at given position
 * 	pos: 0 to 2 (0 => leftmost in the diplay, DP1)
 */
void slcd_clear_dp(uint32_t pos)
{
	if (pos < 3) {
		LCD->WF8B[lcd_fp_pins[pos][1]] &= ~SEG_DP;
	}
}


/* Funtion to set colon segment */
void slcd_set_colon(void)
{
	LCD->WF8B[lcd_fp_pins[3][1]] |= SEG_COL;
}


/* Funtion to clear colon segment */
void slcd_clear_colon(void)
{
	LCD->WF8B[lcd_fp_pins[3][1]] &= ~SEG_COL;
}

/* Function to display a number in hex format
 * 	num : 16-bit number
 */
void slcd_display_hex(uint16_t num)
{
	slcd_set_digit(0, (num & 0xF000) >> 12);
	slcd_set_digit(1, (num & 0xF00) >> 8);
	slcd_set_digit(2, (num & 0xF0) >> 4);
	slcd_set_digit(3, num & 0xF);
}

/* Funtion to display decimal number (no leading zeros)
 * 	num : number less than 10000
 */
void slcd_display_decimal(uint32_t num)
{
	uint32_t digit;
	bool lead_zero = false;

	digit = num/1000;
	if(!digit) {
		lead_zero = true;
		slcd_clear_digit(0);
	}
	else {
		slcd_set_digit(0, digit);
	}

	num -= digit*1000;
	digit = num/100;
	if(!digit && (true == lead_zero)) {
		slcd_clear_digit(1);
	}
	else {
		slcd_set_digit(1, digit);
		lead_zero = false;
	}

	num -= digit*100;
	digit = num/10;
	if(!digit && (true == lead_zero)) {
		slcd_clear_digit(2);
	}
	else {
		slcd_set_digit(2, digit);
		lead_zero = false;
	}

	num -= digit*10;
	digit = num;
	slcd_set_digit(3, digit);
}



/* Function to diplay time as min:sec
 * 	hour - hours (<24)
 * 	min - minutes (<60)
 */
void slcd_display_time(uint32_t hour, uint32_t min)
{
	if((hour > 23) || (min > 59)) {
		return;
	}
	slcd_set_digit(0, hour/10);
	slcd_set_digit(1, hour%10);
	slcd_set_colon();
	slcd_set_digit(2, min/10);
	slcd_set_digit(3, min%10);
}
