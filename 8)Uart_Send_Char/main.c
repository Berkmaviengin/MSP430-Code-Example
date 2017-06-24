
/******************************************************************************
 * uarttan serial ekrana a karakteri yollanmistir.
 * Bu islem yapilirken haberlesme 9600 baudda yapilmistir.
 ******************************************************************************
 * Description: Uart Send Char
 * Author: Yunus Berk Maviengin
 ******************************************************************************
 * Original implementation from:
 * Author: Yunus Berk Maviengin - http://mavienginberk.blogspot.com.tr
 ******************************************************************************/

#include <msp430.h> 
/*
 * main.c
 */
#define RXD        BIT1
#define TXD        BIT2
#define BUTTON    BIT3

void UART_TX(char * tx_data);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;         // Stop Watch dog timer
  BCSCTL1 = CALBC1_1MHZ;            // Set DCO to 1 MHz
  DCOCTL = CALDCO_1MHZ;

  P1DIR &=~BUTTON;
  P1OUT |=  BUTTON;
  P1REN |=  BUTTON;
  P1SEL = RXD + TXD ;
  P1SEL2 = RXD + TXD ;

  UCA0CTL1 |= UCSSEL_2;
  UCA0BR0 = 104;                    // 1MHz 9600
  UCA0BR1 = 0;
  UCA0MCTL = UCBRS0;                // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;             // Start USCI state machine

  while(1)
  {
      if(!((P1IN & BUTTON)==BUTTON))
      {
          UART_TX('a');
          __delay_cycles(100000);
      }
  }
}

void UART_TX(char *data)
{
        while ((UCA0STAT & UCBUSY));
        UCA0TXBUF = data;
}
