#ifndef SYS_ISR_H
#define SYS_ISR_H

#include <stdint.h>

typedef struct registers {
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushad
	uint32_t int_no, err_code; // from `isr_stub`
	uint32_t eip, cs, eflags, useresp, ss; // pushed by int
} registers_t;

typedef struct registers registers_t;

typedef void (*irq_t)(registers_t *);

void irq_install(uint8_t num, irq_t irq);
void irq_uninstall(uint8_t num);

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif /* SYS_ISR_H */
