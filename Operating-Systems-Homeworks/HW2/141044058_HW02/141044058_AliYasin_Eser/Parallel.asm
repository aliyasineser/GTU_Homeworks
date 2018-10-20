        ; 8080 assembler code
        .hexfile Parallel.hex
        .binfile Parallel.com
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
FORK		equ 7
EXEC		equ 8
WAITPID		equ 9

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

	;This program executes 3 programs.

printNumbersProg: dw "PrintNumbers.com", 00H 
printNumbersRevProg: dw "PrintNumbersRev.com", 00H 
sumProg: dw "sum.com", 00H 

begin:
	LXI SP,stack 	; always initialize the stack pointer

	MVI A, FORK  ; store the OS call code to A
	call GTU_OS	; call the OS
	
	
	mvi a, 0
	cmp b

	jnz PARENTZERO
	lxi b, printNumbersProg 
	mvi a, EXEC
	call GTU_OS

	JMP ENDPROC
    HLT

PARENTZERO:

    MVI A, FORK  ; store the OS call code to A
	call GTU_OS	; call the OS

	mvi a, 0
	cmp b

	jnz PARENTONE
	lxi b, printNumbersRevProg 
	mvi a, EXEC
	call GTU_OS

	JMP ENDPROC
    HLT

PARENTONE:

    lxi b, sumProg 
	mvi a, EXEC
	call GTU_OS


	JMP ENDPROC
    HLT

ENDPROC:
    HLT


