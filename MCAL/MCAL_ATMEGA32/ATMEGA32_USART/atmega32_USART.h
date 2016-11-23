/*
 * atmega32_UART.h
 *
 * Created: 10/3/2016 3:56:36 PM
 *  Author: AhmedShaarawy
 */ 


#ifndef ATMEGA32_UART_H_
#define ATMEGA32_UART_H_
#include "atmega32_IO.h"



/*************************************************************************
*/
#define UR_SYNC_MODE			0x40
#define UR_ASYNC_MODE			0x00
#define UR_TRUE_SYNC_ASYNC(as)	(as==0||as==0x40)

#define USR_XCK_FALLING			0x00
#define USR_XCK_RISING			0x01
#define USR_TRUE_XCK(xck)		(xck==0||xck==1)

#define UR_MPCM_EN				0x01
#define UR_MPCM_DIS				0x00
#define UR_TRUE_MPCM(mp)		(mp==0||mp==1)

#define UAR_DSPEED_EN			0x02
#define UAR_DSPEED_DIS			0x00
#define UAR_TRUE_DSPEED(ds)		(ds==0||ds==2)

#define UR_3INT_DISABLE			0x00
#define UR_TXC_1INT_EN			0x40
#define UR_RXC_1INT_EN			0x80
#define UR_UDRE_1INT_EN			0x20
#define UR_TRXC_2INT_EN			0xC0
#define UR_TXC_UDRE_2INT_EN		0x60
#define UR_RXC_UDRE_2INT_EN		0xA0
#define UR_TRXC_UDRE_2INT_EN	0xE0
#define UR_TRUE_INT(inter)		(inter==0||inter==0x40||inter==0x20||inter==0x80||\
								 inter==0xc0||inter==0x60||inter==0xa0||inter==0xe0)


#define UR_PARITY_EVEN_EN		0x20
#define UR_PARITY_ODD_EN		0x30
#define UR_PARITY_DIS			0x00
#define UR_TRUE_PARITY(p)		(p==0||p==0x20||p==0x30)

#define UR_CHARSIZE_5			0x00
#define UR_CHARSIZE_6			0x02
#define UR_CHARSIZE_7			0x04
#define UR_CHARSIZE_8			0x06
#define UR_CHARSIZE_9			0x07
#define UR_TRUE_CHAR(ch)		(ch>=0x00&&ch<=0x07)

#define UR_1STOP_BITS			0x00
#define UR_2STOP_BITS			0x08
#define UR_TRUE_STOPBITS(s)		(s==0||s==0x08)

#define UR_TX_ENABLE			0x08
#define UR_RX_ENABLE			0x10
#define UR_TRX_ENABLE			0x18
#define UR_TRUE_TRX(tr)			(tr==0x08||tr==0x10||tr==0x18)


// BAUD CHOICE
// chose from ( 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 76800, 115200, 230400, 250000 )
#define UR_BAUDRATE_2400		2400
#define UR_BAUDRATE_4800		4800
#define UR_BAUDRATE_9600		9600
#define UR_BAUDRATE_14400		14400
#define UR_BAUDRATE_19200		19200
#define UR_BAUDRATE_28800		28800
#define UR_BAUDRATE_38400		38400
#define UR_BAUDRATE_57600		57600
#define UR_BAUDRATE_76800		76800
#define UR_BAUDRATE_115200		115200
#define UR_BAUDRATE_230400		230400
#define UR_BAUDRATE_250000		250000
#define UR_TRUE_BAUDE(ba)		(ba>=2400&&ba<=250000)

#define UR_TRUE_USART_OBJECT(asy,xck,mpc,Ds,Int,prty,Cha,stp,trx,Brate)		UR_TRUE_SYNC_ASYNC(asy)&&USR_TRUE_XCK(xck)&&UR_TRUE_MPCM(mpc)&&\
										UAR_TRUE_DSPEED(Ds)&&UR_TRUE_INT(Int)&&UR_TRUE_PARITY(prty)&&\
										UR_TRUE_CHAR(Cha)&&UR_TRUE_STOPBITS(stp)&&UR_TRUE_TRX(trx)&&\
										UR_TRUE_BAUDE(Brate)

/************************************************************************/

#define USRTOperateMasterMode()		SET_PIN(B,PIN_XCK);
#define USRTOperateSlaveMode()		CLR_PIN(B,PIN_XCK);


typedef struct
{
	U8 SyncAsyncMode;
	U8 XCKEdgeMode;
	U8 MPCMode;
	U8 DoubleSpeedMode;
	U8 IntModes;
	U8 TRxModes;
	U8 ParityCheckMode;
	U8 DataCharSize;
	U8 StopBitsNum;
	U16 BuadRate;
	U32 MCU_Freq;
	}sUSART;


/* 
** USART 
*/
U8 USARTInti(sUSART *ur);
U8 USARTTx(U16 data);
U8 USARTRx(U16 *RxData);



#endif /* ATMEGA32_UART_H_ */
