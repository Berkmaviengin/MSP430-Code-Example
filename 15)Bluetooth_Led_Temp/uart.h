/*
 *uart.h
 *Version: 1.0
 *Parker Dillmann
 *The Longhorn Engineer (c) 2013 
 *www.longhornengineer.com
 *
 *Check bottom of file for License.
 *
 *This is a uart.h file of the UART Hardware demo using USCI on the MSP430G2553 microcontroller.
 *Set your baud rate in your terminal to 9600 8N1.
 *When using your TI MSP-430 LaunchPad you will need to cross the TXD and RXD jumpers.
 *
*/


/*rx_flag
* This flag is to be used by other modules to check and see if a new transmission has happened.
* This is READ ONLY. Do not write to it or the UART may crash.
*/
extern volatile unsigned int rx_flag;

/*uart_init
* Sets up the UART interface via USCI
* INPUT: None
* RETURN: None
*/
void uart_init(void);

/*uart_getc
* Get a char from the UART. Waits till it gets one
* INPUT: None
* RETURN: Char from UART
*/
unsigned char uart_getc();

/*uart_gets
* Get a string of known length from the UART. Strings terminate when enter is pressed or string buffer fills
* Will return when all the chars are received or a carriage return (\r) is received. Waits for the data.
* INPUT: Array pointer and length
* RETURN: None
*/
void uart_gets();

/*uart_putc
* Sends a char to the UART. Will wait if the UART is busy
* INPUT: Char to send
* RETURN: None
*/
void uart_putc(unsigned char c);

/*uart_puts
* Sends a string to the UART. Will wait if the UART is busy
* INPUT: Pointer to String to send
* RETURN: None
*/
void uart_puts(char *str);

