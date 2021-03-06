/*
 * http_utils.h
 *
 *  Created on: Jun 17, 2016
 *      Author: Visakhan
 */

#ifndef SOURCE_HTTP_UTILS_H_
#define SOURCE_HTTP_UTILS_H_

#include <stdint.h>

extern int http_get(const char *url);
extern int http_open_context(void);
extern int http_close_context(void);
extern int http_init(void);
extern int http_terminate(void);
int http_read(uint8_t *buf, int offset, int size);
extern int http_find_string(const char* str, uint8_t *page_buf, int bufsize);
extern int gprs_configure(void);


#endif /* SOURCE_HTTP_UTILS_H_ */
