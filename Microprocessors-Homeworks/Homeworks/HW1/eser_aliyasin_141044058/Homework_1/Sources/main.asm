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
Counter     DS.B 1
FiboRes     DS.W 1
BuffClean  DS.W 1
ZeroWord	  DC.W 0
MultiplyAnswer DS.B 1

            ; All of the variables and the operation
            ORG $1200
StartOperation FCC    "22.83+11.42="
QueryString   DS.B 30 ; No space String Operation
            ORG $1300
FirstIntPart    DS.B 3    ; BCD integer
FirstInt        DS.B 1	       ; Normal integer
            ORG $1310
FirstDecPart    DS.B 2   ; BCD decimal
FirstDec        DS.B 1      ; Normal decimal
            ORG $1320
SecondIntPart    DS.B 3	  ;BCD integer
SecondInt        DS.B 1	   ;Normal integer
            ORG $1330
SecondDecPart    DS.B 2    ;BCD decimal
SecondDec        DS.B 1	     ; Normal decimal
            ORG $1500
ResultInt        DS.B 1	     ; Result integer part
ResultDec        DS.B 1	      ; Result decimal part
            ORG $1350
GlobalOverflow   DS.B 1	       ; In case of Overflow
GlobalCounter    DS.W 1       ; Pointer to which part of operation
SignOp		   DS.B 1		; add or sub
DigitCounter	   DS.B 1          ; How many digits number has  
Temp		   DS.B 1          ; temporary  
; code section
            ORG   ROMStart

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Multiply A and B ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;            
Multiply:
	     MOVB #0, MultiplyAnswer
	     STAB  Counter
	     STAA Temp
	     LDAB Temp
	     LDAA #0	     
MultiplyLoop:
	     ABA
	     DEC Counter
	     BNE MultiplyLoop     
	     STAA MultiplyAnswer
	     RTS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; BCD to 1 byte number ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
DecimalCombine:	     
	     LDAA X
	     LDAB #10
	     JSR Multiply
	     LDAA MultiplyAnswer
	     ADDA Y
	     STAA Y
	     INX
	     LDAA X
	     ADDA Y
	     STAA Y
	     RTS
	     
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; BCD to 1 byte number ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	     
IntegerCombine:
	     LDAA X
	     LDAB #100
	     JSR Multiply
	     LDAA MultiplyAnswer
	     ADDA Y
	     STAA Y
	     INX
	     LDAA X
	     LDAB #10
	     JSR Multiply
	     LDAA MultiplyAnswer
	     ADDA Y
	     STAA Y
	     INX
	     LDAA X
	     ADDA Y
	     STAA Y
	     RTS
	     
;;;;;;;;;;;;;;;;;;;;;;;;;;Copy the integer bytes and locate Y location;;;;;;;;;;;;;;;;;;;;;;;;;;	     
IntegerParse:
	     LDX  GlobalCounter	     
	     MOVB #0, DigitCounter
IntLoop:
	     LDAA X	     	     
	     CMPA #'.'
	     BEQ IntLoopEnd
	     CMPA #'0'
	     LBLO Error
	     CMPA #'9'
	     LBHI Error
	     INX
	     INC DigitCounter
	     BRA IntLoop
IntLoopEnd:	     
	     ; Load First Integer to spesific storage
	     INY
	     INY
	     ; Turn character to integer and store it 	     
	     DEX
	     LDAB DigitCounter
IntPutLoop:
	     LDAA X
	     SUBA #'0'
	     STAA Y
	     DEX
	     DEY
	     DECB
	     BNE IntPutLoop
	     ; Correct the mess
	     LDAB DigitCounter
IntCorrectionLoop:	     
	     INX
	     DECB
	     BNE IntCorrectionLoop
	     INX
	     INX
	     STX GlobalCounter
	     RTS
	     
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Parse the decimal part;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
DecimalParse:	     
	     LDX  GlobalCounter
	     MOVB #0, DigitCounter
DecLoop:
	     LDAA X	     	     
	     CMPA #'='
	     BEQ DecLoopEnd
	     CMPA #'-'
	     BEQ DecLoopEnd
	     CMPA #'+'
	     BEQ DecLoopEnd
	     CMPA #'0'						        
	     LBLO Error
	     CMPA #'9'
	     LBHI Error
	     INX
	     INC DigitCounter
	     LBRA DecLoop
DecLoopEnd:	     
	     LDX GlobalCounter
	     LDAB DigitCounter
ToDecimalLocation:
	     LDAA X
	     SUBA #'0'
	     STAA Y	     	     
	     INX
	     INY
	     DECB
	     BNE ToDecimalLocation
	     INX
	     STX GlobalCounter
	     DEX
	     RTS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Error Led Part;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	     
Error:
	 MOVB #$FF , DDRB
	 MOVB #$FF , PORTB
	 LBRA EndOfTheStory







;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;MAIN;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	     
; Code Begins
Entry:
_Startup:
		LDS   #RAMEnd+1       ; initialize the stack pointer

		CLI                     ; enable interrupts
		LDX #StartOperation
		LDY #QueryString
		;Remove Spaces
RemSpcLoop:
		LDAA X
		CMPA #' '            
		BNE No_space
		INX
		BRA RemSpcLoop
No_space:
		STAA Y
		INX
		INY
		CMPA #'='            
		BEQ RemSpcLoopEnd
		BRA RemSpcLoop
RemSpcLoopEnd:	    
		MOVW #QueryString, GlobalCounter
		
		; Initialize the data part
		LDX #$1300
		MOVB #80, Counter	    
InitLoop: 
		MOVB #0, X
		INX 
		DEC Counter
		BNE InitLoop

		;Parse the first integer
		LDY #FirstIntPart
		JSR IntegerParse

		;Parse the first decimal
		LDY #FirstDecPart
		JSR DecimalParse

		;Need to get sign for right operation
		LDAA X
		STAA SignOp
		INX
		STX GlobalCounter

		;Parse the second integer
		LDY #SecondIntPart
		JSR IntegerParse 

		;Parse the second decimal
		LDY #SecondDecPart
		JSR DecimalParse

		;We have equal sign at the end ?
		LDAA X
		CMPA #'='
		LBNE Error

		; First integer combines
		LDX #FirstIntPart
		LDY #FirstInt
		JSR IntegerCombine

		; Second integer combines 
		LDX #SecondIntPart
		LDY #SecondInt
		JSR IntegerCombine

		; First decimal combines 
		LDX #FirstDecPart
		LDY #FirstDec
		JSR DecimalCombine

		; Second decimal combines 
		LDX #SecondDecPart
		LDY #SecondDec
		JSR DecimalCombine

		;Check the sign to addition or substraction
		LDAA SignOp
		CMPA #'+'
		BEQ AddOperation
		LDAA SignOp
		CMPA #'-'
		BEQ SubstractOperation

AddOperation:
		 ; Let's do the add operation
		 LDAA FirstDec
		 LDAB SecondDec
		 ABA
		 STAA ResultDec
		 CMPA #100
		 BLO No_Carry
		 LDAA ResultDec
		 SUBA #100
		 STAA ResultDec		 
		 LDAA FirstInt
		 INCA
		 STAA FirstInt
No_Carry:
		 LDAA FirstInt
		 LDAB SecondInt
		 ABA
		 STAA ResultInt
		 LBVS Error
		 MOVB #$FF , DDRB
		 MOVB #$55 , PORTB
		 BRA EndOfTheStory
		 
SubstractOperation:
		 ; Let's do the substract operation
		 LDAA FirstDec
		 LDAB SecondDec
		 SBA
		 STAA ResultDec
		 CMPA #0
		 BGT No_Barrow 
		 LDAA ResultDec
		 ADDA #100
		 STAA ResultDec
		 LDAA FirstInt
		 DECA
		 STAA FirstInt
No_Barrow:
		LDAA FirstInt
		LDAB SecondInt
		SBA
		STAA ResultInt
		LBVS Error
		MOVB #$FF , DDRB
		MOVB #$55 , PORTB
		BRA EndOfTheStory


EndOfTheStory:	
		SWI
		END

;**************************************************************
;*                 Interrupt Vectors                         		     *
;**************************************************************
		ORG   $FFFE
		DC.W  Entry           ; Reset Vector
