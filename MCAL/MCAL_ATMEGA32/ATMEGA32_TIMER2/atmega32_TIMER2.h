/*
 * atmega32_TIMER2.h
 *
 * Created: 9/25/2016 10:14:12 AM
 *  Author: AhmedShaarawy
 */ 


#ifndef ATMEGA32_TIMER2_H_
#define ATMEGA32_TIMER2_H_

#include "atmega32_IO.h"
#include <avr/interrupt.h>



#define TC2_IS_TRUE(mode,OC2,clk,INT,comp,TC2val,syncSel)	( TC2_TRUE_OC2(mode,OC2)&&TC2_TRUE_CLK(clk)&&TC2_TRUE_INT(INT)&&\
															  TC2_TRUE_COMPARE(comp)&&(TC2val>=0x00&&TC2val<=0xff)&&TC2_TRUE_SYNC_MODE(syncSel) )

#define TC2_TRUE_COMPARE(cmpval)		(cmpval>0x00&&cmpval<0xff)


/* SYNCHRONIZATIOM */
#define TC2_SYNCHRONOUS_MODE			0xA0
#define TC2_ASYNCHRONOUS_MODE			0xB0
#define TC2_TRUE_SYNC_MODE(syncSel)		(syncSel==TC2_SYNCHRONOUS_MODE||syncSel==TC2_ASYNCHRONOUS_MODE)


/* TIMER2 MODE */
#define TC2_NORMAL_MODE				0x00
#define TC2_CTC						0x08
#define TC2_FASTPWM					0x48
#define TC2_PWMPHASE				0x40
#define TC2_TRUE_MODE(mode)			(mode==TC2_NORMAL_MODE||mode==TC2_CTC||mode==TC2_FASTPWM||mode==TC2_PWMPHASE)
#define TC2_MODE_IS_NONPWM(mode)	(mode==TC2_NORMAL_MODE||mode==TC2_CTC)
#define TC2_MODE_IS_PWM(mode)		(mode==TC2_FASTPWM||mode==TC2_PWMPHASE)


/* NON-PWM OC2 MODE */
#define TC2_OC2_DISABLE				0x00
#define TC2_OC2_TOGGLE				0x01
#define TC2_OC2_CLEAR				0x02
#define TC2_OC2_SET					0x03
#define TC2_OC2_NONPWM(mode,OC2)	(TC2_TRUE_MODE(mode)&&OC2>=TC2_OC2_TOGGLE&&OC2<=TC2_OC2_SET)

/* PWM OC2 MODE */
/* this values faked by 3 error, it will be edited in function init. */
#define TC2_OC2_NONINVERT		0x05
#define TC2_OC2_INVERT			0x06

#define TC2_OC2_PWM(mode,OC2)	(	TC2_TRUE_MODE(mode)&&(OC2==TC2_OC2_NONINVERT||OC2==TC2_OC2_INVERT)	)

#define TC2_TRUE_OC2(mode,OC2)	(	TC2_OC2_NONPWM(mode,OC2)||TC2_OC2_PWM(mode,OC2)||(TC2_TRUE_MODE(mode)&&OC2==TC2_OC2_DISABLE)	)


/* INTERRUPT MODE */
#define TC2_DISABLE_ALLINT		0x00
#define TC2_OVERFLOW_INT		0x40
#define TC2_COMPARE_INT			0x80
#define TC2_BOTH_INT			0xC0
#define TC2_TRUE_INT(INT)		( INT==TC2_DISABLE_ALLINT||INT==TC2_OVERFLOW_INT||INT==TC2_COMPARE_INT||INT==TC2_BOTH_INT )


/* CLOCK MODE */
#define TC2_DISABLE_CLK			0x00
#define TC2_NO_CLKPRESCALE		0x01
#define TC2_CLKPRESCALE_8		0x02
#define TC2_CLKPRESCALE_32		0x03
#define TC2_CLKPRESCALE_64		0x04
#define TC2_CLKPRESCALE_128		0x05
#define TC2_CLKPRESCALE_256		0x06
#define TC2_CLKPRESCALE_1024	0x07
#define TC2_TRUE_CLK(clk)		(clk>=TC2_DISABLE_CLK&&clk<=TC2_CLKPRESCALE_1024)


#define TC2_Enable_OC2Strobe(mode)		if( TC2_MODE_IS_NONPWM(mode) ) SET_BIT(TCCR2,FOC2);\
										if( READ_BIT(ASSR,AS2) ) while(TC2_READ_TCR2BUSY_FLAG)
											
#define TC2_Prescaler_Reset()			SET_BIT(SFIOR,PSR2)

#define TC2_READ_INT_CMP_FLAG			READ_BIT(TIFR,OCF2)
#define TC2_CLR_INT_CMP_Flag()			CLR_BIT(TIFR,OCF2)
#define TC2_READ_INT_OVF_FLAG			READ_BIT(TIFR,TOV2)
#define TC2_CLR_INT_OVF_Flag()			CLR_BIT(TIFR,TOV2)
#define TC2_READ_TCN2BUSY_FLAG			READ_BIT(ASSR,TCN2UB)
#define TC2_CLR_TCN2Busy_Flag()			CLR_BIT(ASSR,TCN2UB)
#define TC2_READ_OCR2BUSY_FLAG			READ_BIT(ASSR,OCR2UB)
#define TC2_CLR_OCR2Busy_Flag()			CLR_BIT(ASSR,OCR2UB)
#define TC2_READ_TCR2BUSY_FLAG			READ_BIT(ASSR,TCR2UB)
#define TC2_CLR_TCR2Busy_Flag()			CLR_BIT(ASSR,TCR2UB)



typedef struct
{
	U8		SyncModeSel;
	U8		Mode;
	U8		Prescale;
	U8		DesiredINT;
	U8		OC2PinMode;
	U8		CompVal;
	U8		TimerStartVal;
	double	CLKT2;
	void (*pf_DoAtOverflow)(void);
	void (*pf_DoAtCompare)(void);
} sTIMER2;



/************************************************************************************************************************
** => FUNCTION FEATURES:
** This function initials TIMER2 with desired specifications it returns true when it succeeded, otherwise returns false.
** If it returned false, that cased by false specifications arguments.
************************************************************************************************************************/
U8 TC2_Init( sTIMER2 *tmr2 );




#endif /* ATMEGA32_TIMER2_H_ */