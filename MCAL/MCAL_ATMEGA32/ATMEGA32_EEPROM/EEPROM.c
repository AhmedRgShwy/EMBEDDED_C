/*
 * EEPROM.c
 *
 * Created: 11/23/2016 5:09:45 PM
 *  Author: AhmedShaarawy
 */ 


#include "EEPROM.h"


void (*PasstoEEPROMReadyISR)(void);
U8 EEPROMWriteByte(U8 data, U16 address)
{
	U8 check= 0x00;
	if (address>=0 && address<=0x03FF )
	{
		check= 0x01;
		while( (EECR & (1<<EEWE)) != 0);
		EEDR = data ;
		EEAR = address ;
		EECR |= (1<<EEMWE);
		EECR |= (1<<EEWE) ;
	}
	
	return check;
}


U8 EEPROMReadByte(U16 address, U8 *ReadData)
{
	U8 check= 0x00;
	if ( address>=0 && address<=0x03FF )
	{
		check= 0x01;
		while( (EECR & (1<<EEWE)) != 0);
		EEAR = address ;
		EECR |= (1<<EERE);
		*ReadData= EEDR ;
	}
	
	return check;
}


void EEPROMIntInit(void(*PassToEEPROMIntRedyVector)(void))
{
	PasstoEEPROMReadyISR= PassToEEPROMIntRedyVector;
	EECR|= 1<<EERIE;
}



ISR(EE_RDY_vect)
{
	PasstoEEPROMReadyISR();
}