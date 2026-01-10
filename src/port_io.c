#include <port_io.h>
#include <stdint.h>
void out_port(uint16_t port, uint8_t val){
	asm volatile (
		"outb %0, %1"
		:
		: "a" (val), "d" (port)
		:
	);
}

uint8_t in_port(uint16_t port){
	uint8_t recived_val;
	asm volatile (
		"inb %1, %0"
		: "=a" (recived_val)
		: "d" (port)
		:
	);
	return recived_val;
}