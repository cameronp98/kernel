#ifndef SYS_KBD_H
#define SYS_KBD_H

#define KBD_EOI -1

void kbd_init(void);

char kbd_getc(void);
void kbd_retc(char c);

void kbd_gets(char *buffer);

#endif /* SYS_KBD_H */
