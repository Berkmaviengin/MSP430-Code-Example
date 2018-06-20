////////////////////////////////////////////////////////////////////
// THU VIEN HAM CLOCK
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Email:	terran991992@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................
// AP DUNG CHO MACH UNG DUNG MSP430
//******************************************************************/

#ifdef USE_CLOCK
//Chu y thach anh ngoai khong mo phong bang protues duoc
typedef enum { 	DCO_10KHZ,VLO,							//Tan so noi cuc thap,VLO:12Khz
				DCO_100KHZ,								//Tan so noi thap
				DCO_1MHZ,DCO_8MHZ,DCO_12MHZ,DCO_16MHZ,	//Tan so noi cao
				LF,								//Su dung thach anh ngoai tan so thap - 32.768Khz
				HF_1,					//Su dung thach anh ngoai tan so tu 0.4 - 1MHZ
				HF_2,					//Su dung thach anh ngoai tan so tu 1 - 3MHZ
				HF_3					//Su dung thach anh ngoai tan so tu 3 - 16MHZ
				} CLOCK;		
				
void Select_Clock(CLOCK str);
/******************************************************************************\
*					Function (noi dung ham)	                           *
\******************************************************************************/
//////////////////////////////////////////////////////
// Voi xung noi,khi mo phong protues de su dung dien ap nguon cap la 2.7V
// Dien ap khi su dung thuc te la 3.3 V , voi RSEL<=9 thi coi nhu clock=1,5,clock(U=1.8V)
void Select_Clock(CLOCK str)
{
	switch(str)
	{
		case DCO_10KHZ:
		{			
			BCSCTL1 = XT2OFF ;//RSELx=0
			DCOCTL =0;//DCOx=1 MODx=0
			//Setup MCLK:Clock dung cho CPU
			BCSCTL2 =SELM_0 + DIVM_3 ;//DIVMx=8
			break;
		}
		case DCO_100KHZ:
		{
			BCSCTL1 = XT2OFF;//RSELx=0
			DCOCTL = 0x00;//DCOx=0 MODx=0
			//Setup MCLK:Clock dung cho CPU
			BCSCTL2 =SELM_0 ;//DIVMx=0 ,dung dien tro trong
			break;
		}		
		case DCO_1MHZ:
		{
			BCSCTL1 = CALBC1_1MHZ;
			DCOCTL = CALDCO_1MHZ;
			BCSCTL1 |= XT2OFF;
			//Setup MCLK:Clock dung cho CPU
			BCSCTL2 = SELM_0 ;//DIVMx=0
			break;
		}
		case DCO_8MHZ:
		{
			BCSCTL1 = CALBC1_8MHZ;
			DCOCTL = CALDCO_8MHZ;
			BCSCTL1 |= XT2OFF;
			//Setup MCLK
			BCSCTL2 = SELM_0;
			break;
		}
		case DCO_12MHZ:
		{
			BCSCTL1 = CALBC1_12MHZ;
			DCOCTL = CALDCO_12MHZ;
			BCSCTL1 |= XT2OFF;
			//Setup MCLK
			BCSCTL2 = SELM_0;
			break;
		}
		case DCO_16MHZ:
		{
			BCSCTL1 = CALBC1_16MHZ;
			DCOCTL = CALDCO_16MHZ;
			BCSCTL1 |= XT2OFF;
			//Setup MCLK
			BCSCTL2 = SELM_0;
			break;
		}
		case VLO:
		{
			BCSCTL1 &= ~XTS;
			BCSCTL1 |= XT2OFF;
			BCSCTL3 = LFXT1S_2;
			BCSCTL2 = SELM_3 + SELS;
			break;
		}
		case LF:
		{
			BCSCTL1 &= ~XTS;		//Chon tan so thach anh thap,mac dinh laf 32.768Khz
			BCSCTL3 = XCAP_1;
			BCSCTL2 = SELM_3 + SELS;
		}
		case HF_1:
		{
			BCSCTL1 = XT2OFF + XTS;
			BCSCTL2 = SELM_3 + SELS;
			BCSCTL3 = LFXT1S_0;	
			break;		
		}
		case HF_2:
		{
			BCSCTL1 = XT2OFF + XTS;
			BCSCTL2 = SELM_3 + SELS;
			BCSCTL3 = LFXT1S_1;	
			break;		
		}
		case HF_3:
		{
			BCSCTL1 = XT2OFF + XTS;
			_delay_cycles(1000);
			BCSCTL2 = SELM_3 + SELS;
			BCSCTL3 = LFXT1S_2 +XT2S_2;//+ XCAP_3;
			break;		
		}		
	}	
}

#endif

