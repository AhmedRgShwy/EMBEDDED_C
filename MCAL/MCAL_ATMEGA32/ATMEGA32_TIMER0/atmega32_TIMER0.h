/*
 * TIMER0.h
 *
 * Created: 2/14/2016 3:31:37 PM
 *  Author: En_Ahmed Rg Shwy
 */


#ifndef TIMER_H_
#define TIMER_H_

#include "atmega32_IO.h"
#include <avr/interrupt.h>

#define TRUE_T0MODE(mode,OC0)		( ((mode==0x00||mode==0x08)&&(OC0>=0x00&&OC0<=0x03)) || ((mode==0x40||mode==0x48)&&(OC0>=0x04&&OC0<=0x05)) )
#define TRUE_CLKmode(clkmode)		(clkmode>=0x00 && clkmode<=0x07)
#define TRUE_INTmode(INTmode)		(INTmode>=0x00&&INTmode<=0x03)
#define TRUE_COMPARE(cmpval)		(cmpval>0x00&&cmpval<0xff)

/* TIMER MODE */
#define NORMAL_TIMER0	0x00
#define CTC_TIMER0		0x08
#define FASTPWM_TIMER0	0x40
#define PHASEPWM_TIMER0	0x48

/* NON-PWM OC0 MODE */
#define DISABLE_OC0		0x00
#define TOGGLE_OC0		0x01
#define CLEAR_OC0		0x02
#define SET_OC0			0x03

/* PWM OC0 MODE */
/* this value must be 0x02, but it was made by 0x04 to distinguished from non-PWM mode, it will be edited in function init. */
#define NONINVERT_OC0	0x04
/* this value must be 0x03, but it was made by 0x05 to distinguished from non-PWM mode, it will be edited in function init. */
#define INVERT_OC0		0x05

/* INTERRUPT MODE */
#define DISABLE_T0INT	0x00
#define OVERFLOW_T0INT	0x01
#define COMPARE_T0INT	0x02
#define BOTH_T0INT		0x03

/* CLOCK MODE */
#define DISABLE_CLK		0x00
#define NO_CLKPRESCALE	0x01
#define PRESCALE_8		0x02
#define PRESCALE_64		0x03
#define PRESCALE_256	0x04
#define PRESCALE_1024	0x05
#define EXTCLK_FALLINGE	0x06
#define EXTCLK_RISINGE	0x07

#define Enable_T0Strobe()		SET_BIT(TCCR0,FOC0)
#define Disable_T0Strobe()		CLR_BIT(TCCR0,FOC0)

typedef struct
{
	U8		Mode;
	U8		Prescale;
	U8		DesiredINT;
	U8		OC0PinMode;
	U8		CompVal;
	void (*pf_DoAtOverflow)(void);
	void (*pf_DoAtCompare)(void);
} sTIMER0;

/*
** This function initialize TIMER0 to run, it takes pointer to timer0 structure.
** It returns true when it succeeded otherwise it returns false
** Returning false means false arguments, something wrong in assigning the pointer structure object.
*/
U8 TIMER0_Init( sTIMER0 *tmr0 );

#endif /* TIMER_H_ */
