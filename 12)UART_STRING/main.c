#include <msp430.h>

/*
 * main.c
 */
#define RXD        BIT1 //Check your launchpad rev to make sure this is the case. Set jumpers to hardware uart.
#define TXD        BIT2 // TXD with respect to what your sending to the computer. Sent data will appear on this line
#define BUTTON    BIT3

void UART_TX(char * tx_data);            // Function Prototype for TX

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;         // Stop Watch dog timer

  BCSCTL1 = CALBC1_1MHZ;            // Set DCO to 1 MHz
  DCOCTL = CALDCO_1MHZ;

  P1DIR &=~BUTTON;                  // Ensure button is input (sets a 0 in P1DIR register at location BIT3)

  P1OUT |=  BUTTON;                 // Enables pullup resistor on button
  P1REN |=  BUTTON;

  P1SEL = RXD + TXD ;                // Select TX and RX functionality for P1.1 & P1.2
  P1SEL2 = RXD + TXD ;              //

  UCA0CTL1 |= UCSSEL_2;             // Have USCI use System Master Clock: AKA core clk 1MHz

  UCA0BR0 = 104;                    // 1MHz 9600, see user manual
  UCA0BR1 = 0;                      //

  UCA0MCTL = UCBRS0;                // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;             // Start USCI state machine

  while(1)                          // While 1 is equal to 1 (forever)
  {
      if(!((P1IN & BUTTON)==BUTTON)) // Was button pressed?
      {
          UART_TX("Hello World! \r\n");  // If yes, Transmit message & drink beer
          __delay_cycles(600000); //Debounce button so signal is not sent multiple times
      }
  }

}

void UART_TX(char * tx_data) // Define a function which accepts a character pointer to an array
{
    unsigned int i=0;
    while(tx_data[i]) // Increment through array, look for null pointer (0) at end of string
    {
        while ((UCA0STAT & UCBUSY)); // Wait if line TX/RX module is busy with data
        UCA0TXBUF = tx_data[i]; // Send out element i of tx_data array on UART bus
        i++; // Increment variable for array address
    }
}
