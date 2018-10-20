#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


unsigned char getCode(unsigned char val){
  if(val == '0') return 0x3F;
  else if(val == '1') return 0x06;
  else if(val == '2') return 0x5B;
  else if(val == '3') return 0x4F;
  else if(val == '4') return 0x66;
  else if(val == '5') return 0x6D;
  else if(val == '6') return 0x7D;
  else if(val == '7') return 0x07;
  else if(val == '8') return 0x7F;
  else if(val == '9') return 0x6F; 
}

           
void main(void) {
  /* put your own code here */
   

  unsigned char val;
  int i;
  const char *selectStr = "1-Show year in 7-Segment\n2-Show Value on PortB Leds";
  const char *whichYearStr = "Which Year?\n";
  const char *whichValueStr = "Which Value?\n";

  DDRB = 0xFF;
  SCI0BDH = 0x00;
  SCI0BDL = 26;
  SCI0CR1 = 0x00;
  SCI0CR2 = 0x0C;
  DDRP = 0xFF;
 
  
  while(1){
    
    i = 0;
    while(i != 52){
      SCI0DRL = selectStr[i];
      while(!(SCI0SR1 & 0x80));
      ++i;
    }
    
    while(!(SCI0SR1 & 0x20));
    val = SCI0DRL;
      
    if(val == '1'){
    
      i = 0;
      while(i != 12){
        SCI0DRL = whichYearStr[i];
        while(!(SCI0SR1 & 0x80));
        ++i;
      }
      
      while(!(SCI0SR1 & 0x20));
      val = SCI0DRL;
      PTP = 0x0E;
     
      PORTB = getCode(val);
      
      
      while(!(SCI0SR1 & 0x20));
      val = SCI0DRL;
      PTP = 0x0D;
     
      PORTB = getCode(val);
      
      while(!(SCI0SR1 & 0x20));
      val = SCI0DRL;
      PTP = 0xB;
      PORTB = getCode(val);
             
      while(!(SCI0SR1 & 0x20));
      val = SCI0DRL;
         PTP = 0x07;
      PORTB = getCode(val);
        
    }else if(val == '2'){
      PTP = 0xFF;
      i = 0;
      while(i != 13){
        SCI0DRL = whichValueStr[i];
        while(!(SCI0SR1 & 0x80));
        ++i;
      }
           
      while(!(SCI0SR1 & 0x20));
      val = SCI0DRL;
      PORTB = val - '0';  
      
    }else break;     
    
  }

  EnableInterrupts;

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
            