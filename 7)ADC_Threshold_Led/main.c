
/******************************************************************************
 * Board uzerindeki P1.0 daki led adc(P1.4)deki degere gore yanip sonmustur.
 * threshold degeri 500 olarak belirtilmistir
 ******************************************************************************
 * Description: ADC Threshold Led
 * Author: Yunus Berk Maviengin
 ******************************************************************************
 * Original implementation from:
 * Author: Yunus Berk Maviengin - http://mavienginberk.blogspot.com.tr
 ******************************************************************************/

#include <msp430.h> 
#include <stdio.h>
/*
 * main.c
 */
unsigned int ADCValue;
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    ADC10CTL0 = ADC10SHT_2 + ADC10ON ; // ADC10ON, interrupt enabled
    ADC10CTL1 = INCH_4; // input A4(P1.4)

    P1DIR |= 0x01; // Set P1.0 to output direction

    for (;;)
    {
        ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start

        ADCValue=ADC10MEM ;
        if (ADCValue< 500)
            P1OUT &= ~0x01; // Clear P1.0 LED off
        else
            P1OUT |= 0x01; // Set P1.0 LED on
    }
}
