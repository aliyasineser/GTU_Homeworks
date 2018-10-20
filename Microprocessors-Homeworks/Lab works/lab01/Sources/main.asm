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


; code section
            ORG   $1500


Entry:
_Startup:
          LDAA #$FF    ; load hex FF to acc a
          STAA DDRA    ; light  
          STAA DDRB    ; light
          
          STAA DDRJ    ; light
          LDAA #$FE    ; load hex FE to acc a
          ANDA PTJ     ; PTJ && Acc a
          
          LDAA #$4A    ; load hex 4A to acc a
          STAA PORTA   ; inform port a
          STAA PORTB   ; inform port b
          
          ADDA #$01    ; Acc a value + hex 01 -> acc a
          STAA $1200   ; store acc a value to $1200 address
          
          SWI
             
;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            ORG   $FFFE
            DC.W  Entry           ; Reset Vector
