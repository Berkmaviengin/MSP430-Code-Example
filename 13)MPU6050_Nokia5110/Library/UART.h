////////////////////////////////////////////////////////////////////
// THU VIEN DINH NGHIA CAC HAM XU LY UART
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Email:	terran991992@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................
// AP DUNG CHO MACH UNG DUNG MSP430
//******************************************************************/


/*
 * Cac ky tu dac biet
 * 	0 Ky tu rong
 * 	1 Bat dau header
 * 	2 Bat dau van ban
 * 	3 Ket thuc van ban
 * 	4 Ket thuc truyen
 * 	5 Truy van
 * 	7 Tab ngang
 * 	8 Xoa nguoc
 * 	9 Tab ngang
 * 	10 Xuong dong
 * 	11 Tab doc
 */
#ifdef USE_UART
unsigned char UART_Read_Char();				//Nhan ki tu
void UART_Write_Char(unsigned char data);	//Gui ki tu
void UART_Write_String(char* string);		//Gui chuoi ki tu
void UART_Init();						//Khoi tao UART


/******************************************************************************\
*					Function (noi dung ham)	                           *
\******************************************************************************/

//////////////////////////////////////////
//Init UART
void UART_Init()
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	P1SEL |= BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
	P1SEL2 |= BIT1 + BIT2;
	//UCA0CTL0 |= UCPEN ;		//Parity even
	UCA0CTL1 |= UCSSEL_2; // SMCLK
	UCA0BR0 = 131; // 16Mhz/9600=139
	UCA0BR1 = 6;
	UCA0MCTL |= UCBRS0; // Modulation UCBRSx = 1
	UCA0CTL1 &=~ UCSWRST; // **Initialize USCI state machine**
	IE2 &= ~(UCA0RXIE+UCA0TXIE); // Enable USCI_A0 RX interrupt
	//	__bis_SR_register(GIE); // Interrupts enabled
}

//Nhan ki tu
unsigned char UART_Read_Char()
{
	while (!(IFG2&UCA0RXIFG)); // Doi gui xong ky tu truoc
	return UCA0RXBUF; // Moi cho phep nhan ky tu tiep theo
}
//In KyTu
void UART_Write_Char(unsigned char data)
{
	while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
	UCA0TXBUF= data; // Moi cho phep gui ky tu tiep theo
}
/////////////////////////////////////////
//In Xau
void UART_Write_String(char* string)
{
	if(*string == 0)
	{
	while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
	UCA0TXBUF= '0'; // Moi cho phep gui ky tu tiep theo
	}
	while(*string) // Het chuoi ky tu thi thoat
		{
		while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
		UCA0TXBUF= *string; // Moi cho phep gui ky tu tiep theo
		string ++; // Lay ky tu tiep theo
		_delay_cycles(16000);
		}
	UART_Write_Char(0);
}



///////////////////////////////////////////
// Convert so thuc sang string
void Convert_fl2st(float x,char *y)// length do dai, coma do dai sau .
{
	unsigned  int Temp;
	y[0]='0';//
	y[1]='.';
	Temp=(int)(x*10);//Lay phan thap phan
	y[2]=Temp+'0';//Chuyen doi sang ki tu
	Temp=(int)(((x*10-Temp)*10)+0.5);//Lay phan pham
	y[3]=Temp+'0';//Chuyen doi sang ki tu
	y[4]=0;
}

//////////////////////////////////////////
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  while (!(IFG2 & UCA0TXIFG));                // USCI_A0 TX buffer ready?
  UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
}

#endif
