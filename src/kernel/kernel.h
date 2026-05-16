#include <stdarg.h>
#ifndef KERNEL_H
#define KERNEL_H

void kprintf(const char *str, ...);
void hcf();
void kernel_init_all();
#endif
