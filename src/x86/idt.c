#include <x86/idt.h>

__attribute__((aligned(0x10)))
idt_entry_t idt[IDT_MAX_VECTORS];

idtr_t idtr;

bool vectors[IDT_MAX_VECTORS];

void exception_handler() {
	asm volatile ("cli");
	for (;;){
		asm volatile ("hlt");
	}
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
	idt_entry_t* descriptor = &idt[vector];

	descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
	descriptor->kernel_cs      = 0x08;
	descriptor->attributes     = flags;
	descriptor->isr_high       = (uint32_t)isr >> 16;
	descriptor->reserved       = 0;
}

void idt_init() {
	idtr.base = (uintptr_t)&idt[0];
	idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_VECTORS - 1;
	// you may have trouble here 
	for (uint8_t vector = 0; vector < 32; vector++) {
		idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
		vectors[vector] = true;
	}

	__asm__ volatile ("lidt %0" : : "m"(idtr));
	__asm__ volatile ("sti");
}

