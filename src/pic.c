#include <sys/pic.h>
#include <sys/io.h>
#include <stdint.h>

#define ICW1_PIC1 0x11 /* master/slave config, expect ICW4 */
#define ICW1_PIC2 0x11

#define ICW2_PIC1 0x20 /* idt offset */
#define ICW2_PIC2 0x28

#define ICW3_PIC1 0x04 /* line is connected to slave */
#define ICW3_PIC2 0x02 /* irq on master this is connected to */

#define ICW4_PIC1 0x05 /* master PIC, 8086 mode */
#define ICW4_PIC2 0x01 /* 8086 mode */

void pic_init(void)
{

	outb(PIC1, ICW1_PIC1);
	outb(PIC2, ICW1_PIC2);

	outb(PIC1_DATA, ICW2_PIC1);
	outb(PIC2_DATA, ICW2_PIC2);

	outb(PIC1_DATA, ICW3_PIC1);
	outb(PIC2_DATA, ICW3_PIC2);

	outb(PIC1_DATA, ICW4_PIC1);
	outb(PIC2_DATA, ICW4_PIC2);

	outb(PIC1_DATA, 0xff);
	outb(PIC2_DATA, 0xff);

}

void pic_remap(void)
{
	outb(PIC1, 0x11);
	outb(PIC2, 0x11);
	outb(PIC1_DATA, 0x20);
	outb(PIC2_DATA, 0x28);
	outb(PIC1_DATA, 0x04);
	outb(PIC2_DATA, 0x02);
	outb(PIC1_DATA, 0x01);
	outb(PIC2_DATA, 0x01);
	outb(PIC1_DATA, 0x00);
	outb(PIC2_DATA, 0x00);
}
