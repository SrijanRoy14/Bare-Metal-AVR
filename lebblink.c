 #include <avr/io.h>
 #include <util/delay.h>

 int main()
 {
     // Set built-in LED pin as output
     DDRB |= (1 << DDB5); //This is the data direction register for port b setting its 5th pin high
     while (1) {
         PORTB |=  (1 << PB5);   // LED on. Since the default pin 13 led resides in portb register tuning its 5th pin high while keeping others low
         _delay_ms(100);         // wait 500ms
         PORTB &= ~(1 << PB5);   // LED off
         _delay_ms(100);         // wait 500ms
     }
     return 0;
 }