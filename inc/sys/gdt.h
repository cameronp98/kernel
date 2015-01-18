#ifndef SYS_GDT_H
#define SYS_GDT_H

#include <stdint.h>

typedef struct gdt_entry
{
	uint16_t limit_lo;
	uint16_t base_lo;
	uint8_t base_mid;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_hi;
} gdt_entry_t;

struct gdt_ptr
{
	uint16_t limit;
	gdt_entry_t *base;
} __attribute__((packed));

typedef struct gdt_ptr gdt_ptr_t;


void gdt_init(void);

#endif /* SYS_GDT_H */
