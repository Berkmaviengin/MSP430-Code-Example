
/******************************************************************************
 * Board uzerindeki 2 led 1 saniye araliklarla yakip sondurulmustur.
 * Burada yanip sonme islemi timer interrupt ile saglanmistir
 ******************************************************************************
 * Description: Led Blink With Timer
 * Author: Yunus Berk Maviengin
 ******************************************************************************
 * Original implementation from:
 * Author: Yunus Berk Maviengin - http://mavienginberk.blogspot.com.tr
 ******************************************************************************/

#include <msp430.h>
/*
 * main.c
 */
#define led1    BIT0
#define led2    BIT6

void main( void )
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR = led1|led2;
    P1OUT &=~led1;
    P1OUT &=~led2;

    TA0CCR0 = 62500;  // set up terminal count
    TA0CTL = TASSEL_2 + ID_3 + MC_1; // configure and start timer
    TA0CCTL0= CCIE;   // enable timer interrupts
    __enable_interrupt();    // set GIE in SR
    while (1)
    {
    }

}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void myTimerISR(void)
{
    P1OUT ^=led1|led2;
}


