/* GDT_AS.S */
.global gdt_flush
.extern gdt_ptr

gdt_flush:
	lgdt [gdt_ptr]
	/* 0x10 is from data segment */
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	/* 0x08 is from code segment */
	pushq $0x08
	leaq ret(%rip), %rax
	pushq %rax
	lretq
ret:
	ret
