        ; 8080 assembler code
        .hexfile test.hex
        .binfile test.com
        ; try "hex" for downloading in hex format
        .download bin  
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
stack   equ 04000h

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

	;This program is test for OS calls.

list: dw  012H, 034H, 053H, 053H, 05BH, 06FH, 033H, 021H, 07CH, 0FFH, 0BAH, 0CBH, 0A1H, 01AH, 03BH, 0C3H, 04AH, 05DH, 062H, 0A3H, 0B1H, 05CH, 07FH, 0CCH, 0AAH, 34H
size		equ 26
typed: dw "You typed:", 00AH, 00H ; explanation string
memstr: dw "Content of memory that you typed:", 00AH, 00H ; explanation string
teststr: ds 200

begin:
	LXI SP,stack 	; always initialize the stack pointer
	
	MVI A, READ_B	; read int command
	call GTU_OS	; call os

	mov d,b	

	LXI B, typed  ; explanation print
	MVI A, PRINT_STR  ; store the OS call code to A
	call GTU_OS	; call the OS
	
	mov b,d
	MVI a, PRINT_B ; print b
	call GTU_OS

	LXI B, teststr  ; string for read
	MVI A, READ_STR  ; store the OS call code to A
	call GTU_OS	; call the OS

	LXI B, typed  ; explanation print
	MVI A, PRINT_STR  ; store the OS call code to A
	call GTU_OS	; call the OS

	LXI B, teststr  ; test string print
	MVI A, PRINT_STR  ; store the OS call code to A
	call GTU_OS	; call the OS

	
	MVI a, READ_MEM ; read memory
	call GTU_OS

	LXI B, memstr  ; memstr print, inform the user
	MVI A, PRINT_STR  ; store the OS call code to A
	call GTU_OS	; call the OS

	MVI a, PRINT_MEM ; print what 
	call GTU_OS

	HLT
