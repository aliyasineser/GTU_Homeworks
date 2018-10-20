#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

int tempor = 0; // rti interrupt portb temporary variable
int runmode=1; // Run in 1, stop in 0
int overflowOne=0; // Lo bound
int overflowTwo=0; // Hi bound
int overflowGen=0; // overflow counter
unsigned int y;  // play note duration, bad naming
unsigned int time;	 // play note duration, real time
char itemC;   // item for sending, kinda temporary cuz it will send only once
char itemS;   //  item for receiving
int t = 0;	  //  overflow variable for click interval
unsigned int k=0;   // overflow variable for click interval, doesn't change except t changes.
int coin=0;    //  counter for taking 2 clicks. 
unsigned numCount=0; // Lcd character counter

//Play Note function. Plays one note dur duration
void playNote(unsigned long freq, int dur);


// Waits  itime miliseconds
void MSDelay(unsigned int time){
    unsigned int i,j;
    for(i=0; i< time; ++i)
        for(j=0;j<4000;++j);
    
}
// Waits  itime microseconds
void microSecDelay(unsigned int time){
    unsigned int i,j;
    for(i=0; i< time; ++i)
        for(j=0;j<4;++j);
    
}
/*********************************Put2Lcd*********************************/
// One char to lcd
void put2lcd(char c, char type ){
    char c_hi, c_lo;

    c_hi = (c & 0xF0) >> 2;
    c_lo = (c & 0x0F) << 2;
    
    
    PORTK &= (~0x01);
    
    
    if(type == 1)
        PORTK = c_hi | 0x01;
    else
        PORTK = c_hi;
    
    PORTK |= 0x02;
    __asm nop;
    __asm nop;
    __asm nop;
    __asm nop;
    __asm nop;
    __asm nop;
    
    PORTK &= ~0x02;
    
    microSecDelay(50);
    
    if(type == 1)
        PORTK = c_lo | 0x01;
    else
        PORTK = c_lo;
    
    PORTK |= 0x02;
    __asm nop;
    __asm nop;
    __asm nop;
    __asm nop;
    __asm nop;
    __asm nop;
    
    
    PORTK &= ~0x02;
    
    microSecDelay(50); 
    
    
}

// String to lcd
void puts2lcd(char*ptr){
	while(*ptr) {
		put2lcd(*ptr,1);
		ptr++;
		microSecDelay(50);
	}
	
}

// Open Lcd settings.
void openlcd(){
    DDRK = 0xFF;
    MSDelay(100);
    put2lcd(0x28, 0);
    put2lcd(0x0F, 0);
    put2lcd(0x06, 0);
    put2lcd(0x01, 0);
    MSDelay(2);
    
}
/*********************************MAIN*********************************/
void main(void) {
	DDRT = 0x20;	  // Buzzer 
	DDRH = 0x00;	  // Port H input
	DDRB = 0xFF;	  // Port B output
	DDRP  = 0xFF;	  // 7 Segment output
	TSCR1 = 0x80;	  // Timer enable
	TSCR2 = 0x80;	  // No prescaler, enable interrupt
	TIOS = 0x30;	  // Buzzer and playing note, output compare
	TCTL1 = 0x05;	  // choose toggle 

	// Serial Communication variables
	SCI0BDH = 0x00; // Baud Lo
	SCI0BDL = 0x1A; // Baud Hi
	SCI0CR1 = 0x00;  // Control off
	SCI0CR2 = 0xAC; // Both receive and send
	
	//  J output variables	
	DDRJ=0xFF;     //PTJ = output    for LEDs
	PTJ = 0x0;    //Needed by Dragon12+ board

	// Real time interrupt variables
	CRGINT = CRGINT | CRGINT_RTIE_MASK;     //enable RTI 	
  	RTICTL = 0b00111001;	// Real time interrupt interval, according to experiments
	
	//Port H interrupt variables
	PIEH = 0xFF;   //enable PTH interrupt
  	PPSH = 0x00;   //Make it Edge-Trig.

	EnableInterrupts;
	
	openlcd();
        puts2lcd("Metronome");
        MSDelay(500);
        put2lcd(0x01,0);
        MSDelay(2);			 
	while(1){
		 if(runmode){	
			if(coin%2==0)
				t=overflowTwo-overflowOne;
			k=t;
			while (k > 0) {		       
			        TC4 = TCNT-1;
			         
			        while (!(TFLG1 & 0x10));
			        TFLG1 |= 0x10;
			        --k;
		   	 }
		   	 TIOS |= 0x20; 
		         playNote(60000,1);
		         TIOS &= 0xDF;
		
		}
	};

}

// Plays a note. Comes from HW2
void playNote(unsigned long freq, int dur) {
    PORTB = 0xFF;
    y = dur / 2;
    while (y > 0) {
        TFLG2 |= 0x80;
        time = TCNT;
        time += freq;
        TC5 = time;
        while (!(TFLG1 & 0x20));
        TFLG1 |= 0x20;

        if (TFLG2 & 0x80) {
            TFLG2 |= 0x80;
            --y;
        }
    }
    MSDelay(10);
    PORTB = 0x00;
}




// Interrupt serial communication
// Sends char back to see in terminal
// Button "t" 
interrupt ((0x10000-Vsci0)/2-1) void SCI0_ISR(void){
    if(SCI0SR1 & 0x80){
        SCI0DRL = itemC;   
        itemC=0;
    }
    if(SCI0SR1 & 0x20){
    	itemS = SCI0DRL;
        if(itemS == 't'){	
	        itemC=itemS;
	        put2lcd('^',1);
	       	if(runmode){	
		        overflowOne = overflowTwo;
		        overflowTwo = overflowGen;
		        ++coin;
	    	}
	        ++numCount;
	        
	        if(coin % 2 == 1 && SCI0SR1 & 0x80)
	        	SCI0DRL =  '_';
	       else{
	       		put2lcd('v',1);
	       		++numCount;
	       }
	        if(numCount ==16)
	        	put2lcd(0xC0, 0);
	        if(numCount==32){
	        	numCount=0;	
	        	put2lcd(0x80,0);    
	        }
	 }
    }
    
    
}

// interrupt for overflow , counter increments					  
interrupt ((0x10000-Vtimovf)/2-1) void OVF_ISR(void){
	overflowGen++;
	TFLG2 |= 0x80;
}


// interrupt for porth, if porth 00, no metronome will happens
interrupt ((0x10000-Vporth)/2-1) void PORTH_ISR(void){
	if(PTH==0x00) runmode=0;
	else runmode=1;
	PIFH = PIFH | 0xFF; 
}

// interrupt rti for 7-segment update
interrupt (((0x10000-Vrti)/2)-1) void RTI_ISR(void)
{
	tempor = PORTB;
	PTP = 0x07;
	PORTB = 0b00001111;
	microSecDelay(5); 
	if(runmode){
	   	PTP = 0x0B;
		PORTB = 0b01001001;
		microSecDelay(5);
		PTP = 0x0D;
		PORTB = 0b01001001;
		microSecDelay(5);
	}else{	
		PTP = 0x0B;
		PORTB = 0b00001001;
		microSecDelay(5);
		PTP = 0x0D;
		PORTB = 0b00001001;
		microSecDelay(5);
	}
	PTP = 0x0E;
	PORTB = 0b00111001;
	microSecDelay(5);
	PTP = 0x0F;		    
	PORTB = tempor;
	
	CRGFLG = CRGFLG | CRGFLG_RTIF_MASK; //clear it for next round	
}