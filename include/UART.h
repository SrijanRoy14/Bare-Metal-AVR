#ifndef _UART_H_
#define _UART_H_
#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"

//#define F_CPU 16000000L
#define uart0_ucsrA UCSR0A
#define uart0_ucsrB UCSR0B
#define uart0_uscrC UCSR0C
#define uart0_UDR UDR0
#define uart0_baudrate UBRR0

void GB_UART_Init0(); //fucntion for initialising the uart registers
void GB_UART_TxChar0(uint16_t gb_data);//function to push data to the UDR register
char GB_UART_RxChar0();//function to fetch one character at a time from UDR reg
void GB_printString0(const char *gb_myString);//function to print a buffer
void GB_rxstring0(char *gb_buff); // function to read from serial terminal (user input)
void GB_bit0(uint32_t gb_val);//function to convert integer values to binary values


#endif