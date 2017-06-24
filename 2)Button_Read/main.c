#include <msp430.h> 

/*
 * main.c
 */

#define led     BIT0
#define buton   BIT3

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1DIR |=led;
    P1REN|=buton;                   //buton pini yani P1.3 pini enable edildi
    P1OUT|=buton;                   //buton cikisina lojik 1 verildi

    while(1)
    {
        if ((P1IN & buton) ==0 )
        {
            P1OUT |= led;
        }
        else
        {
            P1OUT &= ~led;
        }
    }
}
