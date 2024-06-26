/*ST7066U: has two Registers Instruction Register(IR) & Data Register(DR)
If RS = 1 DR is selected
   RS = 0 IR is selected
When Instruction Register is selected we send Commands for setting up the LCD
When Data Register is selected we send Data for printing on the LCD

R/W pins : configures when to Read/Write
R/W = 1 Read
R/W = 0 Write
Before writing any Command or data Busy Flag should be checked.


Enable Pin: is used for Starting Read or Write Operation
After equating values to Data pins of LCD , Enable pin 
should be toggled from High to low for data/command execution.
if Enable pulse is not their then no command/data will be executed 
Thus Lcd_wait is used in lcd_command() and lcd_data()

The chip has two kind of interface 8 bit or 4-bit:
If 8 bit mode has to be used then all D0-7 pins are used
if 4 bit moder is used then D4-D7 pins is used in which first 4 high bits(D7-4) are send 
followed by last 4 bits(D0-D3)

*/

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "include/UART.h"
#include "include/GPIO.h"


                                              
#define LCD_command_dir DDRB        // --> sets the output and input for commands registers
#define LCD_command_port PORTB     // --> sets the high low of pins
                                                       

//for atmega 328p
#define LCD_data_dir DDRD           // data pins 0-7 (PD0:7-D0:7)--> sets the output or input for data pins
#define LCD_data_port PORTD        // data pins 0-7 (PD0:7-D0:7)--> sets the high low for data pins that is data to be send  is passed to this constant


#define debug false
#define RW 0     // Define Read(1)/Write(0) signal pin, connected to dogital pin D8
#define RS 1       //Define Register Select (data(1)/command reg(0))pin 
#define EN 2        // Define Enable signal pin: Set to 1 for final execution of data/command to d0-7 pins

                  // for atmega 328p                
#define LCD_D0 0
#define LCD_D1 1
#define LCD_D2 2
#define LCD_D3 3
#define LCD_D4 4  //  Digital pin - 4(PD4)                
#define LCD_D5 5  //  Digital pin - 5(PD5)                
#define LCD_D6 6  //  Digital pin - 6(PD6)                
#define LCD_D7 7  //  Digital pin - 7(PD7)                




//Function Set
//Rs RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0 0  0    0   1   DL  N   F   -   -
// 8bit (DL=1) , 4bit (DL=0)
// 1line (N=0) , 2line (N-1)
#define lcd_8bit_1line 0b00110000
#define lcd_8bit_2line 0b00111000
#define lcd_4bit_1line 0b00100000
#define lcd_4bit_2line 0b00101000

//Display ON/OFF control -
//Rs RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0 0  0    0   0   0   1   D   C   B
//DN- display on(D=1), CN- Cursor on(C=1 ), BN- blink on(B=1)
//DF-display off(D=0), CF- cursor off(C=1), BF- blink off(B=0)
#define lcd_DN_CN_BN 0b00001111
#define lcd_DN_CF_BF 0b00001100
#define lcd_DN_CN_BF 0b00001110
#define lcd_DF_CF_BF 0b00001000
#define lcd_DF_CN_BN 0b00001011

//Entry mode set
//Rs RW DB7 DB6 DB5 DB4 DB3 DB2 DB1  DB0
// 0 0  0    0   0   0   0   1  I/D  S/H
//CMR -cursor move right(I/D=1) , DMF- display move off(S/H=0)
//CML -cursor move left(I/D=0) , DMR - display move is performed:right(S/H=1)
//DML- display move is performed: left(S/H=1)
#define lcd_CMR_DMF 0b00000110
#define lcd_CML_DMF 0b00000100
#define lcd_CMR_DMR 0b00000111
#define lcd_CML_DML 0b00000101

#define lcd_clear_all 0b00000001
#define lcd_rhome     0b00000010
#define lcd_SETDDRAMADDR 0x80

uint8_t address_counter=0; // Variable to store Address counter and Busy Flag(7th bit) Status

void lcd_enable_pulse();

void lcd_write8bit(uint8_t value);


uint8_t read_BF_adress();

int LCD_wait(void);

void LCD_command(uint8_t cmnd);
void lcd_clear();
void lcd_Rethome();
void lcd_setcursor(uint8_t col, uint8_t row);
void LCD_init();


void LCD_data(uint8_t data);
void lcd_printint_num(int value);
void LCD_string(const char*str);
void lcd_print1line(const char *buff);
void lcd_print2line(const char *buff);
