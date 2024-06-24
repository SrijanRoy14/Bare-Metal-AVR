#include "include/UART.h"


int main(void)
{
    GB_UART_Init0();
    char rec[100];
    int a=23;
    GB_printString0("hello\n");
    GB_bit0(a);
    while (1)
    {
        GB_printString0("Write a string\n");
        GB_rxstring0(rec);
        GB_printString0(rec);
        GB_printString0("The bit value is: \n");    
        GB_bit0(a);
    }   
}