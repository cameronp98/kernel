#ifndef SYS_KBD_H
#define SYS_KBD_H

#include <stddef.h>

#define KBD_EOI -1

void kbd_init(void);

char kbd_getc(void);
void kbd_retc(char c);

void kbd_gets(char *buffer, size_t size);

#endif /* SYS_KBD_H */
