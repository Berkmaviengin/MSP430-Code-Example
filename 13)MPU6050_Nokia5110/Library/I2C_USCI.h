////////////////////////////////////////////////////////////////////
// THU VIEN DINH NGHIA CAC HAM XU LY I2C
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Email:	terran991992@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................
// AP DUNG CHO MACH UNG DUNG MSP430
//******************************************************************/


#ifdef USE_I2C_USCI

#define MPU6050_ADDRESS	0x68
#define DS1307_ADDRESS	0x68
#define LM92_ADDRESS	0x48
/******************************************************************************\
*					Prototype (nguyen mau ham)    						       *
\******************************************************************************/

void Init_I2C_USCI(unsigned char addr);
void Set_Address(unsigned char addr);
unsigned char ByteRead_I2C_USCI(unsigned char address);
unsigned char ByteWrite_I2C_USCI(unsigned char address, unsigned char Data);
unsigned char WordRead_I2C_USCI(unsigned char Addr_Data,unsigned char *Data, unsigned char Length);
/******************************************************************************\
*					Function (noi dung ham)	                           *
\******************************************************************************/


void Init_I2C_USCI(unsigned char addr)
{
	P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL0 = UCMST+UCMODE_3+UCSYNC;         // I2C Master, synchronous mode
  	UCB0CTL1 = UCSSEL_2+UCSWRST;              // Use SMCLK, keep SW reset
	UCB0BR0 = 40;                             // fSCL = SMCLK/40 = ~400kHz
	UCB0BR1 = 0;
	UCB0I2CSA = addr;                         // Set slave address
	UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
}

void Set_Address(unsigned char addr)
{
  	UCB0CTL1 |= UCSWRST;    
  	UCB0I2CSA = addr;                     		// Set slave address
  	UCB0CTL1 &= ~UCSWRST;                 		// Clear SW reset, resume operation 	
}

unsigned char ByteRead_I2C_USCI(unsigned char address)
{ 	
	while (UCB0CTL1 & UCTXSTP);             	// Cho tin hieu I2C STT duoc gui di
	UCB0CTL1 |= UCTR + UCTXSTT;             	// I2C TX,START

	while (!(IFG2&UCB0TXIFG));					// Cho gui xong
	UCB0TXBUF = address;                      	// Dia chi luu gia tri Seconds

	while (!(IFG2&UCB0TXIFG));					// Cho gui xong

	UCB0CTL1 &= ~UCTR;                      // I2C RX
	UCB0CTL1 |= UCTXSTT;                    // I2C RESTART
	IFG2 &= ~UCB0TXIFG;                     // Xoa co ngat USCI_B0 TX

	while (UCB0CTL1 & UCTXSTT);             // Cho den khi I2C STT duoc gui di
	UCB0CTL1 |= UCTXSTP;                    // Gui bit STOP
	return UCB0RXBUF;
}


//doc 1 mang tu DS
unsigned char WordRead_I2C_USCI(unsigned char Addr_Data,unsigned char *Data, unsigned char Length)
{ 	
	unsigned char i=0;
	while (UCB0CTL1 & UCTXSTP);             // Loop until I2C STT is sent
	UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition

	while (!(IFG2&UCB0TXIFG));
	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi
	UCB0TXBUF = Addr_Data;                      	// Dia chi luu gia tri Seconds

	while (!(IFG2&UCB0TXIFG));
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi

	UCB0CTL1 &= ~UCTR;                      // I2C RX
	UCB0CTL1 |= UCTXSTT;                    // I2C start condition
	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
	while (UCB0CTL1 & UCTXSTT);             // Loop until I2C STT is sent
	for(i=0;i<(Length-1);i++)
	{
		while (!(IFG2&UCB0RXIFG));
		IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
		Data[i] = UCB0RXBUF;
	}
	while (!(IFG2&UCB0RXIFG));
	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
	UCB0CTL1 |= UCTXSTP;                    // I2C stop condition after 1st TX
	Data[Length-1] = UCB0RXBUF;
	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
	return 0;
}

unsigned char ByteWrite_I2C_USCI(unsigned char address, unsigned char data)
{
	while (UCB0CTL1 & UCTXSTP);             // Cho den khi tin hieu STT duoc gui xong
	UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, Gui bit START

	while (!(IFG2&UCB0TXIFG));				// Cho cho bit START gui xong
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi thì thoat khoi ham
	UCB0TXBUF = address;					// Gui dia chi thanh ghi can ghi


	while (!(IFG2&UCB0TXIFG));				// Cho gui xong
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi thì thoat khoi ham
	UCB0TXBUF = data;						// Gui du lieu

	while (!(IFG2&UCB0TXIFG));				// Cho gui xong
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi thì thoat khoi ham
	UCB0CTL1 |= UCTXSTP;                    // Gui bit STOP
	IFG2 &= ~UCB0TXIFG;                     // Xoa co USCI_B0 TX
	return 0;
}
unsigned int Read_LM92()
{
	unsigned char a;
	while (UCB0CTL1 & UCTXSTP);             // Loop until I2C STT is sent
	UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition

	while (!(IFG2&UCB0TXIFG));
	UCB0TXBUF = 0x00;                      	// Dia chi luu gia tri Seconds

	while (!(IFG2&UCB0TXIFG));

	UCB0CTL1 &= ~UCTR;                      // I2C RX
	UCB0CTL1 |= UCTXSTT;                    // I2C start condition
	IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag

	while (UCB0CTL1 & UCTXSTT);             // Loop until I2C STT is sent
	a = UCB0RXBUF;
	while (UCB0CTL1 & UCTXSTT);             // Loop until I2C STT is sent
	UCB0CTL1 |= UCTXSTP;                    // I2C stop condition after 1st TX
	return ((a<<8)|UCB0RXBUF);	
}

 
#endif




