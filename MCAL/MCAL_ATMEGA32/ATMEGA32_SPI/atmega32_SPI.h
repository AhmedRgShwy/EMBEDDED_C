/*
 * atmega32_SPI.h
 *
 * Created: 9/29/2016 9:35:52 AM
 *  Author: AhmedShaarawy
 */ 


#ifndef ATMEGA32_SPI_H_
#define ATMEGA32_SPI_H_

#include "atmega32_lib.h"
#include "atmega32_IO.h"
#include <avr/interrupt.h>


/************************************************************************************************************************/
//	=>> MAKROS SETTINGS:

// (1) At MASTER Mode:
/* if you need to select the slave make it output, and use the MSTER select MAKRO before sending data.
	** if it made input it should held high to ensure MASTER mode.
	** if it made input and held low SPI will turned to SLV mode, to retrieve MASTER mode set bit MSTR in SPCR. */
#define SSPIN_DIRCTION		OUTPUT
#define MOSIPIN_DIRECTION	OUTPUT
// is chosen from section 3
#define DATA_SHIFT_ORDER	SPI_MSB_FIRST
#define SCKPIN_DIRECTION	OUTPUT
//=========================

// (2) At SLAVE MODE:
#define MISOPIN_DIRECTION	OUTPUT
/************************************************************************************************************************/




/******************************** ( SECTION 1 ) *****************************************************
** SCK polarity and phase
** pol == 1, sck is high when idle _HIDLE_
** pol == 0, sck is low when idle _LIDLE_
** phase == 0, sck sample at falling edge
** phase == 1, sck sample at rising edge
*/
#define SPI_SCK_LIdLE_REDGE				0x00
#define SPI_SCK_LIdLE_FEDGE				0x04
#define SPI_SCK_HIdLE_REDGE				0x08
#define SPI_SCK_HIdLE_FEDGE				0x0C
#define SPI_TRUE_SCK_ADJUST(adjust)		(adjust==0x00||adjust==0x04||adjust==0x08||adjust==0x0C)
/****************************************************************************************************/



/*********************************** ( SECTION 2 ) **************************************************
** interrupt adjust */
#define SPI_INT_ENABLE		0x80
#define SPI_INT_DISABLE		0x00
#define SPI_TRUE_INT(INT)	(INT==0x00||INT==0x80)
/***************************************************************************************************/




/********************************* ( SECTION 3 ) **************************************************
** data shifting order adjust */
#define SPI_LSB_FIRST			0x20
#define SPI_MSB_FIRST			0x00
#define SPI_TRUE_DORDER(order)	(order==0x00||order==0x20)
/**************************************************************************************************/




/******************************** ( SECTION 4 ) **************************************************
** SPI control clock/pre-scale speed */
#define SPI_PRESCALE_4			0x00
#define SPI_PRESCALE_16			0x01
#define SPI_PRESCALE_64			0x02
#define SPI_PRESCALE_128		0x03
#define SPI_2X_PRESCALE_2		0x04
#define SPI_2X_PRESCALE_8		0x05
#define SPI_2X_PRESCALE_32		0x06
#define SPI_2X_PRESCALE_64		0x07
#define SPI_TRUE_SCALE(scal)	(scal>=0x00&&scal<=0x07)
/************************************************************************************************/




/******************************* ( SECTION 5 ) ************************************************
** if flag set then shifting is completed */
#define SPI_CHECK_COMPLETE_SHIFT	(READ_BIT(SPSR,SPIF))
/* if read == 1 then there is a write collision */
#define SPI_CHECK_WRCOLLISION		(READ_BIT(SPSR,WCOL))
/* if read == 1 then it is a master */
#define SPI_CHECK_MASTER			(READ_BIT(SPSR,MSTR))
/*********************************************************************************************/


/******************************* ( SECTION 6 ) ************************************************
** Control and synchronize slave:.
** the first MAKRO must be used before the master transmit if MASTER mode and the SS is output.
** the second MAKRO should be used after transmitting, if MASTER mode and transmission needed to terminated.
*/
#define SPI_MSTR_SelectSLV()	IO_PinWrite(B,PIN_SS,0)
#define SPI_MSTR_ReleaseSLV()	IO_PinWrite(B,PIN_SS,1)
/*********************************************************************************************/


typedef struct{
	U8 INTAdjust;
	U8 SCKAdjust;
	U8 SpeedPrescale;
	void (*pfINTAction)(void);
	}sSPIMaster;

/* 
** this global variable is for monitor whether SS is held low when it is input or not,
** if it held low it will generate an interrupt and the interrupt will set the MSR bit in SPCR.
** Because of flipping of MASTER bit, there is a protection in functions Tx, Rx, update, capture.
*/

#define SPI_TRUE_MSTR 	(SPI_GlobalMastring==0x01 /*&& SPI_CHECK_MASTER*/)
#define SPI_TRUE_SLV		(SPI_GlobalMastring==0x00 && !SPI_CHECK_MASTER)


#define SPI_TRUE_MSTR_ADJUST(INT,SCK,scal,ordr,sspin,mosipin,sck)		SPI_TRUE_INT(INT)&&SPI_TRUE_SCK_ADJUST(SCK)&&SPI_TRUE_SCALE(scal)&&\
																		SPI_TRUE_DORDER(ordr)&&(sspin==OUTPUT||sspin==INPUT)&&\
																		(mosipin==OUTPUT||mosipin==INPUT)&&(sck==OUTPUT||sck==INPUT)

typedef struct{
	U8 INTAdjust;
	U8 SCKAdjust;
	void (*pfINTAction)(void);
	}sSPISlave;

#define SPI_TRUE_SLV_ADJUST(INT,misopin)		(SPI_TRUE_INT(INT)&&(misopin==OUTPUT||misopin==INPUT))


U8 SPI_MasterInit(sSPIMaster *spi);
U8 SPI_SlaveInit(sSPISlave *spi);

U8 SPI_MasterTx(U8 u8Data);
U8 SPI_MasterCapture(U8 *u8HeldData);
U8 SPI_SlaveUpdate(U8 u8Data);
U8 SPI_SlaveRx(U8 *u8RxData);
/* used when MASTER needed to be select as Slave from Another SPI, isn't implemented yet. */
U8 SPI_AlterMSTRtoSLV(void);




#endif /* ATMEGA32_SPI_H_ */