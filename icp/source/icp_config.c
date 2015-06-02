
#include <stdint.h>
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "dbg.h"

typedef struct memory_bank_ts{
	uint8_t mem[((64*1024)-1)];
	uint8_t *p_first_free;;
} memory_bank_t;

memory_bank_t my_memory;

void *my_malloc(uint8_t len) {
	uint8_t *ptr = my_memory.p_first_free;
	my_memory.p_first_free += len;
	return ptr;
}

void my_free(uint8_t *ptr) {
	return;
}

void my_memmove(uint8_t *ptr) {
	return;
}

void my_memset(uint8_t *ptr) {
	return;
}


static uint16_t crc16_ccitt(uint16_t crc, uint8_t ser_data)
{
	crc  = (uint8_t)(crc >> 8) | (crc << 8);
	crc ^= ser_data;
	crc ^= (uint8_t)(crc & 0xff) >> 4;
	crc ^= (crc << 8) << 4;
	crc ^= ((crc & 0xff) << 4) << 1;

	return crc;
}
uint16_t crc16(const uint8_t *p, int len)
{
	int i;
	uint16_t crc = 0;

	for (i=0; i<len; i++)
		crc = crc16_ccitt(crc, p[i]);

	return crc;
}

