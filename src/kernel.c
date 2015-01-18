#include <sys/pit.h>
#include <sys/vga.h>
#include <sys/idt.h>
#include <sys/isr.h>
#include <sys/kbd.h>
#include <sys/gdt.h>
#include <string.h>

#define PROMPT_BUFFER_SIZE 64

void kernel_main(void)
{

	disable_interrupts();

	// initialise VGA
	vga_init(VGA_FG_DEFAULT, VGA_BG_DEFAULT);
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
	pit_init(PIT_FREQUENCY_DEFAULT);
	vga_fputs("%COK\n", COLOR_GREEN);

	// initialise Keyboard
	vga_log(INFO, "Initialising keyboard... ");
	kbd_init();
	vga_fputs("%COK\n", COLOR_GREEN);

	// done initialising
	vga_log(INFO, "Finished initialising\n");

	enable_interrupts();

	// start doing stuff!
	vga_fputs("[+%CToyKernel v0.0.1%O+] :: (C) Cameron Phillips 2014\n", COLOR_BLUE);

	char buffer[PROMPT_BUFFER_SIZE] = {0};

	while (1)
	{
		vga_puts("> ");
		memset(buffer, 0, PROMPT_BUFFER_SIZE);
		kbd_gets(buffer, PROMPT_BUFFER_SIZE);
		if (strcmp(buffer, "help") == 0)
		{
			vga_puts("There is no help to be found...\n");
		}
		else if (strcmp(buffer, "exit") == 0)
		{
			vga_log(WARN, "Shutting down.");
			pit_sleep(1000);
			vga_putc('.');
			pit_sleep(1000);
			vga_putc('.');
			break;
		}
		else if (strcmp(buffer, "clock") == 0)
		{
			vga_fputs("system timer: %d\n", pit_get_ticks());
		}
		else
		{
			vga_fputs("unrecognized command '%s'\n", buffer);
		}
	}

}
