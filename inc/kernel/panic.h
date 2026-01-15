#ifndef PANIC_H
#define PANIC_H


void kernel_panic(const char* msg);

// Halt the cpu forever without warning. 
void cpu_haltf();
#endif