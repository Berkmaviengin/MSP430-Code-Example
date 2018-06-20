/********************************************************
 * Yazar: Erhan YILMAZ									*
 * Ýsim:  Uygulama 10.1									*
 * Tarih: 04-06-2014									*
 * Açýklama: SD kart kullanýmý							*
 * **************************************************** */

#include <msp430.h>			// MSP430 baþlýk dosyasý
// SD kart kullanýmý ile ilgili kütüphane dosyalarý
#include <stdint.h>
#include "pff2a/src/diskio.h"
#include "pff2a/src/pff.h"
#include "drivers/spi.h"
/////////////////////////////////////////////////////
// Kullanýlan fonksiyon prototipleri
void Yanlis(void);
void Dogru (void);
void Bekle(unsigned int);
// Dosya sisteminde kullanýlan deðiþkenler
	FATFS fatfs;	  // File system object
	WORD  br,bw;
	BYTE buff[64];
///////////////////////////////////////////
	unsigned char bSayac;	// Sayaç deðiþkeni

void main (void)
{
	WDTCTL 	=  WDTPW + WDTHOLD;		// Watchdog timeri durdur
    WDTCTL  = WDTPW | WDTHOLD;		// Watchdog timeri durdur.
    BCSCTL1 = CALBC1_16MHZ;			// Dahili osilatörü 16MHz'e ayarla.
    DCOCTL = CALDCO_16MHZ;			// Dahili osilatörü 16MHz'e ayarla.
	P1DIR 	&= ~BIT3;				// Port1.0 giriþ
	P1SEL	&= ~BIT3;				// Port1.0 I/O olarak kullanýlacak
	P1SEL2	&= ~BIT3;				// Port1.0 I/O olarak kullanýlacak
	P1REN	|= BIT3;				// Port1.0 Pull-up/down direnci aktif
	P1OUT	|= BIT3;				// Port1.0 Pull-up özelliði aktif
	P2DIR	|= BIT1 + BIT2;			// Port2.1-2 çýkýþ
	P2SEL	&= ~(BIT1 + BIT2);		// Port2.1-2 I/O olarak kullanýlacak
	P2SEL2	&= ~(BIT1 + BIT2);		// Port2.1-2 I/O olarak kullanýlacak
	P2OUT	&= ~(BIT1 + BIT2);		// Port2.1-2 çýkýþlarýný sýfýrla
	spi_initialize();				// USCI_B0 birimini SPI için hazýrla

	while(1)
	{								// Sonsuz döngü
	    while(P1IN & BIT3);						// Butona(P1.0) basýlmasýný bekle
	    _delay_cycles(16000);					// Buton arkýný önlemek için bir süre bekle
	    while(!(P1IN & BIT3));					// Butonun(P1.0) býrakýlmasýný bekle
	    if(pf_mount(&fatfs)==RES_OK)
	    {			// Kartý aç
	        if(pf_open("deneme.txt")==RES_OK)
	        {		// deneme.txt doyasýný aç
	            if(pf_read(buff,64, &br)==RES_OK)
	            {		// Dosyadan 64 karakter veri oku
	                for (bSayac=0; bSayac<=63; bSayac++)	// Okunan karakterleri kontrol et
	                {

	                    if( buff[bSayac] >= 'a' && buff[bSayac] <= 'z')	// Karakter küçük harf mi?
	                        buff[bSayac] -= 0x20;					// Evet ise büyük harf yap.
	                }
	                if(pf_write(buff, 64, &bw)==RES_OK)
	                {	// Okunan karakterleri geri yaz
	                    if(pf_write(0, 0, &bw)==RES_OK)
	                    {		// Dosyayý kapat
	                        Dogru();								// Doðru uyarýsý ver
	                    } else Yanlis();			// Dosya kapanmadýysa yanlýþ uyarýsý ver
	                }
	                else Yanlis();			// Karakterler yazýlmadýysa yanlýþ uyarýsý ver
	            }
	            else Yanlis();			// Karakterler okunmadýysa yanlýþ uyarýsý ver
	        }
	        else Yanlis();			// Dosya açýlmadýysa yanlýþ uyarýsý ver
	    }
	    else Yanlis();			// Kart açýlmadýysa yada yoksa yanlýþ uyarýsý ver
	}							// Sonsuz döngü bitimi
}								// Ana program sonu

// Port2.1 pinine baðlý LED ile uyarý veren fonksiyon
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

// Port2.2 pinine baðlý LED ile uyarý veren fonksiyon
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

// Genel amaçlý bekleme fonksiyonu
void Bekle (unsigned int Bekle){
	unsigned int i;
	for(i=0;i<Bekle;i++)
	_delay_cycles(16000);
}

