
/******************************************************************************
 * Button ile Led Yakilmistir
 * Bu islem yapilirken interrupt kullanilmistir
 ******************************************************************************
 * Description: GPIO Interrupt Led
 * Author: Yunus Berk Maviengin
 ******************************************************************************
 * Original implementation from:
 * Author: Yunus Berk Maviengin - http://mavienginberk.blogspot.com.tr
 ******************************************************************************/

#include <msp430.h> 
/*
 * main.c
 */
#define LED0 BIT0
#define LED1 BIT6
#define BUTTON BIT3

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= (LED0 + LED1);

    P1OUT &= ~(LED0 + LED1);
    P1IE |= BUTTON;
    P1IFG &= ~BUTTON;

    __enable_interrupt();
    for(;;)
    {}
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
P1OUT ^= (LED0 + LED1);
P1IFG &= ~BUTTON;
P1IES ^= BUTTON;

}
