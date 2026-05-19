#include "../entry/multiboot.h"
#include <stdint.h>
#ifndef PMM_H
#define PMM_H

#define HEAP_SIZE 0x100000
#define BLOCK_SIZE 512

#define BLOCK_COUNT (HEAP_SIZE / BLOCK_SIZE)

extern uint8_t bitmap[BLOCK_COUNT / 8];
extern uint8_t *heap_start;
void pmm_init(struct multiboot_info *mb_i);
uint8_t* pmm_alloc();
void pmm_free();
#endif