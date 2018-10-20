        ; 8080 assembler code
        .hexfile sum2.hex
        .binfile sum2.com
        ; try "hex" for downloading in hex format
        .download bin 
	.download hex
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

	; OS call list
PRINT_B		equ 1
PRINT_MEM	equ 2
READ_B		equ 3
READ_MEM	equ 4
PRINT_STR	equ 5
READ_STR	equ 6

	; Position for stack pointer
stack   equ 0F000h

	org 000H
	jmp begin

	; Start of our Operating System
GTU_OS:	PUSH D
	push D
	push H
	push psw
	nop	; This is where we run our OS in C++, see the CPU8080::isSystemCall()
		; function for the detail.
	pop psw
	pop h
	pop d
	pop D
	ret
; ---------------------------------------------------------------
; YOU SHOULD NOT CHANGE ANYTHING ABOVE THIS LINE        

	;This program adds numbers from 0 to 10. The result is stored at variable
	; sum. The results is also printed on the screen.

sum	ds 2 ; will keep the sum

begin:
	LXI SP,stack 	; always initialize the stack pointer
        mvi c, 10	; init C with 10
	mvi a, 0	; A = 0
loop:
	ADD c		; A = A + C
	DCR c		; --C
	JNZ loop	; goto loop if C!=0
	STA SUM		; SUM = A

			; Now we will call the OS to print the value of sum
	LXI B, SUM	; Load the address of the printed value to the B and C registers
	MVI A, PRINT_MEM	; store the OS call code to A
	call GTU_OS	; call the OS
	hlt		; end program
