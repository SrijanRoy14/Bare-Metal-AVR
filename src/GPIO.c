
#include "include/GPIO.h"


void pinMode( uint8_t pin , uint8_t volatile *pin_data_direction_register, bool Mode )
{
	if(Mode==1)
	//*pin_data_direction_register|= (1 << pin);
    SET_BIT(*pin_data_direction_register,pin);
	else if(Mode==0)
	//*pin_data_direction_register&= ~(1 << pin);
    CLEAR_BIT(*pin_data_direction_register,pin);
}
//PORTB
void digitalWrite( uint8_t pin ,uint8_t volatile *port_data_pin_register, bool state)
{
	if(state==1)
	//*port_data_pin_register|= (1 << pin);
    SET_BIT(*port_data_pin_register,pin);
	else if(state==0)
	//*port_data_pin_register&= ~(1 << pin);
    CLEAR_BIT(*port_data_pin_register,pin);
}
//PINx
uint8_t digitalRead( uint8_t pin , uint8_t volatile *port_input_pin_register)
{
	//return ((*port_input_pin_register) & (1<<pin));
    return IS_SET(*port_input_pin_register,pin);
}