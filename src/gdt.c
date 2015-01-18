#include <sys/gdt.h>

gdt_entry_t gdt[3];
gdt_ptr_t gdt_ptr;

extern void gdt_flush(void);

static void gdt_set_gate(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt[num].base_lo = base & 0xffff;
	gdt[num].base_mid = (base >> 16) & 0xff;
	gdt[num].base_hi = (base >> 24) & 0xff;

	gdt[num].limit_lo = limit & 0xffff;
	gdt[num].granularity = (limit >> 16) & 0x0f;

	gdt[num].granularity |= gran & 0xf0;
	gdt[num].access = access;
}

void gdt_init(void)
{
	gdt_ptr.limit = (sizeof(*gdt) * 3) - 1;
	gdt_ptr.base = gdt;

	// null segment
	gdt_set_gate(0, 0, 0, 0, 0);

	// kernel code segment
	gdt_set_gate(1, 0, 0xffffffff, 0x9a, 0xcf);

	// kernel data segment
	gdt_set_gate(2, 0, 0xffffffff, 0x92, 0xcf);

	gdt_flush();
}
