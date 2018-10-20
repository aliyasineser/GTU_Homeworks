        ; 8080 assembler code
        .hexfile Sort.hex
        .binfile Sort.com
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

	;This program sorts numbers.

list: dw  12H, 34H, 53H, 2AH, 5BH, 6FH, 33H, 21H, 7CH, 0FFH, 0BAH, 0CBH, 0A1H, 1AH, 3BH, 0C3H,4AH, 5DH,62H, 0A3H, 0B1H, 5CH, 7FH, 0CCH, 0AAH, 34H
size		equ 26

; For this algorithm, i searched many sites and saw a site called easynotes
; I learned the assembly sort from there and modified for 8080

begin:
	LXI SP,stack 	; always initialize the stack pointer
	mvi b, size	; size of the list for outer loop
outer:  mvi c, size	; size of the list for inner loop
	lxi h, list	; store list address to HL
	
inner:  mov a,m		; Take the first element
	inx h		; Increase the list address
	inx h		; for access another element
	mov d,m		; take the second element
	cmp d		; Compare A and D
	JC no_swap	; If A < C, no need to swap       	

	; otherwise
	mov m,a		; store A to second elements address
	dcx h		; Decrease address
	dcx h		; for access first element
	mov m,d		; store D to first elements address
	inx h		; Increase again so we updated
	inx h		; the list index for another iteration
	
no_swap: dcr c		; --C
	jnz inner	; Loop until C == 0

	dcr b		; -- B
	jnz outer	; Loop until B == 0
	
	; end of the sort, let us print
	mvi e, size	; init e as s ize
	lxi h, list	; store the list 
print:
	mov b,m		; take content from HL to b
	MVI A, PRINT_B  ; store the OS call code to A
	call GTU_OS	; call the OS
	inx h		; Increase the HL
	inx h		; for the next element
	dcr e		; decrease e, element counter
	jnz print	; Loop until e == 0
end:	
	HLT		; End of the program, well played

	




