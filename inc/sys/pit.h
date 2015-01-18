#ifndef SYS_TIMER_H
#define SYS_TIMER_H

#include <stdint.h>

#define PIT_CLOCKS_PER_SEC 1193180

void pit_init(uint32_t freq);

uint32_t pit_get_ticks(void);

#endif /* SYS_TIMER_H */
