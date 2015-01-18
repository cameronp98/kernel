#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>

#define NULL ((void *)0)

void *memset(void *dst, int32_t x, size_t n);

void *memcpy(void *dst, void *src, size_t n);

void *memmove(void *dst, void *src, size_t n);

int memcmp(void *ptr1, void *b, size_t ptr2);

int strcmp(char *str1, char *str2);

#endif /* STRING_H */
