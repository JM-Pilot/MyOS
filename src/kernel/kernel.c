#include <kernel/kernel.h>
#include "../drivers/vga.h"
#include <kernel/lib/stdio.h>
#include <kernel/lib/string.h>
#include "bugshell/shell.h"
#include "../entry/multiboot.h"
#include "../mem/mem.h"
void hcf(){
	asm volatile ("cli");
	for (;;)
		asm volatile ("hlt");
}
void kernel_main(struct multiboot_info *mb_i){
	asm volatile ("cli");
	kernel_init_all(mb_i);
	asm volatile ("sti");
	
	while (1) {
		sh_mn_loop();
	}
	
	hcf();
}