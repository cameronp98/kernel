#include <sys/pit.h>
#include <sys/vga.h>
#include <sys/idt.h>
#include <sys/isr.h>
#include <sys/kbd.h>
#include <sys/gdt.h>

#define SYSTEM_TIMER_FREQ 50

void kernel_main(void)
{

	disable_interrupts();

	// initialise VGA
	vga_init();
	vga_log(INFO, "VGA Initialised\n");

	// initialise GDT
	vga_log(INFO, "Initialising GDT... ");
	gdt_init();
	vga_fputs("%COK\n", COLOR_GREEN);

	// initialise IDT
	vga_log(INFO, "Initialising IDT... ");
	idt_init();
	vga_fputs("%COK\n", COLOR_GREEN);

	vga_log(INFO, "Initialising PIT... ");
	pit_init(SYSTEM_TIMER_FREQ);
	vga_fputs("%COK\n", COLOR_GREEN);

	// initialise Keyboard
	vga_log(INFO, "Initialising keyboard... ");
	kbd_init();
	vga_fputs("%COK\n", COLOR_GREEN);

	// done initialising
	vga_log(INFO, "Finished initialising\n");

	enable_interrupts();

	// start doing stuff!
	vga_fputs("[+%CMoonOS v0.1%O+] :: (C) Cameron Phillips 2014\n", COLOR_BLUE);

	vga_puts("> ");
	while (1)
	{
		vga_putc(kbd_getc());
	}


	for (;;);

}
