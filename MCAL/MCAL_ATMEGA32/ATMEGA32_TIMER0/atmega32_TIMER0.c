/*
 * TIMER.c
 *
 * Created: 9/21/2016 7:25:02 PM
 * Author: Ahmed Ragab Shaarawy
 */ 


#include "atmega32_TIMER0.h"


static void ( *overflowExecution )( void );
static void ( *compareMatchExecution )( void );

U8 TIMER0_Init( sTIMER0 *tmr0 )
{
	U8 check= 0;
	if( TRUE_T0MODE(tmr0->Mode,tmr0->OC0PinMode)&&TRUE_CLKmode(tmr0->Prescale)&&TRUE_INTmode(tmr0->DesiredINT)&&TRUE_COMPARE(tmr0->CompVal) )
	{
		check= 1;
		
		IO_PinDir(B,PIN_OC0,OUTPUT);
		/* setting the compare value to compare register OCR0 */
		OCR0 = tmr0->CompVal;
	
		/* INTERRUPT SETTING:
		** (1) clearing compare match interrupt enable OCIE0, and overflow interrupt enable TOIE0 
		** (2) setting the desired interrupt on ( OCIE0, TOIE0 )
		*/
		TIMSK &= ~(0x03);	
		TIMSK |= tmr0->DesiredINT;
	
		/* clearing the TCCR0 for use */
		TCCR0 = 0x00;

		/* setting clock source in CS00, CS01, CS02. */
		TCCR0 |= tmr0->Prescale;
	
		/* setting pin mode in COM00, COM01 */
		if(tmr0->OC0PinMode== NONINVERT_OC0 || tmr0->OC0PinMode== INVERT_OC0)  // if it PWM mode 
			tmr0->OC0PinMode -= 2;					       // then must subtracted by 2
		TCCR0 |= ( (tmr0->OC0PinMode) << 4 );

	
		/* setting timer0 mode in WGM00, WGM01 */
		TCCR0 |= tmr0->Mode;
	
		/* setting the pointer to function by address of function comes form upper layer to execute when timer overflow */
		overflowExecution = tmr0->pf_DoAtOverflow;
	
		/* setting the pointer to function by address of function comes form upper layer to execute when timer compare match */
		compareMatchExecution = tmr0->pf_DoAtCompare;
	}
	return check;
}


ISR( TIMER0_OVF_vect )
{
	overflowExecution();
}

ISR( TIMER0_COMP_vect )
{
	compareMatchExecution();
}
	
