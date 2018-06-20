#include <msp430.h> 
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*
 * main.c
 */
unsigned int ADCValue;
int sic=27;

long temp;
long IntDegF;
long IntDegC;
char buffer[32];
char buffer1[32];

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;           //Stop WDT
    BCSCTL1 = CALBC1_8MHZ;              //Set DCO to 8Mhz
    DCOCTL = CALDCO_8MHZ;               //Set DCO to 8Mhz
    P1DIR |=BIT6;
    P1OUT &=~BIT6;
    uart_init();
    ADC10CTL1 = INCH_10 + ADC10DIV_3; // Temp Sensor ADC10CLK/4
    ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;
    __enable_interrupt();

    while(1)
    {
        unsigned char c = uart_getc();
        if(c=='a')
        {
            P1OUT |=BIT6;
            uart_puts("led acik\n\r");
        }
        if(c=='k')
        {
            P1OUT &=~BIT6;
            uart_puts("led kapali\n\r");
        }
        if(c=='t')
        {
            ADC10CTL0 |= ENC + ADC10SC;
            temp = ADC10MEM;
            IntDegC = ((temp - 673) * 423) / 1024;
            sprintf(buffer, "Temp: %d C \n\r", IntDegC);
            uart_puts(buffer);
        }

    }
}
