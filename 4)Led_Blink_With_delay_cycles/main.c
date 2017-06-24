
/******************************************************************************
 * Board uzerindeki 2 led 1 saniye araliklarla yakip sondurulmustur.
 * Burada gecikme __delay_cycles() ile saglanmistir.
 ******************************************************************************
 * Description: Led Blink With Software __delay_cycles()
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

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1DIR |=led1|led2;
    P1OUT &=~led1;
    P1OUT &=~led2;
	while(1)
	{
	    P1OUT ^=led1 |led2;
	    __delay_cycles(1000000);
	}
}
