#include <sys/panic.h>
#include <sys/vga.h>
#include <sys/isr.h>
#include <string.h>

void dump_regs(registers_t *regs)
{
	vga_log(INFO, "Register dump:\n");

	vga_log(INFO, "eax=%x\n", regs->eax);
	vga_log(INFO, "ebx=%x\n", regs->ebx);
	vga_log(INFO, "ecx=%x\n", regs->ecx);
	vga_log(INFO, "edx=%x\n", regs->edx);

}

void panic(registers_t *regs)
{

	vga_log(WARN, "Kernel Panic\n");

	if (regs != NULL)
	{
		dump_regs(regs);
	}

	__asm__ __volatile__ ("cli");
	__asm__ __volatile__ ("hlt");

}
