#include "../../src/entry/multiboot.h"
#include "../../src/mem/heap.h"
#include <stdarg.h>
#ifndef KERNEL_H
#define KERNEL_H

extern uint8_t mem[4096];
extern heap_bm_t heap;

/* Kernel Print Formatted
 * Code from my old project
 */
void kprintf(const char *str, ...);

/* HALT CATCH FIRE
 * @warning DO NOT USE UNLESS YOU HAVE TO
 */
void hcf();

/* Initialize all important kernel stuff */
void kernel_init_all(struct multiboot_info *mb_i);

/* i Panik */
void panic(const char *msg);
#endif
