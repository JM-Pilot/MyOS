#include "kernel.h"
#include "../drivers/vga.h"
void hcf(){
	asm volatile ("cli");
	for (;;)
		asm volatile ("hlt");
}
void kernel_main(){
	vga_init();
	hcf();
}