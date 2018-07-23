#include <msp430.h>			// MSP430 başlık dosyası
// SD kart kullanımı ile ilgili kütüphane dosyaları
#include <stdint.h>
#include "pff2a/src/diskio.h"
#include "pff2a/src/pff.h"
#include "drivers/spi.h"
/////////////////////////////////////////////////////
// Kullanılan fonksiyon prototipleri
void Yanlis(void);
void Dogru (void);
void Bekle(unsigned int);
// Dosya sisteminde kullanılan değişkenler
	FATFS fatfs;	  // File system object
	WORD  br,bw;
	BYTE buff[64];
///////////////////////////////////////////
	unsigned char bSayac;	// Sayaç değişkeni

void main (void)
{
	WDTCTL 	=  WDTPW + WDTHOLD;		// Watchdog timeri durdur
    WDTCTL  = WDTPW | WDTHOLD;		// Watchdog timeri durdur.
    BCSCTL1 = CALBC1_16MHZ;			// Dahili osilatörü 16MHz'e ayarla.
    DCOCTL = CALDCO_16MHZ;			// Dahili osilatörü 16MHz'e ayarla.
	P1DIR 	&= ~BIT3;				// Port1.0 giriş
	P1SEL	&= ~BIT3;				// Port1.0 I/O olarak kullanılacak
	P1SEL2	&= ~BIT3;				// Port1.0 I/O olarak kullanılacak
	P1REN	|= BIT3;				// Port1.0 Pull-up/down direnci aktif
	P1OUT	|= BIT3;				// Port1.0 Pull-up özelliği aktif
	P2DIR	|= BIT1 + BIT2;			// Port2.1-2 çıkış
	P2SEL	&= ~(BIT1 + BIT2);		// Port2.1-2 I/O olarak kullanılacak
	P2SEL2	&= ~(BIT1 + BIT2);		// Port2.1-2 I/O olarak kullanılacak
	P2OUT	&= ~(BIT1 + BIT2);		// Port2.1-2 çıkışlarını sıfırla
	spi_initialize();				// USCI_B0 birimini SPI için hazırla

	while(1)
	{								// Sonsuz döngü
	    while(P1IN & BIT3);						// Butona(P1.0) basılmasını bekle
	    _delay_cycles(16000);					// Buton arkını önlemek için bir süre bekle
	    while(!(P1IN & BIT3));					// Butonun(P1.0) bırakılmasını bekle
	    if(pf_mount(&fatfs)==RES_OK)
	    {			// Kartı aç
	        if(pf_open("deneme.txt")==RES_OK)
	        {		// deneme.txt doyasını aç
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
	                    {		// Dosyayı kapat
	                        Dogru();								// Doğru uyarısı ver
	                    } else Yanlis();			// Dosya kapanmadıysa yanlış uyarısı ver
	                }
	                else Yanlis();			// Karakterler yazılmadıysa yanlış uyarısı ver
	            }
	            else Yanlis();			// Karakterler okunmadıysa yanlış uyarısı ver
	        }
	        else Yanlis();			// Dosya açılmadıysa yanlış uyarısı ver
	    }
	    else Yanlis();			// Kart açılmadıysa yada yoksa yanlış uyarısı ver
	}							// Sonsuz döngü bitimi
}								// Ana program sonu

// Port2.1 pinine bağlı LED ile uyarı veren fonksiyon
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

// Port2.2 pinine bağlı LED ile uyarı veren fonksiyon
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

// Genel amaçlı bekleme fonksiyonu
void Bekle (unsigned int Bekle){
	unsigned int i;
	for(i=0;i<Bekle;i++)
	_delay_cycles(16000);
}

