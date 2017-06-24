
/******************************************************************************
 * uarttan karakterler beklenmistir.
 * Gelen karaktere gore ledler acilip kapanmistir.
 ******************************************************************************
 * Description: Uart Recieve Led
 * Author: Yunus Berk Maviengin
 ******************************************************************************
 * Original implementation from:
 * Author: Yunus Berk Maviengin - http://mavienginberk.blogspot.com.tr
 ******************************************************************************/

#include <msp430.h> 
/*
 * main.c
 */
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);

static volatile char data;

void main(void)
{
     WDTCTL = WDTPW + WDTHOLD; // Stop WDT
     P1DIR |= BIT0 + BIT6; // Set the LEDs on P1.0, P1.6 as outputs
     P1OUT = BIT0; // Set P1.0
     BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
     DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz

    /* Configure hardware UART */
     P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
     P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
     UCA0CTL1 |= UCSSEL_2; // Use SMCLK
     UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
     UCA0BR1 = 0; // Set baud rate to 9600 with 1MHz clock
     UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
     UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
     IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
     __bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled

     UARTSendArray("\n\n\n\r",4);
     UARTSendArray("\t\t *************************************************\n\r",54);
     UARTSendArray("\t\t               MSP430 Receive ve Led       \n\r", 47);
     UARTSendArray("\t\t *************************************************\n\r",54);
     UARTSendArray("\n\n\n\r",4);
     __delay_cycles(2000000);
     UARTSendArray("Led icin Karakter Girin ", 25);
     UARTSendArray("\n\r", 2);
     UARTSendArray("\n\r", 2);
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    data = UCA0RXBUF;

    UARTSendArray("Karakter: ", 10);
    UARTSendArray(&data, 1);
    UARTSendArray("\n\r", 2);

    switch(data)
    {
        case 'R':
        {
            P1OUT |= BIT0;
            UARTSendArray("\n\r", 2);
            UARTSendArray("Kirmizi led Acik ", 18);
            UARTSendArray("\n\r", 2);
        }
        break;
        case 'r':
        {
            P1OUT &= ~BIT0;
            UARTSendArray("\n\r", 2);
            UARTSendArray("Kirmizi led Kapali ", 19);
            UARTSendArray("\n\r", 2);
        }
        break;
        case 'G':
        {
            P1OUT |= BIT6;
            UARTSendArray("\n\r", 2);
            UARTSendArray("Yesil led Acik ", 16);
            UARTSendArray("\n\r", 2);
        }
        break;
        case 'g':
        {
            P1OUT &= ~BIT6;
            UARTSendArray("\n\r", 2);
            UARTSendArray("Yesil led Kapali ", 17);
            UARTSendArray("\n\r", 2);
        }
        break;
        default:
        {
             UARTSendArray("\n\r", 2);
             UARTSendArray("Gecersiz Karakter: ", 19);
             UARTSendArray(&data, 1);
             UARTSendArray("\n\r", 2);
        }
        break;
     }
}

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength)
{
    while(ArrayLength--)
    { // Loop until StringLength == 0 and post decrement
        while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
        UCA0TXBUF = *TxArray; //Write the character at the location specified py the pointer
        TxArray++; //Increment the TxString pointer to point to the next character
    }
}
