/*
 * RingBuffer.h
 *
 *  Created on: 07/06/2016
 *      Author: nathanjp
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>

typedef uint8_t buffer_t;

struct ring_b {
	int8_t length;
	buffer_t *start;
	buffer_t *end;
	buffer_t data[];
};

void rb_init(struct ring_b* buf, int8_t length);
void rb_push(struct ring_b* buf, int8_t data);
buffer_t rb_pop(struct ring_b* buf);



#endif /* RINGBUFFER_H_ */
