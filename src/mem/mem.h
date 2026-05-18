#include "../entry/multiboot.h"
#include <stdint.h>
#ifndef MEM_H
#define MEM_H

#define HEAP_SIZE 0x100000
#define BLOCK_SIZE 512

#define BLOCK_COUNT (HEAP_SIZE / BLOCK_SIZE)

extern uint8_t bitmap[BLOCK_COUNT / 8];
extern uint8_t *heap_start;
void mem_init(struct multiboot_info *mb_i);
uint8_t* mem_alloc();
void mem_free();
#endif