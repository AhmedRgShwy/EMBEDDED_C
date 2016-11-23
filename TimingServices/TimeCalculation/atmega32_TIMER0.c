/*
 * TIMER.c
 *
 * Created: 9/21/2016 7:25:02 PM
 *  Author: Ahmed Ragab Shaarawy
 */ 


#include "atmega32_TIMER0.h"


static void ( *TC0_overflowExecution )( void );
static void ( *TC0_compareMatchExecution )( void );

U8 TC0_Init( sTIMER0 *tmr0 )
{
	U8 check= 0;
	if(	TC0_IS_TRUE(tmr0->Mode,tmr0->OC0PinMode,tmr0->PrescaleClk,tmr0->DesiredINT ) )
	{
		check= 1;
		
		if(tmr0->OC0PinMode)
			IO_PinDir(B,PIN_OC0,OUTPUT);
		/* setting the compare value to compare register OCR0 */
		OCR0 = tmr0->CompVal;
		
		/* setting timer0 start value to TCNT0 register OCR0 */
		TCNT0= tmr0->TimerStartVal;
	
		/* INTERRUPT SETTING:
		** (1) clearing compare match interrupt enable OCIE0, and overflow interrupt enable TOIE0 
		** (2) setting the desired interrupt on ( OCIE0, TOIE0 )
		*/
		TIMSK &= ~(0x03);	
		TIMSK |= tmr0->DesiredINT;
		
		/* clearing the TCCR0 for use */
		TCCR0 = 0x00;
	
		/* setting pin mode in COM00, COM01 */
		if( TC0_MODE_IS_PWM(tmr0->Mode) )	// if it PWM mode 
			tmr0->OC0PinMode -= 3;			// then must subtracted by 3
		TCCR0 |= ( (tmr0->OC0PinMode) << COM00 );

		/* setting timer0 mode in WGM00, WGM01 */
		TCCR0 |= tmr0->Mode;
	
		/* setting the pointer to function by address of function comes form upper layer to execute when timer overflow */
		TC0_overflowExecution = tmr0->pf_DoAtOverflow;
	
		/* setting the pointer to function by address of function comes form upper layer to execute when timer compare match */
		TC0_compareMatchExecution = tmr0->pf_DoAtCompare;
		
		/* setting clock source in CS00, CS01, CS02. */
		TCCR0 |= tmr0->PrescaleClk;
	}
	return check;
}



ISR( TIMER0_OVF_vect )
{
	TC0_overflowExecution();
}



ISR( TIMER0_COMP_vect )
{
	TC0_compareMatchExecution();
}
	
