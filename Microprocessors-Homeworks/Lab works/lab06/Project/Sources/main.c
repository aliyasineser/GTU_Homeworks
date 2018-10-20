#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

/*
* Implemented By Ali Yasin Eser, 20.04.2017
*/


unsigned int overflowCounter;
unsigned int loadRegister;

// 24 mhz clock, 1 second wait with overflow counting 
void OneSec(){
  overflowCounter = 366;
  TFLG2 = 0x80;
  while(overflowCounter){
    while(!(TFLG2 & 0x80));
    --overflowCounter;
    TFLG2 = 0x80;
  }
};


void main(void) {
  /* put your own code here */



  EnableInterrupts;

  DDRB = 0xFF; // Output seven segment

  TSCR1 = 0x80; // Enable timer
  TSCR2 = 0x00; // No interrapt, no prescaler
  DDRP = 0xFF;  // Port p output
  
  
  PTP = 0x0E; // Segment3
  PORTB = 0x06; // Print 1
  OneSec();

  PTP = 0x0D; // Segment 2
  PORTB = 0x67; // Print 9 
  OneSec();
  
  PTP = 0x0B; // Segment 1
  PORTB = 0x7D; // Print 6
  OneSec();

  PTP = 0x07;  // Segment 0
  PORTB = 0x06;  // Print 1
  OneSec();
  
  
  
  // NOW IT IS TIME TO MAKE BONUS PART -> BUZZER
  
 TIOS = 0x20;    // Activate PTT5
 TCTL1 = 0x04;   // Toggle PTT5
 TFLG1 = TFLG1 | 0x20;  // Clear the flag
 
 while(1){
  loadRegister = TCNT; // Take current
  TC5 = loadRegister + 24000; // Add desired pulse width for 500 hz
  while( !(TFLG1 & 0x20) );   // Wait till flag changes, TC5 == TCNT
  TFLG1 = TFLG1 | 0x20;  // Clear the flag
 
 }
  
  // I am not leaving main, so i do not need that
  /*
  for(;;) {
    _FEED_COP(); // feeds the dog 
  } // loop forever 
  // please make sure that you never leave main 
  */
}
   
