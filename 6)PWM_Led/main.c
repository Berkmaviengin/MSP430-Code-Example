
/******************************************************************************
 * Board uzerindeki P1.0 daki led pwm ile surulmustur.
 * Burada pwm timer ve min,max duty ve periyod ile saglanmistir.
 ******************************************************************************
 * Description: PWM Led
 * Author: Yunus Berk Maviengin
 ******************************************************************************
 * Original implementation from:
 * Author: Yunus Berk Maviengin - http://mavienginberk.blogspot.com.tr
 ******************************************************************************/

#include <msp430.h> 
/*
 * main.c
 */
#define PIN     BIT0
#define PERIOD      2000
#define MIN_DUTY    50
#define MAX_DUTY    1900

unsigned int duty = MIN_DUTY;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog
    P1DIR |= PIN;           // Output direction
    P1OUT = PIN;            // Out = 1
    TA0CCTL0 = CCIE;        // CCR0 interrupt enabled
    TA0CCR0 = duty;
    TA0CTL = TASSEL_2 + MC_2;   // SMCLK, contmode
    __bis_SR_register(LPM0_bits + GIE); // Enter LPM0 w/ interrupt
}

__attribute__((__interrupt__(TIMER0_A0_VECTOR)))
void Timer0_A(void)
{
    P1OUT ^= PIN;           // Toggle output
    if(P1OUT & PIN) {
        duty++;
        if(duty > MAX_DUTY) duty = MIN_DUTY;
        TA0CCR0 += duty;
    } else {
        TA0CCR0 += PERIOD - duty;
    }
}
