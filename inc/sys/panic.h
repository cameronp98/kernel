#ifndef SYS_PANIC_H
#define SYS_PANIC_H

#include <sys/isr.h>

void dump_regs(registers_t *regs);

void panic(registers_t *regs);

#endif /* SYS_PANIC_H */
