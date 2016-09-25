/*
 * atmega32_TIMER1.h
 *
 * Created: 9/21/2016 6:29:43 AM
 *  Author: AhmedShaarawy
 */ 


#ifndef ATMEGA32_TIMER1_H_
#define ATMEGA32_TIMER1_H_

#include "atmega32_IO.h"
#include <avr/interrupt.h>

/* TIMER MODE */

#define TC1_NORMAL_MODE					0x00
#define TC1_PWMPHASE_8BITTOP			0x01
#define TC1_PWMPHASE_9BITTOP			0x02
#define TC1_PWMPHASE_10BITTOP			0x03
#define TC1_CTC_OCR1ATOP				0x04				
#define TC1_FASTPWM_8BITTOP				0x05
#define TC1_FASTPWM_9BITTOP				0x06
#define TC1_FASTPWM_10BITTOP			0x07
#define TC1_PWMPHASEFREQENCY_ICR1TOP	0x08
#define TC1_PWMPHASEFREQENCY_OCR1ATOP	0x09
#define TC1_PWMPHASE_ICR1TOP			0x0A
#define TC1_PWMPHASE_OCR1ATOP			0x0B
#define TC1_CTC_ICR1TOP					0x0C
#define TC1_FASTPWM_ICR1TOP				0x0E
#define TC1_FASTPWM_OCR1ATOP			0x0F
#define TC1_TRUE_MODE(mode)				(mode>=TC1_NORMAL_MODE && mode<=TC1_FASTPWM_OCR1ATOP && mode!=0x0D)

#define TC1_MODE_IS_NONPWM(mode)		(mode==TC1_NORMAL_MODE || mode==TC1_CTC_OCR1ATOP || mode==TC1_CTC_ICR1TOP)

#define TC1_MODE_IS_PWM(mode)			(TC1_TRUE_MODE(mode) && mode!=TC1_NORMAL_MODE && mode!=TC1_CTC_OCR1ATOP && mode!=TC1_CTC_ICR1TOP)

#define TC1_ICR1_ISTOP(TC1mode)			(TC1mode==TC1_PWMPHASEFREQENCY_ICR1TOP||TC1mode==TC1_PWMPHASE_ICR1TOP||TC1mode==TC1_CTC_ICR1TOP ||\
										 TC1mode==TC1_FASTPWM_ICR1TOP)
#define TC1_ICR1_NOTTOP(TC1mode)		(TC1mode!=TC1_PWMPHASEFREQENCY_ICR1TOP&&TC1mode!=TC1_PWMPHASE_ICR1TOP&&TC1mode!=TC1_CTC_ICR1TOP&&\
										 TC1mode!=TC1_FASTPWM_ICR1TOP)


/* NON-PWM OC1x MODE */
#define TC1_OC1x_DISABLE					0x00

#define TC1_OC1x_TOGGLE						0x01
#define TC1_OC1x_CLEAR						0x02
#define TC1_OC1x_SET						0x03
#define TC1_OC1x_IS_NONPWM(mode,OC1x)	(TC1_MODE_IS_NONPWM(mode)&&(OC1x>=TC1_OC1x_TOGGLE && OC1x<=TC1_OC1x_SET))


/* PWM OC1x MODE 
** faked error by 3 , it'll be edited in init function.
*/
#define TC1_OC1A_TOGGLE				0x04
#define TC1_OC1x_NONINVERT			0x05
#define TC1_OC1x_INVERT				0x06
#define TC1_OC1x_IS_PWM(mode,OC1x)	(TC1_MODE_IS_PWM(mode)&&(OC1x>=TC1_OC1A_TOGGLE && OC1x<=TC1_OC1x_INVERT))

#define TC1_TRUE_OC1x(mode,OC1x)	(TC1_OC1x_IS_NONPWM(mode,OC1x)||TC1_OC1x_IS_PWM(mode,OC1x)||(TC1_TRUE_MODE(mode)&& OC1x==TC1_OC1x_DISABLE) )



/* INTERRUPT MODES */
#define TC1_DISABLE_ALLINTS			0x00
#define TC1_OVERFLOW_1INT			0x01
#define TC1_COMPARE1B_1INT			0x02
#define TC1_OVF_CMP1B_2INT			0x03
#define TC1_COMPARE1A_1INT			0x04
#define TC1_OVF_CMP1A_2INT			0x05
#define TC1_CMP1x_2INT				0x06
#define TC1_CMP1x_OVF_3INT			0x07
#define TC1_CAPTURE_1INT			0x08
#define TC1_CAP_OVF_2INT			0x09
#define TC1_CAP_CMP1B_2INT			0x0A
#define TC1_CAP_CMP1B_OVF_3INT		0x0B
#define TC1_CAP_CMP1A_2INT			0x0C
#define TC1_CAP_CMP1A_OVF_3INT		0x0D
#define TC1_CAP_CMP1A_CMP1B_3INT	0x0E
#define TC1_ENABLE_ALL_4INT			0x0F


#define TC1_TRUE_INTMODE(INT)	(INT>=TC1_DISABLE_ALLINTS && INT<=TC1_ENABLE_ALL_4INT) 



/* CLOCK MODE */
#define TC1_DISABLE_CLK			0x00
#define TC1_NO_CLKPRESCALE		0x01
#define TC1_CLKPRESCALE_8		0x02
#define TC1_CLKPRESCALE_64		0x03
#define TC1_CLKPRESCALE_256		0x04
#define TC1_CLKPRESCALE_1024	0x05
#define TC1_EXTCLK_FALLE 		0x06
#define TC1_EXTCLK_RISEE		0x07
#define TC1_TRUE_CLK(clk)		(clk>=TC1_DISABLE_CLK && clk<=TC1_EXTCLK_RISEE)


/* PIN ICP1 ADJUST NOISE FILTER, TRIGGER EDGE */
#define	TC1_ICP1_NO_NFILTER_FEDGE			0x00
#define TC1_ICP1_NO_NEFILTER_REDGE			0x01
#define TC1_ICP1_NFILTER_FEDGE				0x02
#define TC1_ICP1_NFILTER_REDGE				0x03
#define TC1_TRUE_ICP1_ADJUST(adjust)	(adjust>=TC1_ICP1_NO_NFILTER_FEDGE && adjust<=TC1_ICP1_NFILTER_REDGE)		



/* FORCE OUTPUT COMPARE */
#define TC1_Enable_OC1AStrobe()		SET_BIT(TCCR1A,FOC1A)
#define TC1_Enable_OC1BStrobe()		SET_BIT(TCCR1A,FOC1B)
#define TC1_Disable_OC1AStrobe()	CLR_BIT(TCCR1A,FOC1A)
#define TC1_Disable_OC1BStrobe()	CLR_BIT(TCCR1A,FOC1B)



/* RAD INTERRUPT FLAGS */
#define TC1_READ_INT_CAPTURE_FLAG()		READ_BIT(TIFR,ICF1)
#define TC1_READ_INT_CMP1A_FLAG()		READ_BIT(TIFR,OCF1A)
#define TC1_READ_INT_CMP1B_FLAG()		READ_BIT(TIFR,OCF1B)
#define TC1_READ_INT_OVF_FLAG()			READ_BIT(TIFR,TOV1)



/* READ CAPTURE REGISTER AFTER YOU HAVE TRIGGERED ICP1 */
#define TC1_READ_CAPTURE()				(ICR1&0xFFFF)


typedef struct
{
	U8		Mode;
	U8		Prescale;
	U8		DesiredINT;
	U8		OC1APinMode;
	U8		OC1BPinMode;
	U8		ICP1Adjust;
	U16		CompValA;
	U16		CompValB;
	U16		TimerStartVal;
	U16		ICR1TopVal;
	void (*pf_DoAtOverflow)(void);
	void (*pf_DoAtCompareA)(void);
	void (*pf_DoAtCompareB)(void);
	void (*pf_DoAtCapture)(void);
} sTIMER1;

#define TC1_IS_TRUE(mode,clk,INT,OC1A,OC1B,ICP1,cmpA,cmpB,tmr,ICR1Top)		TC1_TRUE_CLK(clk)&&TC1_TRUE_INTMODE(INT)&&\
																			(TC1_TRUE_OC1x(mode,OC1A)&&TC1_TRUE_OC1x(mode,OC1B))&&\
																			TC1_TRUE_ICP1_ADJUST(ICP1)&&(cmpA>=0x0000&&cmpA<=0xFFFF)&&\
																			(cmpB>=0x0000&&cmpB<=0xFFFF)&&(tmr>=0x0000&&tmr<=0xFFFF)&&\
																			(ICR1Top>=0x0000&&ICR1Top<=0xFFFF)
																				
																
U8 TC1_Init( sTIMER1 *tmr1 );



#endif /* ATMEGA32_TIMER1_H_ */