#include <kernel/kernel.h>
#include "../drivers/vga.h"
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
	asm volatile ("cli");
	kernel_init_all(mb_i);
	asm volatile ("sti");
	
	void *a = heap_alloc(&heap, 32);
	void *b = heap_alloc(&heap, 64);
	heap_free(&heap, a);
	void *c = heap_alloc(&heap, 16);
	kprintf("a = %x\n", a);
	kprintf("b = %x\n", b);
	kprintf("c = %x\n", c);
	kprintf("fblock = %x\n", heap.fblock);
	while (1) {
		sh_mn_loop();
	}
	
	hcf();
}