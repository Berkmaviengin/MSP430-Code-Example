
/******************************************************************************
 * Mpsp430 launchpad uzerindeki iki led yakilmistir
 ******************************************************************************
 * Description: Leds On
 * Author: Yunus Berk Maviengin
 ******************************************************************************
 * Original implementation from:
 * Author: Yunus Berk Maviengin - http://mavienginberk.blogspot.com.tr
 ******************************************************************************/

#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR |=(BIT0) |(BIT6); //Cikis olarak ayarlandi (0x)
    P1OUT |=(BIT0) |(BIT6);
	while(1)
	{
	}
}
