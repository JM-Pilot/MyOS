#include <stdint.h>
#include "asm.h"
#include "pit.h"
#include "idt.h"
#include "../../drivers/vga.h"
#include "irq.h"
void timer_phase(int hz){
	int divisor = 1193180 / hz;
	outb(0x43, 0x36);
	outb(0x40, divisor & 0xFF);
	outb(0x40, divisor >> 8);
}

int ticks = 0;

void pit_handler(struct registers *r){
	ticks++;
}

int pit_get_ticks(){
	return ticks;
}
void pit_install(){
	irq_install_handler(0, pit_handler);
}

