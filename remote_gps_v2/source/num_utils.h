/*
 * num_utils.h
 *
 *  Created on: Jul 9, 2015
 *      Author: Visakhan
 */

#ifndef SOURCES_NUM_UTILS_H_
#define SOURCES_NUM_UTILS_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern void parse_decimal(int* output, const char *buf, int length);
extern void parse_float(float *output, const char *buf, int length);
extern int get_quoted_string(const uint8_t *source, uint8_t *dest, int limit);
extern int float_to_string(const float *num, int frac_len, uint8_t *buf);

#endif /* SOURCES_NUM_UTILS_H_ */
