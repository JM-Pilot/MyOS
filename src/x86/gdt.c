#include <x86/gdt.h>
#include <stdint.h>
#include <vga.h>
gdt_entry_t gdt[3];
gdt_ptr_t gdt_ptr;

void gdt_set_entry(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}



void gdt_init(){
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
	gdt_ptr.base = (uint32_t)&gdt;

	gdt_set_entry(0, 0, 0, 0, 0);                // Null segment

	gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment, 0x08 offset from GDT base

	gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment, 0x10 offset from GDT base

	gdt_flush();
	print_str("GDT initialized\n");
}