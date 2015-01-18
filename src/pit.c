#include <sys/pit.h>
#include <sys/vga.h>
#include <sys/isr.h>
#include <sys/io.h>
#include <stdint.h>
#include <stddef.h>

uint32_t pit_frequency;
uint32_t pit_ticks;

void pit_handler(registers_t *regs)
{
	pit_ticks++;
}

void pit_init(uint32_t freq)
{
	pit_frequency = freq;

	pit_ticks = 0;

	irq_install(0, &pit_handler);

	uint32_t divisor = PIT_CLOCKS_PER_SEC / pit_frequency;

	// @todo: replace hardcoded values w/ constants
	outb(0x43, 0x36);

	uint8_t lo = divisor & 0xff;
	uint8_t hi = (divisor >> 8) & 0xff;

	outb(0x40, lo);
	outb(0x40, hi);

}

uint32_t pit_get_ticks(void)
{
	return pit_ticks;
}

void pit_sleep(uint32_t ticks)
{
	uint32_t start = pit_ticks;

	while ((pit_ticks - start) < ticks)
	{
		// wait
	}

}
