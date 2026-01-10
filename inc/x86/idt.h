#ifndef IDT_H
#define IDT_H
#define IDT_MAX_VECTORS 256
#include <stdint.h>
#include <stdbool.h>
typedef struct {
	uint16_t    isr_low;
	uint16_t    kernel_cs;
	uint8_t     reserved;
	uint8_t     attributes;
	uint16_t    isr_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

__attribute__((aligned(0x10))) 
extern idt_entry_t idt[IDT_MAX_VECTORS];

extern idtr_t idtr;

extern bool vectors[IDT_MAX_VECTORS];

extern void* isr_stub_table[];

__attribute__((noreturn))
void exception_handler(void);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_init(void);
#endif 