#include "idt.h"
#include "irq.h"
#include "asm.h"
#include "../../drivers/vga.h"
#include <stdint.h>

extern uint32_t irq_stub_table[16];
void *irq_routines[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

void irq_install_handler(int irq, void (*handler)(struct registers *r)){
	irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq){
    irq_routines[irq] = 0;
}


void irq_remap(void){
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}
void irq_handler(struct registers *reg){
	void (*handler)(struct registers *r) = irq_routines[reg->int_no - 32];
	if (handler) 
		handler(reg);
	if (reg->int_no >= 40)
		outb(0xA0, 0x20);
	outb(0x20, 0x20);
}
void irq_init(){
	irq_remap();
	for (int i = 0; i < 16; i++)
		idt_set_desc(32 + i, irq_stub_table[i], 0x08, 0x8E);
}
