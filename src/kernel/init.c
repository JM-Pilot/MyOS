#include "kernel.h"
#include "../drivers/vga.h"
#include "../arch/x86/gdt.h"
void kernel_init_all(){
	vga_init();
	kprintf("VGA Initialized\n");
	gdt_init();
	kprintf("GDT Initialized\n");
}