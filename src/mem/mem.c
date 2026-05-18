#include "../entry/multiboot.h"
#include <stdint.h>
#include "mem.h"
#include <kernel/lib/string.h>
uint8_t bitmap[BLOCK_COUNT / 8];
uint8_t *heap_start;

extern uint32_t _kernel_end;
void mem_init(struct multiboot_info *mb_i){
	memset(bitmap, 0, BLOCK_COUNT / 8);
	heap_start = (uint8_t *)&_kernel_end;
	multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)mb_i->mmap_addr;
	while ((uint32_t)mmap < mb_i->mmap_addr + mb_i->mmap_length){
		if (mmap->type != MULTIBOOT_MEMORY_AVAILABLE){
			uint32_t start = mmap->addr / BLOCK_SIZE;
			uint32_t end = (mmap->addr + mmap->len) / BLOCK_SIZE;
			for (uint32_t i = start; i < end && i < BLOCK_COUNT; i++){
				bitmap[i / 8] |= (1 << (i % 8));
			} 
		}
		mmap = (multiboot_memory_map_t *)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
	}
}
uint8_t* mem_alloc(){
	for (int i = 0; i < BLOCK_COUNT; i++){
		if (!(bitmap[i / 8] & (1 << (i % 8)))){
			bitmap[i / 8] |= (1 << (i % 8));
			return heap_start + (i * BLOCK_SIZE);
		}
	}
	return NULL;
}
void mem_free(uint8_t *addr){
	uint32_t i = (addr - heap_start) / BLOCK_SIZE;
	bitmap[i / 8] &= ~(1 << (i % 8));
}