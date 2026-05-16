#include <stdarg.h>
#ifndef KERNEL_H
#define KERNEL_H

/* Kernel Print Formatted
 * Code from my old project
 */
void kprintf(const char *str, ...);

/* HALT CATCH FIRE
 * @warning DO NOT USE UNLESS YOU HAVE TO
 */
void hcf();

/* Initialize all important kernel stuff */
void kernel_init_all();
#endif
