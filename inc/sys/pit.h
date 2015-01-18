#ifndef SYS_TIMER_H
#define SYS_TIMER_H

#include <stdint.h>

#define PIT_CLOCKS_PER_SEC 1193180
#define PIT_FREQUENCY_DEFAULT 1000

void pit_init(uint32_t frequency);

void pit_set_frequency(uint32_t frequency);

uint32_t pit_get_ticks(void);

void pit_sleep(uint32_t ticks);

#endif /* SYS_TIMER_H */
