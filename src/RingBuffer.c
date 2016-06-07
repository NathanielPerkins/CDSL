/*
 * RingBuffer.c
 *
 *  Created on: 07/06/2016
 *      Author: nathanjp
 */

#include "RingBuffer.h"



void rb_init (struct ring_b* buf, int8_t length) {
	buf->length = length;
	buf->data = malloc(length*sizeof(buffer_t));
	buf->start = &(buf->data[0]);
	buf->end = &(buf->data[0]);
}

void rb_push (struct ring_b* buf, int8_t data) {
	if (buf->end == buf->start - 1) {
		buf->start = (buf->start+1) % buf->length + buf->data[0];
	}
	buf->end = (buf->end+1) % buf->length + buf->data[0];
	buf->data[buf->end - 1] = data;
}

buffer_t rb_pop(struct ring_b* buf){
	if (buf->end == buf->start){
		return -1;
	}
	buffer_t data = buf->data[buf->end-1];
	buf->end -= 1;
	return data;
}


