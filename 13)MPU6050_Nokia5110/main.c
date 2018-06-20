#define USE_CLOCK
#define USE_I2C_USCI
#define USE_MPU6050
#define USE_UART

////////////////////////////////////////////////////////////////////////////////


#include <wchar.h>
#include "stdio.h"
#include <string.h>
#include "Library/mymath.h"
#include <math.h>
#include "msp430g2553.h"
#include "Library/Global.h"
#include "Library/UART.h"
#include "Library/Clock.h"
#include "Library/I2C_USCI.h"
#include "Library/MPU6050.h"
#include <msp430.h>
#include "nokia_5110.h"
#include "bmp_pixel.h"
int temp=0,i=0;
int abc=0;
unsigned char x[20];
unsigned char y[20];
unsigned char z[20];
char buff[50];
char buff1[50];
char buff2[50];
/******************************************************************************/
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer

    LCD_init();
    LCD_clear();
    __delay_cycles(1000000);
    _delay_cycles(100000);
    Init_I2C_USCI(MPU6050_ADDRESS);
    Setup_MPU6050();
    _delay_cycles(320000);
    Get_Accel_Values();
    Get_Gyro_Values();
    ACCEL_XOUT = 0;
    ACCEL_YOUT = 0;
    ACCEL_ZOUT = 0;
    ACCEL_XOUT_PAST=0;          //
    ACCEL_YOUT_PAST=0;
    ACCEL_ZOUT_PAST=0;
    ACCEL_XA    =0;
    ACCEL_YA    =0;
    ACCEL_ZA    =0;
    ACCEL_XV    = 0;
    ACCEL_YV    = 0;
    ACCEL_ZV    = 0;
    ACCEL_XDECAC=0;
    ACCEL_YDECAC=0;
    ACCEL_ZDECAC=0;
    _delay_cycles(1000000);
    while(1)
    {
        LCD_clear();
        LCD_write_english_string(1,0,"Accelerometer");
        unsigned char x[20]="X: ";
        unsigned char y[20]="Y: ";
        unsigned char z[20]="Z: ";
        sprintf(buff,"%d",ACCEL_XOUT);
        strcat(x, buff);
        sprintf(buff1,"%d",ACCEL_YOUT);
        strcat(y, buff1);
        sprintf(buff2,"%d",ACCEL_ZOUT);
        strcat(z, buff2);
        Get_Accel_Values();
        LCD_write_english_string(20,2,x);
        LCD_write_english_string(20,3,y);
        LCD_write_english_string(20,4,z);
        __delay_cycles(8000000);
                //LCD_write_chinese_string(12,2,12,4,0,5);
                //LCD_write_chinese_string(0,4,12,7,4,0);

    }

}
