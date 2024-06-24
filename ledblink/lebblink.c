 
 #include <util/delay.h>
 #include "include/GPIO.h"

 int main() 
 {
     // Set built-in LED pin as output     
     //DDRB |= (1 << DDB5); //This is the data direction register for port b setting its 5th pin high
     pinMode(DDB5,&DDRB,OUTPUT);
     
     while (1) {
         //PORTB |=  (1 << PB5);   // LED on. Since the default pin 13 led resides in portb register tuning its 5th pin high while keeping others low
         digitalWrite(PB5,&PORTB,HIGH);
         _delay_ms(100);         // wait 500ms
        // PORTB &= ~(1 << PB5);   // LED off
         digitalWrite(PB5,&PORTB,LOW);
         _delay_ms(100);         // wait 500ms
     }
     return 0;
 }