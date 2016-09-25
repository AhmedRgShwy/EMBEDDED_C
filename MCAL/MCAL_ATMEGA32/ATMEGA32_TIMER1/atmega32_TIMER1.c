/*
 * atmega32_TIMER1.c
 *
 * Created: 9/21/2016 6:29:21 AM
 *  Author: AhmedShaarawy
 */ 

#include "atmega32_TIMER1.h"

static void ( *TC1_overflowExecution )( void );
static void ( *TC1_compareMatchAExecution )( void );
static void ( *TC1_compareMatchBExecution )( void );
static void ( *TC1_captureExecution )( void );

U8 TC1_Init( sTIMER1 *tmr1 )
{
	U8 check= 0;
	if(		TC1_IS_TRUE(tmr1->Mode,tmr1->Prescale,tmr1->DesiredINT,tmr1->OC1APinMode,tmr1->OC1BPinMode,
			tmr1->ICP1Adjust,tmr1->CompValA,tmr1->CompValB,tmr1->TimerStartVal,tmr1->ICR1TopVal)	)
	{
		check= 1;
	
		//IO_PinDir(D,PIN_OC1A,OUTPUT);
		//IO_PinDir(D,PIN_OC1B,OUTPUT);
		
		/* setting registers values */
		OCR1A= tmr1->CompValA;
		OCR1B= tmr1->CompValB;
		TCNT1= tmr1->TimerStartVal;
		ICR1=  tmr1->ICR1TopVal;
		
		/* Adjusting ICP1 ( working edge and noise filter canceler ) */
		TCCR1B|= tmr1->ICP1Adjust << ICES1;
		
		/* INTERRUPT SETTING: */
		TIMSK&= ~(0x1C);
		TIMSK|= tmr1->DesiredINT << TOIE1;
		
		/* clearing the TCCR1A & TCCR1B for use */
		TCCR1A = 0x00;	TCCR1B = 0x00;
		
		/* setting clock source in CS00, CS01, CS02. */
		TCCR1B|= tmr1->Prescale;
		
		/* handling faked error in pin OC1A/B mode */
		if( TC1_OC1x_IS_PWM(tmr1->Mode,tmr1->OC1APinMode) )
			tmr1->OC1APinMode -= 2;
		if( TC1_OC1x_IS_PWM(tmr1->Mode,tmr1->OC1BPinMode) )
			tmr1->OC1BPinMode -= 2;
		
		/* setting pin mode in COM1An, COM1Bn depending on TC1 pin selection */
		TCCR1A|= tmr1->OC1APinMode << COM1A0 ;
		TCCR1A|= tmr1->OC1BPinMode << COM1B0 ;
		
		/* setting timer1 mode in WGM1n */
		TCCR1A|= tmr1->Mode&0x03 ;
		TCCR1B|= ((tmr1->Mode&0x0C)>>2) << WGM12 ;
		
		/* setting the pointers to functions for execution when interrupts */
		TC1_overflowExecution= tmr1->pf_DoAtOverflow;
		TC1_compareMatchAExecution= tmr1->pf_DoAtCompareA;
		TC1_compareMatchBExecution= tmr1->pf_DoAtCompareB;
		TC1_captureExecution= tmr1->pf_DoAtCapture;
	}
	return check;
}



ISR(TIMER1_OVF_vect)
{
	TC1_overflowExecution();
}

ISR(TIMER1_COMPA_vect)
{
	TC1_compareMatchAExecution();
}

ISR(TIMER1_COMPB_vect)
{
	TC1_compareMatchBExecution();
}


ISR(TIMER1_CAPT_vect)
{
	TC1_captureExecution();
}



