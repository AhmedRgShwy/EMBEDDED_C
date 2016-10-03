/*
 * atmega32_SPI.c
 *
 * Created: 9/29/2016 9:35:32 AM
 *  Author: AhmedShaarawy
 */ 



#include "atmega32_SPI.h"

U8 SPI_GlobalMastring= 0xFF; 

void (*pfDoAtCompleteShifting)(void);
U8 SPI_MasterInit(sSPIMaster *spi)
{
	U8 check= 0;
	if(SPI_TRUE_MSTR_ADJUST(spi->INTAdjust,spi->SCKAdjust,spi->SpeedPrescale,DATA_SHIFT_ORDER,SSPIN_DIRCTION,MOSIPIN_DIRECTION,SCKPIN_DIRECTION))
	{
		check= 1;
		IO_PinDir(B,PIN_SS,SSPIN_DIRCTION);
		IO_PinDir(B,PIN_SCK,SCKPIN_DIRECTION);
		IO_PinDir(B,PIN_MOSI,MOSIPIN_DIRECTION);
		SPCR= 0x00;
		SET_BIT(SPCR,MSTR);
		SPI_GlobalMastring= 0x01;
		SPCR|= ( (1<<SPE)|spi->INTAdjust|DATA_SHIFT_ORDER|spi->SCKAdjust|(spi->SpeedPrescale&0x03) );
		SPSR|= spi->SpeedPrescale&0x04 ;
		pfDoAtCompleteShifting= spi->pfINTAction ;
	}
	return check;
}


U8 SPI_SlaveInit(sSPISlave *spi)
{
	U8 check= 0;
	if(SPI_TRUE_SLV_ADJUST(spi->INTAdjust,MISOPIN_DIRECTION))
	{
		check= 1;
		IO_PinDir(B,PIN_MISO,MISOPIN_DIRECTION);
		SPCR= SPI_GlobalMastring= 0x00;
		SPCR|= ( (1<<SPE)|spi->INTAdjust|spi->SCKAdjust ) ;
		pfDoAtCompleteShifting= spi->pfINTAction;
	}
	return check;
}



U8 SPI_MasterTx(U8 u8Data)
{
	U8 check= 0x00;
	if(SPI_TRUE_MSTR && MOSIPIN_DIRECTION == OUTPUT )
	{
		check= 0x01;
		SPDR= u8Data;
		while(!SPI_CHECK_COMPLETE_SHIFT);
	}
	return check;
}


U8 SPI_MasterCapture(U8 *u8HeldData)
{
	U8 check= 0x00;
	if(SPI_TRUE_MSTR)
	{
		check= 0x01;
		while(!SPI_CHECK_COMPLETE_SHIFT);
		*u8HeldData= SPDR;
	}
	return check;
}



U8 SPI_SlaveUpdate(U8 u8Data)
{
	U8 check= 0x00;
	if( SPI_TRUE_SLV && MISOPIN_DIRECTION == OUTPUT )
	{
		check= 0x01;
		while(!SPI_CHECK_COMPLETE_SHIFT);
		SPDR= u8Data;
	}
	return check;
}


U8 SPI_SlaveRx(U8 *u8RxData)
{
	U8 check= 0x00;
	if(SPI_TRUE_SLV)
	{
		check= 0x01;
		while(!SPI_CHECK_COMPLETE_SHIFT);
		*u8RxData= SPDR;
	}
	return check;
}



ISR(SPI_STC_vect)
{
	if(SPI_TRUE_SLV||SPI_TRUE_MSTR)
		pfDoAtCompleteShifting();
}