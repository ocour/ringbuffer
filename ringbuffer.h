#pragma once

/*
	Created using ->
	https://www.snellman.net/blog/archive/2016-12-13-ring-buffers/
*/

#include <stdint.h>
#include <stdio.h>

/* Can only be a power of two(2) numbers, for example 2^6 = 64 */
#define RINGBUFFER_LENGTH 1024

typedef struct {
	uint8_t buffer[RINGBUFFER_LENGTH];
#if RINGBUFFER_LENGTH < 255
	uint8_t read, write;
#else 
	uint16_t read, write;
#endif
} Ringbuffer;

typedef enum {
	RINGBUFFER_OK = 0x0,
	RINGBUFFER_FULL,
	RINGBUFFER_NO_SUFFICIENT_SPACE,
} Ringbuffer_Status;

uint8_t Ringbuffer_empty(Ringbuffer* buf);
uint16_t Ringbuffer_freespace(Ringbuffer* buf);
//void push(Ringbuffer* buf, uint8_t val);
//void shift(Ringbuffer* buf, uint8_t* data);

uint16_t Ringbuffer_read(Ringbuffer* buf, uint8_t* data, uint16_t len);
uint8_t Ringbuffer_write(Ringbuffer* buf, uint8_t* data, uint16_t len);

void Ringbuffer_init(Ringbuffer* buf);
void Ringbuffer_print(Ringbuffer* buf);
