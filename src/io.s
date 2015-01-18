global outb
outb:
	mov ax, [esp + 8]
	mov dx, [esp + 4]
	out dx, al
	ret

global inb
inb:
	mov dx, [esp + 4]
	in al, dx
	ret
