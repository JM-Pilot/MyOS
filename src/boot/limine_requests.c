#include <boot/limine_requests.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdbool.h>
#include <boot/limine.h>


__attribute__((used, section(".limine_requests")))
volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(4);

__attribute__((used, section(".limine_requests")))
volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};
