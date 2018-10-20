;*****************************************************************
;* This stationery serves as the framework for a                 *
;* user application (single file, absolute assembly application) *
;* For a more comprehensive program that                         *
;* demonstrates the more advanced functionality of this          *
;* processor, please see the demonstration applications          *
;* located in the examples subdirectory of the                   *
;* Freescale CodeWarrior for the HC12 Program directory          *
;*****************************************************************

; export symbols
            XDEF Entry, _Startup            ; export 'Entry' symbol
            ABSENTRY Entry        ; for absolute assembly: mark this as application entry point



; Include derivative-specific definitions 
		INCLUDE 'derivative.inc' 

ROMStart    EQU  $4000  ; absolute address to place my code/constant data

; variable/data section

            ORG RAMStart
 ; Insert here your data definition.
Counter     DS.W 1
FiboRes     DS.W 1
FirstCounter  DS.W 1
SecondCounter DS.W 1
ThirdCounter  DS.W 1


            ORG $1500
FirstNum    DS.W 1
SecondNum   DS.W 1
Quotient    DS.W 1
Remainder   DS.W 1

; code section
    ORG   ROMStart

;;;;;;;;;;;;;;;;;;;;;;
TakeTwoInput:
    LDAA #01
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    LDAA #$00
    LDAB PTH
    STD FirstNum
    LDAA #01
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    JSR DelayHalfSecond
    LSLA
    ADDA #$1
    STAA PORTB
    LDAA #$00
    LDAB PTH
    STD SecondNum
    RTS

;;;;;;;;;;;;;;;;
DelayHalfSecond:

    MOVW #$FFFF , FirstCounter
Floop:
    MOVW #$FFFF , SecondCounter
Sloop:
    MOVW #$21AA, ThirdCounter
Tloop:
    NOP
    DEC ThirdCounter
    BNE Tloop    
    DEC SecondCounter
    BNE Sloop
    DEC FirstCounter
    BNE Floop
    RTS
    


Entry:
_Startup:
    LDS   #RAMEnd+1       ; initialize the stack pointer

    CLI                     ; enable interrupts

    MOVB #$00, DDRH
    MOVB #$FF, DDRB
    MOVW #$00, FirstNum
    MOVW #$00, SecondNum
    MOVW #$00, Quotient
    MOVW #$00, Remainder
    
    
    
    
    JSR TakeTwoInput
    
    LDD FirstNum
    LDX SecondNum
    IDIV
    STX Quotient
    STD Remainder
    STAB PORTB
    JSR DelayHalfSecond 
    JSR DelayHalfSecond
    JSR DelayHalfSecond





;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
    ORG   $FFFE
    DC.W  Entry           ; Reset Vector
