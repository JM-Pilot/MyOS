#include "kernel.h"
#include "../drivers/vga.h"
#include "kernel.h"
void hcf(){
	asm volatile ("cli");
	for (;;)
		asm volatile ("hlt");
}
void kernel_main(){
	asm volatile ("cli");
	kernel_init_all();
	asm volatile ("sti");
	hcf();
}