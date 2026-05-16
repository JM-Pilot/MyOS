#include "gdt.h"
#include <stdint.h>

extern void gdt_load();
struct gdt_desc gdt[3];
struct gdtr gdt_reg;

void gdt_set_desc(uint8_t n, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags){
	gdt[n].base_low = base & 0xFFFF;
	gdt[n].base_mid = (base >> 16) & 0xFF;
	gdt[n].base_mid = (base >> 24) & 0xFF;

	gdt[n].limit_low = limit & 0xFFFF;
	gdt[n].flags = ((limit >> 16) & 0x0F) | (flags & 0xF0);

	gdt[n].access_byte = access;
}
void gdt_init(){
	gdt_reg.size = (sizeof(struct gdt_desc) * 3) - 1;
	gdt_reg.offset = (uint32_t)&gdt;
	gdt_set_desc(0, 0, 0, 0, 0);
	gdt_set_desc(1, 0, 0xFFFFF, 0x9A, 0xCF);
	gdt_set_desc(2, 0, 0xFFFFF, 0x92, 0xCF);
	
	gdt_load();
}