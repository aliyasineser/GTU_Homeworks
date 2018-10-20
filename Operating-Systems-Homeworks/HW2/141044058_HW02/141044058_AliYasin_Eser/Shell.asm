        ; 8080 assembler code
        .hexfile Shell.hex
        .binfile Shell.com
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

	;This is a shell program. 

prompt: ds 100
childPid: ds 1


begin:
	LXI SP,stack 	; always initialize the stack pointer
	

START:

	LXI B, prompt  ; string for read
	MVI A, READ_STR  ; store the OS call code to A
	call GTU_OS	; call the OS
	
	MVI A, FORK  ; store the OS call code to A
	call GTU_OS	; call the OS

	lxi h,childPid
	mov m,b
	mov a,b
	mvi b, 0
	cmp b

	jnz PARENT
	lxi b, prompt 
	mvi a, EXEC
	call GTU_OS

	HLT

PARENT:
	mov b,m
	mvi a, WAITPID
	call GTU_OS
	JMP START	

	HLT
