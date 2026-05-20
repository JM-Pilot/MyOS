#include <stdint.h>
#include "idt.h"
#include "irq.h"
#include <kernel/kernel.h>
#include "../../kernel/console.h"

const char *exception_messages[] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
};
void isr_exception_handler(struct registers *reg){
	
	if (reg->int_no >= 32){
		irq_handler(reg);
	}
	if (reg->int_no < 32){
		console_main.cursor_x = 0;
		console_main.cursor_y = 0;
		console_main.fg = 0xFF0000;
		kprintf("INTERRUPT REACHED!\tERROR: %d\t(%s)\n", reg->int_no, (reg->int_no < 19 ? exception_messages[reg->err_code] : "reserved"));
		kprintf("REBOOT YOUR COMPUTER\n");
		kprintf("EAX: %x, ECX: %x, EDX: %x, EBX: %x\n", 
			reg->eax, reg->ecx, reg->edx, reg->ebx);
		kprintf("ESP: %x, EBP: %x, ESI: %x, EDI: %x\n",
			reg->esp, reg->ebp, reg->esi, reg->edi);
		kprintf("GS: %x, FS: %x, ES: %x, DS: %d\n",
			reg->gs, reg->fs, reg->es, reg->ds);
		kprintf("EIP: %x, CS %x", reg->eip, reg->cs);
		hcf();
	}
}