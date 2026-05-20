#include <kernel/kernel.h>
#include "../drivers/video/vgafb.h"
#include "../drivers/video/psf.h"
#include "../arch/x86/gdt.h"
#include "../arch/x86/idt.h"
#include "../arch/x86/irq.h"
#include "../arch/x86/pit.h"
#include "../arch/x86/kbd.h"
#include "bugshell/shell.h"
#include "../mem/pmm.h"
#include "../mem/heap.h"
#include "console.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

uint8_t mem[4096];
heap_bm_t heap;	
void kernel_init_all(struct multiboot_info *mb_i){
	vgafb_init(mb_i);
	console_init();
	kprintf("VGA FRAMEBUFFER Initialized\n");
	kprintf("%dx%d\n", mb_i->framebuffer_width, mb_i->framebuffer_height);
	kprintf("%dx%d\n", fb_width, fb_height);

	gdt_init();
	kprintf("GDT Initialized\n");

	idt_init();
	kprintf("IDT Initialized\n");
	irq_init();
	kprintf("IRQ Initialized\n");
	pit_install();
	kprintf("PIT Installed\n");
	kbd_install();
	kprintf("KBD Installed\n");

	pmm_init(mb_i);
	kprintf("PMM Initialized\n");

	heap_init(&heap);
	heap_add_block(&heap, (uintptr_t)mem, 4096, 16);
	kprintf("HEAP Initialized\n");
	
	kprintf("\nWelcome to MyOS / JM-Pilot OS\nThis is still in development expect bugs\n\n");

	shell_init();
}