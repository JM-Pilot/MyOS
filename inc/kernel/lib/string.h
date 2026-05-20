#include <stdint.h>
#include <stddef.h>
#ifndef STRING_H
#define STRING_H

void *memset(void *dest, int val, size_t len);
void *memcpy(void *dest, const void *src, size_t len);
void *memmove(void *dest, void *src, size_t len);
int memcmp(const void *a, const void *b, size_t count);
int strcmp(const char *p1, const char *p2);
int strncmp(const char *s1, const char *s2, size_t n);
#endif