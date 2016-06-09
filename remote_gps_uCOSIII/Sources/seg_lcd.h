/*
 * seg_lcd.h
 *
 *  Created on: Jun 3, 2016
 *      Author: Visakhan
 */

#ifndef SOURCES_SEG_LCD_H_
#define SOURCES_SEG_LCD_H_

#include "MKL46Z4.h"
#include "stdbool.h"

/* Front plane waveform bits for each segments (for FRDM-KL46 board. Refer LCD datasheet) */
#define SEG_D		0x11
#define SEG_E		0x22
#define SEG_G		0x44
#define SEG_F		0x88
#define SEG_DP		0x11
#define SEG_COL		0x11
#define SEG_C		0x22
#define SEG_B		0x44
#define SEG_A		0x88
#define SEG_NONE	0x00

/* Funtions */
void slcd_init(void);
void slcd_set_digit(uint32_t digit, uint32_t val);
void slcd_clear_digit(uint32_t digit);
void slcd_set_dp(uint32_t pos);
void slcd_clear_dp(uint32_t pos);
void slcd_set_colon(void);
void slcd_clear_colon(void);
void slcd_diplay_hex(uint16_t num);
void slcd_display_time(uint32_t hour, uint32_t min);
void slcd_display_decimal(uint32_t num);


#endif /* SOURCES_SEG_LCD_H_ */
