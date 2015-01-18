#ifndef SYS_VGA_H
#define SYS_VGA_H

#include <stdarg.h>
#include <stdint.h>

typedef enum vga_color
{
	COLOR_BLACK,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_MAGENTA,
	COLOR_BROWN,
	COLOR_LIGHT_GREY,
	COLOR_DARK_GREY,
	COLOR_LIGHT_BLUE,
	COLOR_LIGHT_GREEN,
	COLOR_LIGHT_CYAN,
	COLOR_LIGHT_RED,
	COLOR_LIGHT_MAGENTA,
	COLOR_LIGHT_BROWN,
	COLOR_WHITE
} vga_color_t;

typedef enum
{
	GOOD, INFO, WARN
} vga_logtype_t;

/* housekeeping */

void vga_init(void);

void vga_clear(void);
void vga_scroll(void);

void vga_setfg(vga_color_t color);
void vga_setbg(vga_color_t color);

uint8_t vga_getfg(void);
uint8_t vga_getbg(void);

/* string output */

void vga_putc(char c);

void vga_puts(char *s);
void vga_fputs(char *f, ...);
void vga_vfputs(char *f, va_list args);

void vga_log(vga_logtype_t type, char *f, ...);

// void vga_putf(char *f, ...);

/* numerical output */

void vga_puti(int32_t x, uint8_t base);
void vga_putd(int32_t x);
void vga_putx(int32_t x);
void vga_putb(int32_t x);


#endif /* SYS_VGA_H */
