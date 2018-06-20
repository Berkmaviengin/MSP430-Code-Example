/********************************************************
 * Yazar: Erhan YILMAZ									*
 * �sim:  Uygulama 10.1									*
 * Tarih: 04-06-2014									*
 * A��klama: SD kart kullan�m�							*
 * **************************************************** */

#include <msp430.h>			// MSP430 ba�l�k dosyas�
// SD kart kullan�m� ile ilgili k�t�phane dosyalar�
#include <stdint.h>
#include "pff2a/src/diskio.h"
#include "pff2a/src/pff.h"
#include "drivers/spi.h"
/////////////////////////////////////////////////////
// Kullan�lan fonksiyon prototipleri
void Yanlis(void);
void Dogru (void);
void Bekle(unsigned int);
// Dosya sisteminde kullan�lan de�i�kenler
	FATFS fatfs;	  // File system object
	WORD  br,bw;
	BYTE buff[64];
///////////////////////////////////////////
	unsigned char bSayac;	// Saya� de�i�keni

void main (void)
{
	WDTCTL 	=  WDTPW + WDTHOLD;		// Watchdog timeri durdur
    WDTCTL  = WDTPW | WDTHOLD;		// Watchdog timeri durdur.
    BCSCTL1 = CALBC1_16MHZ;			// Dahili osilat�r� 16MHz'e ayarla.
    DCOCTL = CALDCO_16MHZ;			// Dahili osilat�r� 16MHz'e ayarla.
	P1DIR 	&= ~BIT3;				// Port1.0 giri�
	P1SEL	&= ~BIT3;				// Port1.0 I/O olarak kullan�lacak
	P1SEL2	&= ~BIT3;				// Port1.0 I/O olarak kullan�lacak
	P1REN	|= BIT3;				// Port1.0 Pull-up/down direnci aktif
	P1OUT	|= BIT3;				// Port1.0 Pull-up �zelli�i aktif
	P2DIR	|= BIT1 + BIT2;			// Port2.1-2 ��k��
	P2SEL	&= ~(BIT1 + BIT2);		// Port2.1-2 I/O olarak kullan�lacak
	P2SEL2	&= ~(BIT1 + BIT2);		// Port2.1-2 I/O olarak kullan�lacak
	P2OUT	&= ~(BIT1 + BIT2);		// Port2.1-2 ��k��lar�n� s�f�rla
	spi_initialize();				// USCI_B0 birimini SPI i�in haz�rla

	while(1)
	{								// Sonsuz d�ng�
	    while(P1IN & BIT3);						// Butona(P1.0) bas�lmas�n� bekle
	    _delay_cycles(16000);					// Buton ark�n� �nlemek i�in bir s�re bekle
	    while(!(P1IN & BIT3));					// Butonun(P1.0) b�rak�lmas�n� bekle
	    if(pf_mount(&fatfs)==RES_OK)
	    {			// Kart� a�
	        if(pf_open("deneme.txt")==RES_OK)
	        {		// deneme.txt doyas�n� a�
	            if(pf_read(buff,64, &br)==RES_OK)
	            {		// Dosyadan 64 karakter veri oku
	                for (bSayac=0; bSayac<=63; bSayac++)	// Okunan karakterleri kontrol et
	                {

	                    if( buff[bSayac] >= 'a' && buff[bSayac] <= 'z')	// Karakter k���k harf mi?
	                        buff[bSayac] -= 0x20;					// Evet ise b�y�k harf yap.
	                }
	                if(pf_write(buff, 64, &bw)==RES_OK)
	                {	// Okunan karakterleri geri yaz
	                    if(pf_write(0, 0, &bw)==RES_OK)
	                    {		// Dosyay� kapat
	                        Dogru();								// Do�ru uyar�s� ver
	                    } else Yanlis();			// Dosya kapanmad�ysa yanl�� uyar�s� ver
	                }
	                else Yanlis();			// Karakterler yaz�lmad�ysa yanl�� uyar�s� ver
	            }
	            else Yanlis();			// Karakterler okunmad�ysa yanl�� uyar�s� ver
	        }
	        else Yanlis();			// Dosya a��lmad�ysa yanl�� uyar�s� ver
	    }
	    else Yanlis();			// Kart a��lmad�ysa yada yoksa yanl�� uyar�s� ver
	}							// Sonsuz d�ng� bitimi
}								// Ana program sonu

// Port2.1 pinine ba�l� LED ile uyar� veren fonksiyon
void Dogru(void){
	P2OUT |= BIT1;
	Bekle(1000);
	P2OUT &= ~BIT1;
	Bekle(500);
	P2OUT |= BIT1;
	Bekle(500);
	P2OUT &= ~BIT1;
	Bekle(500);
}

// Port2.2 pinine ba�l� LED ile uyar� veren fonksiyon
void Yanlis(void){
	P2OUT |= BIT2;
	Bekle(500);
	P2OUT &= ~BIT2;
	Bekle(500);
	P2OUT |= BIT2;
	Bekle(500);
	P2OUT &= ~BIT2;
	Bekle(500);
}

// Genel ama�l� bekleme fonksiyonu
void Bekle (unsigned int Bekle){
	unsigned int i;
	for(i=0;i<Bekle;i++)
	_delay_cycles(16000);
}

