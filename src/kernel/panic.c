#include <kernel/panic.h>


void cpu_haltf(){
	asm volatile ("cli");
	for (;;){	// Halt the cpu forever
		asm volatile ("hlt");
	}
}