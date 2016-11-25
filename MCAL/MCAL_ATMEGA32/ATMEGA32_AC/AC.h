/*
 * AC.h
 *
 * Created: 11/24/2016 6:48:33 PM
 *  Author: AhmedShaarawy
 */ 


#ifndef AC_H_
#define AC_H_

#include "atmega32_lib.h"
#include <avr/interrupt.h>



#define AC_INT_ON_MODE			0x08
#define AC_INT_OFF_MODE			0x00
#define AC_TRUE_INT(Int)		(Int==0x00||Int==0x08)

#define AC_INT_ADJUST_ON_TOGGLE		0x00
#define AC_INT_ADJUST_ON_FALL		0x02
#define AC_INT_ADJUST_ON_RISE		0x03
#define AC_TRUE_INT_ADJUST(iadj)	(iadj==0x00||iadj==0x02||iadj==0x03)

#define AC_BANDGAB_POSTV_IN_ON		0x00
#define AC_BANDGAB_POSTV_IN_OFF		0x40
#define AC_TRUE_BANDGAB(bg)			(bg==0x00||bg==0x40)

#define AC_TRIGGER_TC1CAP_ON		0x04
#define AC_TRIGGER_TC1CAP_OFF		0x00
#define AC_TRUE_TRIGGER_TC1(tr)		(tr==0x00||tr==0x04)

#define AC_ACMUX_ON_MODE			0x08
#define AC_ACMUX_OFF_MODE			0x00
#define AC_TRUE_ACMUX_MD(mxm)		(mxm==0x00||mxm==0x08)

#define AC_ACMUX_A0_NEGTV_IN	0x00
#define AC_ACMUX_A1_NEGTV_IN	0x01
#define AC_ACMUX_A2_NEGTV_IN	0x02
#define AC_ACMUX_A3_NEGTV_IN	0x03
#define AC_ACMUX_A4_NEGTV_IN	0x04
#define AC_ACMUX_A5_NEGTV_IN	0x05
#define AC_ACMUX_A7_NEGTV_IN	0x06
#define AC_ACMUX_A8_NEGTV_IN	0x07
#define AC_TRUE_ACMUX_CH(mxc)	(mxc>=0x00&&mxc<=0x07)

#define AC_TRUE_OBJECT(Int,iadj,bg,tr,mxm,mxc)		AC_TRUE_INT(Int)&&AC_TRUE_INT_ADJUST(iadj)&&AC_TRUE_BANDGAB(bg)&&\
													AC_TRUE_TRIGGER_TC1(tr)&&AC_TRUE_ACMUX_MD(mxm)&&AC_TRUE_ACMUX_CH(mxc)


#define ACDisablePower()	SET_BIT(ACSR,ACD)
#define ACPowerSwitchOff()	SET_BIT(ACSR,ACD)
#define ACDisableInt()		CLR_BIT(ACSR,ACIE)
#define AC_READ_OUTPUT		READ_BIT(ACSR,ACO)
#define AC_READ_INT_FLAG	READ_BIT(ACSR,ACI)




typedef struct
{
	U8 ACIntMode;
	U8 ACIntAdjust;
	// instead off negative pin AI1, if this bit is enabled then this SW will disable ADC
	U8 ACMUXMode;
	U8 ACMUXChannelSel;
	// instead off positive pin AI0
	U8 BandgabMode;
	// USE AC output as input to TC1 capture
	U8 TirggerTC1CapMode;
	void(*PassToACIntVector)(void);
	}sAC;


U8 ACInit(sAC *ac);
U8 ACReadOutput(void);
void ACStopACMUX(void);

#endif /* AC_H_ */