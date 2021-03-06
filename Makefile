TARGET = kernel.iso

INCDIR=inc
SRCDIR=src
OBJDIR=obj
ISODIR=iso

CC := /opt/cross/bin/i686-elf-gcc
CCFLAGS := -std=gnu99 -nostdlib -ffreestanding -Wall -Wextra

LD := /opt/cross/bin/i686-elf-gcc
LDFLAGS = -T link.ld  -nostdlib -ffreestanding -lgcc

AS := nasm
ASFLAGS :=  -felf32

SOURCES := $(wildcard $(SRCDIR)/*.c)
ASM_SRC := $(wildcard $(SRCDIR)/*.s)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.c.o,$(SOURCES))
OBJECTS += $(patsubst $(SRCDIR)/%.s,$(OBJDIR)/%.s.o,$(ASM_SRC))

$(TARGET): $(OBJECTS)
	$(LD) $^ $(LDFLAGS)
	mkdir -p $(ISODIR)/boot
	mv a.out $(ISODIR)/boot/a.out
	grub-mkrescue -o $(TARGET) $(ISODIR)

$(OBJDIR)/%.s.o: $(SRCDIR)/%.s
	$(AS) -o $@ $^ $(ASFLAGS)

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(CC) -o $@ $^ $(CCFLAGS) -c -I $(INCDIR)

.PHONY: clean iso

clean:
	rm $(OBJECTS)
	rm $(TARGET)
