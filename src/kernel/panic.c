#include <kernel/panic.h>
#include <kernel/tty.h>

void kernel_panic(const char* msg){
	write_str(msg, 0xFF0000);
	cpu_haltf();
}
void cpu_haltf(){
	asm volatile ("cli");
	for (;;){	// Halt the cpu forever
		asm volatile ("hlt");
	}
}