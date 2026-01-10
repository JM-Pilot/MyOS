.global gdt_flush
.extern gdt_ptr

gdt_flush:
	lgdtl [gdt_ptr]
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	jmp $0x08, $retflush
retflush:
	ret
