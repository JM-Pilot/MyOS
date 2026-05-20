#include <kernel/kernel.h>
#include "../kernel/console.h"
#include <kernel/lib/stdio.h>
#include <kernel/lib/string.h>
#include "bugshell/shell.h"
#include "../entry/multiboot.h"
#include "../mem/pmm.h"
void hcf(){
	asm volatile ("cli");
	for (;;)
		asm volatile ("hlt");
}
void kernel_main(struct multiboot_info *mb_i){
	if (mb_i == NULL) while(1);
	uint32_t *test = (uint32_t *)mb_i->framebuffer_addr;
	test[0] = 0xFFFFFF;
	asm volatile ("cli");
	kernel_init_all(mb_i);
	asm volatile ("sti");

	while (1) {
		sh_mn_loop();
	}
	
	hcf();
}