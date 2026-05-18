#include <stdint.h>
#include <stddef.h>
#include <kernel/lib/string.h>

void *memset(void *dest, int val, size_t len){
	uint8_t *ptr = (uint8_t*)dest;
	while (len-- > 0)
		*ptr++ = val;
	return dest;
}