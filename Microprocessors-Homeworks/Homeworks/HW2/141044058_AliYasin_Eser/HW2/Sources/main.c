#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */



#define C2 183502 
#define  C2S 173202           
#define D2 163483
#define D2S 154318
#define E2  145648
#define  F2 137474
#define  F2S 123761
#define  G2 122478
#define  G2S 115601
#define  A2 109117
#define A2S 103171
#define  B2 97213     
#define C3 91758 
#define  C3S 86607           
#define D3 81747 
#define D3S 86607 
#define E3 72828 
#define  F3 68741 
#define  F3S 64880 
#define  G3 61239 
#define  G3S 57803 
#define  A3 54558 
#define A3S 51497 
#define  B3 48606 
#define  C4  45877  
#define C4S 43305 
#define  D4 40873
#define  D4S 38578 
#define E4 36413  
#define F4 34369
#define  F4S 32441
#define  G4 30619
#define G4S 28901
#define A4 27280  
#define  A4S 25748  
#define  B4 24303 
#define  C5 22939  
#define C5S 21651 
#define D5 20436
#define D5S 19289 
#define  E5 18206 
#define F5   17184
#define  F5S  16220
#define  G5    15310
#define  G5S  14450
#define A5  13639
#define A5S  12874
#define B5  12151
#define  C6  11469
#define C6S  10825
#define D6    10218
#define D6S   9644
#define  E6     9103
#define  F6     8592
#define F6S    8110
#define  G6     7655
#define G6S   7225
#define A6    6819
#define A6S     6437
#define B6    6075

#define WhisperSize    60
#define InTheEndSize 32
#define ForsakenSize 58

#define WhisperPart 15
#define ForsakenPart   29
#define InTheEndPart  13



unsigned int time;
unsigned long k;
unsigned long y;

unsigned long inTheArray[InTheEndSize] = { 
A3/2,E4/2,E4/2,C4/2,B3/2,B3/2,B3/2,
B3/2,C4/2,A3/2,E4/2,E4/2,C4/2,B3/2,B3/2,B3/2,B3/2,C4/2,A3/2,
E4/2,E4/2,C4/2,B3/2,B3/2,B3/2,B3/2,C4/2,
A3/2,E4/2,E4/2,C4/2,B3/2
} ;

unsigned long inTheTime[InTheEndSize] = {
180,180,180,180,180,180,180,90,90,
180,180,180,180,180,180,180,90,90,
180,180,180,180,180,180,180,90,90 ,
180,180,180,180,300
}  ;


unsigned long WhisperArray[WhisperSize] = {
C4S/2 ,B3/2 ,F3S/2 ,D3/2, C4S/2 ,B3/2 ,F3S/2 ,D3/2,
A3/2, G3/2, D3/2, B2/2,A3/2, G3/2, D3/2,
 G3/2, F3S/2, D3/2, B2/2, G2/2,
 F2S/2, G2/2, A2/2, B2/2,C3S/2,D3/2, E3/2, F3S/2,
 
 C4S/2 ,B3/2 ,F3S/2 ,D3/2, C4S/2 ,B3/2 ,F3S/2 ,D3/2,
A3/2, G3/2, D3/2, B2/2,A3/2, G3/2, D3/2,
 G3/2, F3S/2, D3/2, B2/2, G2/2,
 F2S/2, G2/2, A2/2, B2/2,C3S/2,D3/2, E3/2, F3S/2
 
}    ;

unsigned long WhisperTime[WhisperSize] = {
200,80,200,240, 200,80,200,240,
200,80,200,240,200,80,330,
200,80,150,150,350,
200,200,200,200,200,200,200,200,

200,80,200,240, 200,80,200,240,
200,80,200,240,200,80,330,
200,80,150,150,350,
200,200,200,200,200,200,200,200

  
}  ;


unsigned long forsakenArray[ForsakenSize] = {

D4/2,A5/2,D4/2,A5/2,E4/2,F4/2,E4/2,D4/2,A5/2,D4/2,A5/2,F4/2,D4/2,E4/2    ,
D4/2,A5S/2,D4/2,A5S/2,E4/2,F4/2,E4/2,D4/2, A5S/2,G4/2,D4/2,F4/2, D4/2,E4/2,
D4/2,A5/2,D4/2,A5/2,E4/2,F4/2,E4/2,D4/2,A5/2,D4/2,A5/2,F4/2,D4/2,E4/2 ,
D4/2,A5S/2,D4/2,A5S/2,E4/2,F4/2,E4/2,D4/2,	 G4/2, A5S/2, F4/2,E4/2,D4/2,F4/2,D4/2,E4/2
}  ;

unsigned long forsakenTime[ForsakenSize] = {
70,70,70,70,70,70,70,70,70,70,70,70,70,
70,70,70,70,70,70,70,70, 70,70,70,70,70,70,               
70,70,70,70,70,70,70,70,70,70,70,70,70,
70,70,70,70,70,70,70,70, 70,70,70,70, 70,70,70, 70 ,70,70
}   ;

void playNote(unsigned long freq, int dur);
void MSDelay(unsigned int);
void playInTheEnd(int param);
void playForsaken(int param);
void playWhisper(int param);
void main(void) {
    /* put your own code here */

    DDRT = 0x20;
    DDRH = 0x00;
    DDRB = 0xFF;
    DDRP  = 0xFF;
    TSCR1 = 0x80;
    TSCR2 = 0x01;
    TIOS = 0x20;
    TCTL1 = 0x04;
    PORTB = 0x00;
    PTP = 0x07;	

    
    for(;;){
            if(PTH == 0x01){
            	TIOS |= 0x20;  	
            	PORTB = 0x06;
            	MSDelay(1000);  
	    	playWhisper(WhisperSize);
	    	TIOS &= 0xDF;
	    	PORTB = 0x00;
            }else if(PTH == 0x02){
                TIOS |= 0x20; 
                PORTB = 0x5B;
                MSDelay(1000);  
		playInTheEnd(InTheEndSize);
		TIOS &= 0xDF;
            }else if(PTH == 0x03){
          	TIOS |= 0x20; 
            	PORTB = 0x4F;
            	MSDelay(1000);  
	    	playForsaken(ForsakenSize);
	    	TIOS &= 0xDF;
            }else if(PTH == 0x00){
          	PORTB = 0x06;
                MSDelay(1000);  
            	playWhisper(WhisperPart);		      // 5SN
	    	TIOS &= 0xDF;
	    	MSDelay(1000);					  
		TIOS |= 0x20; 
		PORTB = 0x5B; 
		MSDelay(1000);  
		playInTheEnd(InTheEndPart);	     // 5SN
	    	TIOS &= 0xDF;
	    	MSDelay(1000);					  
		TIOS |= 0x20;  
		PORTB = 0x4F;
		MSDelay(1000);  
		playForsaken(ForsakenPart);		       // 5SN
	    	TIOS &= 0xDF;					  		
            }else{
            	TIOS &= 0xDF;
            	PORTB = 0xFE;
            }
           	MSDelay(5000);     	// 5 SEC DELAY
    }
    EnableInterrupts;


    for (;;) {
        _FEED_COP(); /* feeds the dog */
    } /* loop forever */
    /* please make sure that you never leave main */
}

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

void playWhisper(int param){
	unsigned int i=0;
	for(i=0;i< param; ++i){
	
		playNote(WhisperArray[i], WhisperTime[i]);

	}
	

}

void playInTheEnd(int param) {
	unsigned int i=0;
	for(i=0;i< param; ++i){
		playNote(inTheArray[i], inTheTime[i]);
	}
}

void playForsaken(int param) {
  	unsigned int i=0;
	for(i=0;i< param; ++i){
		playNote(forsakenArray[i], forsakenTime[i]);
	}


}

// Waits  itime miliseconds
void MSDelay(unsigned int itime) 
{
    unsigned int i;
    unsigned int j;
    for (i = 0; i < itime; i++)
        for (j = 0; j < 4000; j++);
}
