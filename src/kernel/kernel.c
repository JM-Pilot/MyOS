#include "kernel.h"
#include "../drivers/vga.h"
#include "kernel.h"
#include <kernel/lib/stdio.h>
#include <kernel/lib/string.h>
#include "bugshell/shell.h"
void hcf(){
	asm volatile ("cli");
	for (;;)
		asm volatile ("hlt");
}
void kernel_main(){
	asm volatile ("cli");
	kernel_init_all();
	asm volatile ("sti");
	while (1) {
		sh_mn_loop();
	}
	
	hcf();
}