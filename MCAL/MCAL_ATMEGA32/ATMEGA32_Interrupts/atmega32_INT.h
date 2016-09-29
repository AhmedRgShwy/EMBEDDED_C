/*
 * atmega32_INTERRUPTS.h
 *
 * Created: 9/29/2016 4:10:57 AM
 *  Author: AhmedShaarawy
 */ 


#ifndef ATMEGA32_INT_H_
#define ATMEGA32_INT_H_

#include "atmega32_lib.h"

/*
** External sense control. 
** for INT0/1 all of these modes are available, However INT2 support falling edge and rising edge only.
*/
#define EXINT_LOWLEVEL			0x00
#define EXINT_LOGICCAHNGE		0x01
#define EXINT_FEDGE				0x02
#define EXINT_REDGE				0x03

#define EXINT0_TRUE_SCTR(sense)			(sense>=0x00&&sense<=0x03)
#define	EXINT1_TRUE_SCTR(sense)			(sense>=0x00&&sense<=0x03)
#define	EXINT2_TRUE_SCTR(sense)			(sense==0x02||sense==0x03)


/*
** INTCtr: Interrupt control
*/
#define EXINT_DISABLE	0x00
#define EXINT_ENABLE	0x01


/*
** read interrupt flags
*/
#define EXINT0_READ_FLAG	READ_BIT(GIFR,INTF0)
#define EXINT1_READ_FLAG	READ_BIT(GIFR,INTF1)
#define EXINT2_READ_FLAG	READ_BIT(GIFR,INTF2)
/*
** clear interrupt flags
*/
#define EXINT0_Clear_Flag()		SET_BIT(GIFR,INTF0)
#define EXINT1_Clear_Flag()		SET_BIT(GIFR,INTF1)
#define EXINT2_Clear_Flag()		SET_BIT(GIFR,INTF2)
/*
** enabling and disabling interrupts
*/
#define EXINT0_Enable()		SET_BIT(GICR,INT0)
#define EXINT1_Enable()		SET_BIT(GICR,INT1)
#define EXINT2_Enable()		SET_BIT(GICR,INT2)

#define EXINT0_Disable()	CLR_BIT(GICR,INT0)
#define EXINT1_Disable()	CLR_BIT(GICR,INT1)
#define EXINT2_Disable()	CLR_BIT(GICR,INT2)

/* moves interrupts to the start of the Flash Boot section */
#define MoveInterrupts()	SET_BIT(GICR,IVCE);\
							SET_BIT(GICR,IVSEL)



typedef struct{
	U8 SenseControl;
	void (*pfINTAction)(void);
	}sEXINT;

U8 EXINT0_Init(sEXINT *exint);
U8 EXINT1_Init(sEXINT *exint);
U8 EXINT2_Init(sEXINT *exint);



#endif /* ATMEGA32_INTERRUPTS_H_ */