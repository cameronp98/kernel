#ifndef SYS_PIC_H
#define SYS_PIC_H

#include <stdint.h>

#define PIC1 0x20
#define PIC2 0xA0

#define PIC_ACK 0x20

#define PIC1_DATA (PIC1 + 1)
#define PIC2_DATA (PIC2 + 1)

void pic_init(void);

void pic_remap(void);

#endif /* SYS_PIC_H */
