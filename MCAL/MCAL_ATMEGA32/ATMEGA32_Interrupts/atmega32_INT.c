/*
 * atmega32_INTERRUPTS.c
 *
 * Created: 9/29/2016 4:10:28 AM
 *  Author: AhmedShaarawy
 */ 


#include "atmega32_INT.h"
#include <avr/interrupt.h>

void (*pfDoAtEXINT0)(void);
void (*pfDoAtEXINT1)(void);
void (*pfDoAtEXINT2)(void);

U8 EXINT0_Init(sEXINT *ex)
{
	U8 check= 0;
	if(EXINT0_TRUE_SCTR(ex->SenseControl))
	{
		check= 1;
		MCUCR|= ex->SenseControl;
		SET_BIT(GICR,INT0);
		pfDoAtEXINT0= ex->pfINTAction;
	}
	return check;
}


U8 EXINT1_Init(sEXINT *ex)
{
	U8 check= 0;
	if(EXINT1_TRUE_SCTR(ex->SenseControl))
	{
		check= 1;
		MCUCR|= (ex->SenseControl)<<ISC10;
		SET_BIT(GICR,INT1);
		pfDoAtEXINT1= ex->pfINTAction;
	}
	return check;
}



U8 EXINT2_Init(sEXINT *ex)
{
	U8 check= 0;
	if(EXINT2_TRUE_SCTR(ex->SenseControl))
	{
		check= 1;
		if(ex->SenseControl==EXINT_REDGE)
			SET_BIT(MCUCSR,ISC2);
		else
			CLR_BIT(MCUCSR,ISC2);
		SET_BIT(GICR,INT2);
		pfDoAtEXINT2= ex->pfINTAction;
	}
	return check;
}



ISR(INT0_vect)
{
	pfDoAtEXINT0();
}


ISR(INT1_vect)
{
	pfDoAtEXINT1();
}


ISR(INT2_vect)
{
	pfDoAtEXINT2();
}

