#ifndef SYS_IDT_H
#define SYS_IDT_H

#include <stdint.h>

typedef struct idt_entry
{
	uint16_t base_lo;
	uint16_t sel;
	uint8_t zero;
	uint8_t flags;
	uint16_t base_hi;
} idt_entry_t;

struct idt_ptr
{
	uint16_t limit;
	idt_entry_t *base;
} __attribute__((packed));

typedef struct idt_ptr idt_ptr_t;


void enable_interrupts(void);

void disable_interrupts(void);

void idt_init(void);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif /* SYS_IDT_H */
