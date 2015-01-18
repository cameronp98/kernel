#include <sys/panic.h>
#include <sys/isr.h>
#include <sys/vga.h>
#include <sys/pic.h>
#include <sys/io.h>
#include <stdint.h>

static const char *error_messages[] = {
	"Division by Zero",
	"Debugger",
	"NMI",
	"Breakpoint",
	"Overflow",
	"Bounds",
	"Invalid Opcode",
	"Coprocessor Not Available",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Invalid Task State Segment",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"reserved",
	"Math Fault",
	"Alignment Check",
	"Machine Check",
	"Floating-Point Exception",
};

irq_t irqs[16] = {0};

void isr_handler(registers_t regs)
{

	vga_log(WARN, "unhandled interrupt: %x\n", regs.int_no);

	panic(&regs);

	if (regs.int_no < 19)
	{
		vga_fputs(" (%s)", error_messages[regs.int_no]);
	}

	vga_putc('\n');

	asm("cli");
	asm("hlt");

}

void irq_install(uint8_t num, irq_t irq)
{
	irqs[num] = irq;
}

void irq_uninstall(uint8_t num)
{
	irqs[num] = 0;
}

void irq_handler(registers_t regs)
{

	regs.int_no -= 32;

	if (regs.int_no >= 8)
	{
		outb(PIC2, PIC_ACK);
	}

	outb(PIC1, PIC_ACK);

	irq_t handler = irqs[regs.int_no];

	if (handler != 0)
	{
		handler(&regs);
	}

}
