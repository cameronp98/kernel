#include <sys/kbd.h>
#include <sys/vga.h>
#include <sys/isr.h>
#include <sys/io.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define KBD_PORT_DATA 0x60

#define KBD_BUFFER_SIZE 1024

uint8_t kbd_buffer[KBD_BUFFER_SIZE];
size_t kbd_buffer_pos = 0;

uint8_t kbd_shift = 0;
uint8_t kbd_ctrl = 0;
uint8_t kbd_alt = 0;

const char kbd_layout_us[128] = {
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
	'9', '0', '-', '=', '\b',	/* Backspace */
	'\t',			/* Tab */
	'q', 'w', 'e', 'r',	/* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
	0,			/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
	'\'', '`',   0,		/* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
	'm', ',', '.', '/',   0,				/* Right shift */
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0, 0, 0, 0, 0, 0, 0, 0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',
	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* 79 - End key*/
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};

void kbd_handler(registers_t *regs)
{

	uint8_t scancode = inb(KBD_PORT_DATA);

	if (scancode & 0x80)
	{
		scancode -= 0x80;

		switch(scancode)
		{
			case 0x2a:
				kbd_shift = 0;
				break;
			case 0x1d:
				kbd_shift = 0;
				break;
			case 0x38:
				kbd_alt = 0;
				break;
		}

	}
	else
	{
		// try to add the character to the keyboard buffer
		if (kbd_buffer_pos < KBD_BUFFER_SIZE)
		{
			switch(scancode)
			{
				case 0x2a:
					kbd_shift = 1;
					break;
				case 0x1d:
					kbd_shift = 1;
					break;
				case 0x38:
					kbd_alt = 1;
					break;
				default:
					kbd_buffer[kbd_buffer_pos++] = kbd_layout_us[scancode];
			}
		}
		else
		{
			vga_log(WARN, "kbd_handler(): Keyboard buffer full\n");
		}
	}

}

void kbd_init(void)
{
	kbd_alt = 0;
	kbd_ctrl = 0;
	kbd_shift = 0;
	kbd_buffer_pos = 0;
	irq_install(1, &kbd_handler);
}

char kbd_getc(void)
{
	while (kbd_buffer_pos == 0)
	{
		// wait until a key is pressed
	}

	return kbd_buffer[--kbd_buffer_pos];

}

void kbd_retc(char c)
{
	if (kbd_buffer_pos < KBD_BUFFER_SIZE)
	{
		kbd_buffer[kbd_buffer_pos++] = c;
	}

	vga_log(WARN, "kbd_retc(): Keyboard buffer full\n");
}

void kbd_gets(char *buffer, size_t size)
{
	const char *buffer_start = buffer;

	char c;

	while ((c = kbd_getc()) != '\n' && c != '\0')
	{
		if (c == '\b') {
			if (buffer > buffer_start)
			{
				size++;
				*--buffer = 0;
				vga_putc('\b');
			}
		}
		else if (size > 0)
		{
			size--;
			*buffer++ = c;
			vga_putc(c);
		}
	}

	vga_putc('\n');

}
