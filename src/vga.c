#include <sys/vga.h>
#include <sys/io.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define VGA_MEM 0x000B8000

#define VGA_PORT_COMMAND 0x3D4
#define VGA_PORT_DATA    0x3D5

#define VGA_COMMAND_BYTE_HI 14
#define VGA_COMMAND_BYTE_LO 15

#define VGA_COLS 80
#define VGA_ROWS 25
#define VGA_LAST_ROW (VGA_COLS * (VGA_ROWS - 1))

#define VGA_FG_DEFAULT COLOR_LIGHT_GREY
#define VGA_BG_DEFAULT COLOR_BLACK

#define VGA_FG_INFO COLOR_CYAN
#define VGA_FG_GOOD COLOR_GREEN
#define VGA_BG_WARN COLOR_RED

#define PUTI_BUFFER_SIZE 32

uint16_t *vga_mem = (uint16_t *) VGA_MEM;

uint8_t vga_px, vga_py;
uint8_t vga_fg, vga_bg;

static void vga_make_entry(uint32_t i, int8_t c)
{
	vga_mem[i] = (vga_bg << 12) | (vga_fg << 8) | c;
}

static void vga_update_cursor(void)
{
	uint16_t pos = vga_px + vga_py * VGA_COLS;
	outb(VGA_PORT_COMMAND, VGA_COMMAND_BYTE_HI);
	outb(VGA_PORT_DATA, (pos >> 8) & 0xff);
	outb(VGA_PORT_COMMAND, VGA_COMMAND_BYTE_LO);
	outb(VGA_PORT_DATA, pos & 0xff);
}

void vga_init(void)
{
	vga_setfg(VGA_FG_DEFAULT);
	vga_setbg(VGA_BG_DEFAULT);
	vga_clear();
	vga_px = 0;
	vga_py = 0;
}

void vga_clear(void)
{

	for (size_t i = 0; i < VGA_COLS * VGA_ROWS; i++)
	{
		vga_make_entry(i, ' ');
	}

	vga_px = 0;
	vga_py = 0;

	vga_update_cursor();

}

void vga_scroll(void)
{

	for (uint8_t x = 0; x < VGA_COLS; x++)
	{
		for (uint8_t y = 0; y < VGA_ROWS - 1; y++)
		{
			const uint16_t pos = x + y * VGA_COLS;
			const uint8_t c = vga_mem[pos + VGA_COLS] & 0xff;
			vga_make_entry(pos, c);
		}
	}

	for (uint8_t i = 0; i < VGA_COLS; i++)
	{
		vga_make_entry(VGA_LAST_ROW + i, ' ');
	}

	vga_px = 0;
	vga_py = VGA_ROWS - 1;

	vga_update_cursor();

}

void vga_setfg(vga_color_t color)
{
	vga_fg = color & 0x0f;
}

void vga_setbg(vga_color_t color)
{
	vga_bg = color & 0x0f;
}

uint8_t vga_getfg(void)
{
	return vga_fg;
}

uint8_t vga_getbg(void)
{
	return vga_bg;
}

void vga_putc(char c)
{
	switch(c)
	{
		case '\n':
			vga_px = 0;
			vga_py++;
			break;
		case '\r':
			vga_px = 0;
			return;
		case '\b':
			if (vga_px > 0)
			{
				vga_px--;
			}
			else if (vga_py > 0)
			{
				vga_py--;
			}
			vga_make_entry(vga_px + vga_py * VGA_COLS, ' ');
			break;
		case '\0':
			return;
		default:
			vga_make_entry(vga_px + vga_py * VGA_COLS , c);
			vga_px++;
			break;
	}

	if (vga_px == VGA_COLS)
	{
		vga_px = 0;
		vga_py++;
	}

	if (vga_py == VGA_ROWS)
	{
		vga_scroll();
	}

	vga_update_cursor();

}

void vga_puts(char *str)
{
	while (*str != '\0')
	{
		vga_putc(*str++);
	}
}

void vga_vfputs(char *f, va_list args)
{
	uint8_t orig_fg = vga_fg;

	char c;
	while ((c = *f++) != '\0')
	{
		if (c == '%')
		{
			c = *f++;
			switch(c)
			{
				case '%': // percent
					vga_putc('%');
					break;
				case 'x': // hex
					vga_putx(va_arg(args, int32_t));
					break;
				case 'd': // decimal
					vga_putd(va_arg(args, int32_t));
					break;
				case 'b': // binary
					vga_putb(va_arg(args, int32_t));
					break;
				case 'c': // character
					vga_putc(va_arg(args, int32_t));
					break;
				case 's': // string
					vga_puts(va_arg(args, char *));
					break;
				case 'C': // color
					vga_setfg(va_arg(args, vga_color_t));
					break;
				case 'O': // restore original color
					vga_setfg(orig_fg);
					break;
				default:
					vga_puts("invalid format character '");
					vga_putc(c);
					vga_puts("'\n");
					return;
			}
		}
		else
		{
			vga_putc(c);
		}
	}

	vga_setfg(orig_fg);
}

void vga_fputs(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vga_vfputs(fmt, args);
	va_end(args);
}

void vga_log(vga_logtype_t type, char *fmt, ...)
{

	vga_putc('[');

	switch (type)
	{
		case GOOD:
			vga_fputs("%CGOOD", VGA_FG_GOOD);
			break;
		case INFO:
			vga_fputs("%CINFO", VGA_FG_INFO);
			break;
		case WARN:
			vga_fputs("%CWARN", VGA_BG_WARN);
			break;
	}

	vga_puts("] ");

	va_list args;
	va_start(args, fmt);
	vga_vfputs(fmt, args);
	va_end(args);


}

void vga_puti(int32_t x, uint8_t base)
{
	const char *digits = "0123456789abcdef";

	if (x < 0)
	{
		vga_putc('-');
		x *= -1;
	}

	switch(base)
	{
		case 16:
			vga_puts("0x");
			break;
		case 2:
			vga_puts("0b");
			break;
		default:
			break;
	}

	if (x == 0)
	{
		vga_putc('0');
		return;
	}

	uint8_t buffer[PUTI_BUFFER_SIZE];
	size_t i = 0;

	// push x's digits in order
	while (x > 0)
	{
		buffer[i++] = digits[x % base];
		x /= base;
	}

	// pop each character and print it
	while (i--)
	{
		vga_putc(buffer[i]);
	}
}

void vga_putd(int32_t x)
{
	vga_puti(x, 10);
}

void vga_putx(int32_t x)
{
	vga_puti(x, 16);
}

void vga_putb(int32_t x)
{
	vga_puti(x, 2);
}
