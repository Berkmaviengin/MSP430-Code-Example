
/******************************************************************************
 * Board uzerindeki 2 led 1 saniye araliklarla yakip sondurulmustur.
 * Burada gecikme for dongusu ile saglanmistir.
 ******************************************************************************
 * Description: Led Blink With Software Delay
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
#define delay   50000

int main(void)
{
    volatile unsigned int sayac;
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR |=led1|led2;
	P1OUT &=~led1;
	P1OUT &=~led2;
	while(1)
	{
	    P1OUT ^=led1|led2;
	    for(sayac=0;sayac<delay;sayac++)
	    {
	    }
	}
}
