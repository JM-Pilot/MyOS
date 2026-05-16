#include "idt.h"
#include <stdint.h>

extern uint32_t isr_stub_table[32];

struct idtr idt_reg;
struct idt_desc idt[256];

void idt_set_desc(int n, uint32_t offset, uint16_t selector, uint8_t attributes){
	idt[n].offset_low = offset & 0xFFFF;
	idt[n].offset_high = (offset >> 16) & 0xFFFF;
	idt[n].attributes = attributes;
	idt[n].segment_selector = selector;
	idt[n].reserved = 0;
}
void idt_init(){
	idt_reg.size = (sizeof(struct idt_desc) * 256) - 1;
	idt_reg.offset = (uint32_t)&idt;

	for (uint8_t i = 0; i < 32; i++){
		idt_set_desc(i, isr_stub_table[i], 0x08, 0x8E);
	}
	asm volatile ("lidt %0" : : "m"(idt_reg));
}