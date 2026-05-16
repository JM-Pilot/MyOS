#include "idt.h"
#ifndef IRQ_H
#define IRQ_H

void irq_install_handler(int irq, void (*handler)(struct registers *r));
void irq_uninstall_handler(int irq);
void irq_remap(void);
void irq_handler(struct registers *reg);
void irq_init();
#endif