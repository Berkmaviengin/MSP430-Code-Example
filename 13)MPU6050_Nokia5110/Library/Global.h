////////////////////////////////////////////////////////////////////
// THU VIEN DINH NGHIA CAC HAM DELAY
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Email:	terran991992@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................
// AP DUNG CHO MACH UNG DUNG MSP430
//******************************************************************/


/* Mot so macro thuong dung */
#ifndef sbi
	#define sbi(REG,BIT) REG |= (1<<BIT)    // set BIT trong thanh ghi REG
#endif
#ifndef cbi
	#define cbi(REG,BIT) REG &= ~(1<<BIT)   // clear BIT trong thanh ghi REG
#endif
#ifndef pin
	#define pin(x,PIN)	 (PIN) & (1<<x)
#endif
#ifndef BIT_IS_SET
	#define BIT_IS_SET(REG,BIT)     (REG&(1<<BIT))     
        // kiem tra BIT trong REG co duoc set ko
#endif
#ifndef BIT_IS_CLEAR
	#define BIT_IS_CLEAR(REG,BIT)	(!(REG&(1<<BIT)))  
        // kiem tra BTI trong REG co duoc clear ko
#endif 
#ifndef TRUE
  #define TRUE true
#endif
#ifndef FALSE
  #define FALSE false
#endif
//#ifndef BOOL
//  typedef bool BOOL;
//#endif

#define FRE 8		//Mhz

void _delay_ms(unsigned  Value) // Hàm delay
{
	volatile unsigned int i=0;
	for(i=0;i<Value;i++)_delay_cycles(1000);
}

#define _delay_us(x) _delay_cycles(x);
