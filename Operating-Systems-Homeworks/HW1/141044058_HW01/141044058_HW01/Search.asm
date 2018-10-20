        ; 8080 assembler code
        .hexfile Search.hex
        .binfile Search.com
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

	;This program does linear search.

list: dw  012H, 034H, 053H, 053H, 05BH, 06FH, 033H, 021H, 07CH, 0FFH, 0BAH, 0CBH, 0A1H, 01AH, 03BH, 0C3H, 04AH, 05DH, 062H, 0A3H, 0B1H, 05CH, 07FH, 0CCH, 0AAH, 34H
size		equ 26
error: dw "Error", 00AH, 00H ; error string
Found: dw "Found in index:", 00AH, 00H ; found string


begin:
	LXI SP,stack 	; always initialize the stack pointer
	
	MVI A, READ_B	; read int command
	call GTU_OS	; call os
	mov d,b		; store data that has been read
	mvi e, size	; init e as s ize
	mvi c, 0	; init index
	lxi h, list	; store the list 

loop:	mov a,m		; take content from HL to b
	cmp d		; compare it with the number that use typed
	jz foundp	; if found go to foundp

	inx h		; Increase the HL
	inx h		; for the next element
	
	inr c
	dcr e		; decrease e, element counter
	jnz loop	; loop until e == 0

NotFound:
	LXI B, error  ; error print
	MVI A, PRINT_STR  ; store the OS call code to A
	call GTU_OS	; call the OS
	HLT


foundp:  
	mov l,c
	; Found string
	LXI B, Found
	MVI a, PRINT_STR
	call GTU_OS

	mov b,l
	MVI A, PRINT_B
	call GTU_OS
	HLT

