.code32
.extern gdt_reg
.global gdt_load

gdt_load:
	lgdt gdt_reg
	ljmp $0x08, $.rel_cs
.rel_cs:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ret