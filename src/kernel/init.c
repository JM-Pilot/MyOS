#include "kernel.h"
#include "../drivers/vga.h"
#include "../arch/x86/gdt.h"
#include "../arch/x86/idt.h"
#include "../arch/x86/irq.h"
#include "../arch/x86/pit.h"
#include "../arch/x86/kbd.h"
void kernel_init_all(){
	vga_init();
	kprintf("VGA Initialized\n");
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
}