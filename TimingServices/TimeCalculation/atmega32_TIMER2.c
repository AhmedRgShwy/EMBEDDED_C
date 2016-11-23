/*
 * atmega32_TIMER2.c
 *
 * Created: 9/25/2016 10:13:50 AM
 *  Author: AhmedShaarawy
 */ 


#include "atmega32_TIMER2.h"


static void ( *TC2_overflowExecution )( void );
static void ( *TC2_compareMatchExecution )( void );

U8 TC2_Init( sTIMER2 *tmr2 )
{
	U8 check= 0;
	if(	TC2_IS_TRUE(tmr2->Mode,tmr2->OC2PinMode,tmr2->Prescale,tmr2->DesiredINT,tmr2->CompVal,tmr2->TimerStartVal,tmr2->SyncModeSel))
	{
		check= 1;

		/* setting direction for OC2 */
		if(tmr2->OC2PinMode)
			IO_PinDir(D,PIN_OC2,OUTPUT);
		/* clearing the TCCR0 for use */
		TCCR2 = 0x00;
		/* clearing compare match interrupt enable OCIE2, and overflow interrupt enable TOIE2 */
		TIMSK &= ~(0x03);
		/* setting the pointer to function by address of function comes form upper layer to execute when timer overflow */
		TC2_overflowExecution = tmr2->pf_DoAtOverflow;
		/* setting the pointer to function by address of function comes form upper layer to execute when timer compare match */
		TC2_compareMatchExecution = tmr2->pf_DoAtCompare;
		
		/* setting Synchronous CLKi/o mode as sync */
		if( tmr2->SyncModeSel== TC2_SYNCHRONOUS_MODE)	CLR_BIT(ASSR,AS2);
		/* setting Synchronous CLKi/o mode as Async */
		else	SET_BIT(ASSR,AS2);

		/* setting timer2 start value to TCNT2 register OCR2 */
		TCNT2= tmr2->TimerStartVal;
		if( tmr2->SyncModeSel== TC2_ASYNCHRONOUS_MODE )
			while(TC2_READ_TCN2BUSY_FLAG);
		/* setting the compare value to compare register OCR2 */
		OCR2 = tmr2->CompVal;
		if( tmr2->SyncModeSel== TC2_ASYNCHRONOUS_MODE )
		while(TC2_READ_OCR2BUSY_FLAG);
		/* clearing INT flags */
		CLR_BIT(TIFR,TOV2);
		CLR_BIT(TIFR,OCF2);
		/* setting the desired interrupt on ( OCIE2, TOIE2 ) */
		TIMSK |= tmr2->DesiredINT;
		if( TC2_MODE_IS_PWM(tmr2->Mode) )	// if it PWM mode
		tmr2->OC2PinMode -= 3;			// then must subtracted by 3
		TCCR2 |= ( (tmr2->OC2PinMode) << COM20 );
		if( tmr2->SyncModeSel== TC2_ASYNCHRONOUS_MODE )
			while(TC2_READ_TCR2BUSY_FLAG);
		/* setting timer2 mode in WGM2n */
		TCCR2 |= tmr2->Mode;
		if( tmr2->SyncModeSel== TC2_ASYNCHRONOUS_MODE )
			while(TC2_READ_TCR2BUSY_FLAG);
		/* setting clock source in CS2n */
		TCCR2 |= tmr2->Prescale;
		if( tmr2->SyncModeSel== TC2_ASYNCHRONOUS_MODE )
			while(TC2_READ_TCR2BUSY_FLAG);
	}
	return check;
}


ISR( TIMER2_OVF_vect )
{
	TC2_overflowExecution();
}


ISR( TIMER2_COMP_vect )
{
	TC2_compareMatchExecution();
}



