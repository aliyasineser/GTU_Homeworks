#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


char itemC;
unsigned int counter = 0;

void MSDelay(unsigned int time){
  unsigned int i,j;
  for(i=0; i< time; ++i)
    for(j=0;j<4000;++j);

}

void microSecDelay(unsigned int time){
  unsigned int i,j;
  for(i=0; i< time; ++i)
    for(j=0;j<4;++j);

}

void put2lcd(char c, char type ){
  char c_hi, c_lo;
  
  PORTB = c;
  
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

void openlcd(){
  DDRK = 0xFF;
  MSDelay(100);
  put2lcd(0x28, 0);
  put2lcd(0x0F, 0);
  put2lcd(0x06, 0);
  put2lcd(0x01, 0);
  MSDelay(2);
 
}

void main(void) {
  /* put your own code here */
  
  SCI0BDH = 0x00;
  SCI0BDL = 0x1A;
  SCI0CR1 = 0x00;
  SCI0CR2 = 0x24;
  DDRB = 0xFF;
  EnableInterrupts;
  openlcd();
  for(;;){
  }

}
 

interrupt ((0x10000-Vsci0)/2-1) void SCI0_ISR(void){
   if(SCI0SR1 & 0x80){   
    SCI0DRL = itemC; 
   }
   if(SCI0SR1 & 0x20){
    itemC = SCI0DRL;  
    if((itemC >= 48 & itemC <=57) || (itemC >= 97 & itemC <=122) || (itemC >= 65 & itemC <=90) || itemC == ' '){
      if(counter == 16)
        put2lcd(0xC0,0);
      put2lcd(itemC, 1);
      ++counter; 
    }
    
   }
     

}




 
