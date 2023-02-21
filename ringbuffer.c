#include "ringbuffer.h"

/* Static function forward decleration */
static uint16_t Ringbuffer_mask(uint16_t val);
static uint8_t Ringbuffer_full(Ringbuffer* buf);
static uint16_t Ringbuffer_size(Ringbuffer* buf);

/* Used when incrementing Read and Write pointer/index */
static uint16_t Ringbuffer_mask(uint16_t val)
{
	return val & (RINGBUFFER_LENGTH - 1);
}

/*
	Checks whether Ringbuffer is full or not,
	1 if full, 0 if not
*/
static uint8_t Ringbuffer_full(Ringbuffer* buf)
{
	return Ringbuffer_size(buf) == RINGBUFFER_LENGTH;
}

/* Get size of Ringbuffer */
static uint16_t Ringbuffer_size(Ringbuffer* buf)
{
	return buf->write - buf->read;
}

/*
	Checks whether Ringbuffer is empty or not,
	1 if empty, 0 if not
*/
uint8_t Ringbuffer_empty(Ringbuffer* buf)
{
	return buf->read == buf->write;
}

/* Get freespace of Ringbuffer */
uint16_t Ringbuffer_freespace(Ringbuffer* buf)
{
	return RINGBUFFER_LENGTH - Ringbuffer_size(buf);
}

/*
// Writes one element
void push(Ringbuffer* buf, uint8_t val)
{
	if(!ringbuffer_full(buf))
		buf->buffer[ringbuffer_mask(buf->write++)] = val;
}
*/

/*
// Reads one element and returns it
void shift(Ringbuffer* buf, uint8_t* data)
{
	if(!ringbuffer_empty(buf))
		*data = buf->buffer[ringbuffer_mask(buf->read++)];
}
*/

/*
	Reads multiple elements,
	Returns counter which is equal to the amount of data read
*/
uint16_t Ringbuffer_read(Ringbuffer* buf, uint8_t* data, uint16_t len)
{
	uint16_t counter = 0;

	while (!Ringbuffer_empty(buf) && counter < len)
		data[counter++] = buf->buffer[Ringbuffer_mask(buf->read++)];

	return counter;
}

/*
	Writes multiple elements,
	Returns Ringbuffer_Status
*/
uint8_t Ringbuffer_write(Ringbuffer* buf, uint8_t* data, uint16_t len)
{
	uint16_t counter = 0;
	uint16_t freespace = Ringbuffer_freespace(buf);

	// if full return
	if (Ringbuffer_full(buf))
		return RINGBUFFER_FULL;
	else if (freespace < len)
		return RINGBUFFER_NO_SUFFICIENT_SPACE;

	while (counter < len)
		buf->buffer[Ringbuffer_mask(buf->write++)] = data[counter++];

	return RINGBUFFER_OK;
}

/* Initialize Ringbuffer */
void Ringbuffer_init(Ringbuffer* buf)
{
	buf->read = buf->write = 0;
}

/* Prints whole Ringbuffer, used for debugging and Testing */
void Ringbuffer_print(Ringbuffer* buf)
{
	printf("**********\n");
	for (int i = 0; i < RINGBUFFER_LENGTH; i++) {
		printf(
			"> %d %c%s\n", buf->buffer[i],
			(buf->read == i || (buf->read - RINGBUFFER_LENGTH) == i) ? '<' : ' ',
			(buf->write == i || (buf->write - RINGBUFFER_LENGTH) == i) ? "<-" : " ");
	}
	printf("**********\n");
}