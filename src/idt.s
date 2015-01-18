global idt_flush
idt_flush:
	extern idt_ptr
	lidt [idt_ptr]
	ret

%macro ISR_NOERR 1
global isr%1
isr%1:
	push byte 0
	push byte %1
	jmp isr_stub
%endmacro

%macro ISR_ERRCODE 1
global isr%1
isr%1:
	push byte %1
	jmp isr_stub
%endmacro

ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERRCODE 8
ISR_NOERR 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31

isr_stub:
	pusha ; push edi, esi, ebp...

	mov ax, ds
	push eax

	mov ax, 0x10 ; load the kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	extern isr_handler
	call isr_handler

	pop eax
	mov ds, ax ; restore the original data segment descriptor
	mov es, ax
	mov fs, ax
	mov gs, ax

	; cleanup
	popa ; pop edi, esi, ebp...

	add esp, 8 ; account for int_no and error_code

	iret
