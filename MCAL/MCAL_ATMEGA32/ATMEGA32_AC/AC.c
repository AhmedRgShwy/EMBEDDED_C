/*
 * AC.c
 *
 * Created: 11/24/2016 6:48:23 PM
 *  Author: AhmedShaarawy
 */ 

#include "AC.h"

U8 ACMUXOldValue;
void(*PassACIntToISR)(void);
U8 ACInit(sAC *ac)
{
	U8 check= 0x00;
	if (AC_TRUE_OBJECT(ac->ACIntMode,ac->ACIntAdjust,ac->BandgabMode,ac->TirggerTC1CapMode,ac->ACMUXMode,ac->ACMUXChannelSel))
	{
		check =0x01;
		ACSR |= (ac->BandgabMode)|(ac->ACIntMode)|(ac->TirggerTC1CapMode)|(ac->ACIntAdjust);
		SFIOR|= ac->ACMUXMode;
		if (ac->ACMUXMode)
		{
			CLR_BIT(ADCSRA,ADEN);			// disable ADC first
			ACMUXOldValue= 0x1F&ADMUX;		// keep old value to retrieve
			ADMUX |= ac->ACMUXChannelSel;	// use the MUX for AC
		}
	}
	return check;
}


U8 ACReadOutput(void)
{
	return AC_READ_OUTPUT;
}


void ACStopACMUX(void)
{
	CLR_BIT(SFIOR,ACME);
	ADMUX |= ACMUXOldValue ;
}

