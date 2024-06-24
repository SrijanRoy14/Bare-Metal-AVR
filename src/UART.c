#include "include/UART.h"

void GB_UART_Init0()
{
	//103 fpr 9600
	//8 for 115200
	uart0_baudrate = 103;
	uart0_ucsrB = (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0); //00001000, 00010000 //setting rx tx and receive complete interrupt
    //we are using the default mode(parity diabled, data bits 8...etc) uart mode so not configuring the ucsrC register
}
void GB_UART_TxChar0(uint16_t gb_data)
{
	while((uart0_ucsrA & (1<<UDRE0))==0); //00100000
	uart0_UDR = gb_data;
	
}
char GB_UART_RxChar0()
{
	while(!(uart0_ucsrA & (1<<RXC0)));  // 1000000
	return uart0_UDR;
}
void GB_rxstring0(char *gb_buff)
{
	int gb_i=0;
	char gb_myValue;
	do
	{
		gb_myValue = GB_UART_RxChar0();
		if(gb_myValue!='\n')
		{
			gb_buff[gb_i]=gb_myValue;
			gb_i++;
		}    
		else
		{
			gb_buff[gb_i]='\0';
			break;
		}

	}
	while( !(uart0_ucsrA & (1<<RXC0)));
	}
void GB_printString0(const char *gb_myString)      /////to print any string
{
	while (*gb_myString) GB_UART_TxChar0(*gb_myString++);
}
/*
Remember the passed integer should have
'\n' as its last element
*/

void GB_bit0(uint32_t gb_val)
{
	int8_t gb_ptr;
	for(gb_ptr=7;gb_ptr>=0;gb_ptr--)
	{
		if ((gb_val & (1<<gb_ptr))==0) GB_UART_TxChar0('0');
		else GB_UART_TxChar0('1');
	}
}