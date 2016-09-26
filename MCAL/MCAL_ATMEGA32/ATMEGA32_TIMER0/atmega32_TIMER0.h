/*
 * TIMER.h
 *
 * Created: 2/14/2016 3:31:37 PM
 *  Author: En_Ahmed Rg Shwy
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "atmega32_IO.h"
#include <avr/interrupt.h>

#define TC0_IS_TRUE(mode,OC0,clk,INT,comp,TC0val)	( TC0_TRUE_OC0(mode,OC0)&&TC0_TRUE_CLK(clk)&&TC0_TRUE_INT(INT)&&\
								TC0_TRUE_COMPARE(comp)&&(TC0val>=0x00&&TC0val<=0xff) )

#define TC0_TRUE_COMPARE(cmpval)		(cmpval>0x00&&cmpval<0xff)

											   

/* TIMER0 MODE */
#define TC0_NORMAL_MODE			0x00
#define TC0_CTC				0x08
#define TC0_FASTPWM			0x48
#define TC0_PWMPHASE			0x40
#define TC0_TRUE_MODE(mode)		(mode==TC0_NORMAL_MODE||mode==TC0_CTC||mode==TC0_FASTPWM||mode==TC0_PWMPHASE)
#define TC0_MODE_IS_NONPWM(mode)	(mode==TC0_NORMAL_MODE||mode==TC0_CTC)
#define TC0_MODE_IS_PWM(mode)		(mode==TC0_FASTPWM||mode==TC0_PWMPHASE)

/* NON-PWM OC0 MODE */
#define TC0_OC0_DISABLE				0x00
#define TC0_OC0_TOGGLE				0x01
#define TC0_OC0_CLEAR				0x02
#define TC0_OC0_SET				0x03
#define TC0_OC0_NONPWM(mode,OC0)	(TC0_TRUE_MODE(mode)&&OC0>=TC0_OC0_TOGGLE&&OC0<=TC0_OC0_SET)

/* PWM OC0 MODE */
/* this values faked by 3 error, it will be edited in function init. */
#define TC0_OC0_NONINVERT		0x05
#define TC0_OC0_INVERT			0x06 
#define TC0_OC0_PWM(mode,OC0)	(	TC0_TRUE_MODE(mode)&&(OC0==TC0_OC0_NONINVERT||OC0==TC0_OC0_INVERT)	)

#define TC0_TRUE_OC0(mode,OC0)	(	TC0_OC0_NONPWM(mode,OC0)||TC0_OC0_PWM(mode,OC0)||(TC0_TRUE_MODE(mode)&&OC0==TC0_OC0_DISABLE)	)

/* INTERRUPT MODE */
#define TC0_DISABLE_ALLINT		0x00
#define TC0_OVERFLOW_INT		0x01
#define TC0_COMPARE_INT			0x02
#define TC0_BOTH_INT			0x03
#define TC0_TRUE_INT(INT)		( INT>=TC0_DISABLE_ALLINT&&INT<=TC0_BOTH_INT )

/* CLOCK MODE:
** the Prescaler(6 > CSn2:0 > 1) shared betwwen timer0 and timer1, when it set its value you actually set the two timers prescaller 
** Also when you reset the prescaler from SFIOR at PSR10 bit, you actually reset the two timers prescaler.
*/
#define TC0_DISABLE_CLK				0x00
#define TC0_NO_CLKPRESCALE			0x01
#define TC0_TC1_CLKPRESCALE_8			0x02
#define TC0_TC1_CLKPRESCALE_64			0x03
#define TC0_TC1_CLKPRESCALE_256			0x04
#define TC0_TC1_CLKPRESCALE_1024		0x05
#define TC0_EXTCLK_T0T1PINS_FALLE		0x06
#define TC0_EXTCLK_T0T1PINS_RISEE		0x07
#define TC0_TRUE_CLK(clk)			(clk>=TC0_DISABLE_CLK&&clk<=TC0_EXTCLK_RISEE)

#define TC0_TC1_Prescaler_Reset()	SET_BIT(SFIOR,PSR10)


#define TC0_Enable_OC0Strobe(mode)		if( TC0_MODE_IS_NONPWM(mode) )\
											SET_BIT(TCCR0,FOC0)
											
#define TC0_Disable_OC0Strobe()			CLR_BIT(TCCR0,FOC0)

#define TC0_READ_INT_CMP_FLAG			READ_BIT(TIFR,OCF0)
#define TC0_CLR_INT_CMP_Flag()			CLR_BIT(TIFR,OCF0)
#define TC0_READ_INT_OVF_FLAG			READ_BIT(TIFR,TOV0)
#define TC0_CLR_INT_OVF_Flag()			CLR_BIT(TIFR,TOV0)

typedef struct  
{
	U8		Mode;
	U8		PrescaleClk;
	U8		DesiredINT;
	U8		OC0PinMode;
	U8		CompVal;
	U8		TimerStartVal;
	void (*pf_DoAtOverflow)(void);
	void (*pf_DoAtCompare)(void);
} sTIMER0;



/************************************************************************************************************************
** => FUNCTION FEATURES:
** This function initials TIMER0 with desired specifications it returns true when it succeeded, otherwise returns false.
** If it returned false, that cased by false specifications arguments.
************************************************************************************************************************/
U8 TC0_Init( sTIMER0 *tmr0 );

#endif /* TIMER_H_ */
