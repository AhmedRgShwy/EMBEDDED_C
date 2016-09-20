/*
 * atmega32_IO.c
 *
 * Created: 9/17/2016 10:31:12 AM
 *  Author: AhmedShaarawy
 */

#include "PIC16F877A_IO.h"


/* FUNCTION(1) */
U8 IO_PortDir(U8 portBase, U8 dir)
{
        U8 checkPins= 0;

        if( TRUE_PORT(portBase) && TRUE_DIR(dir) )
        {
                if(dir == OUTPUT)
                        TRIS(portBase)= 0x00;
                else
                        TRIS(portBase)= 0xff;
                PORT(portBase)= 0x00;
                switch(portBase)
                {
                        case 0x05: checkPins= 0x06; break;
                        case 0x06: case 0x07: case 0x08:
                        checkPins= 0x08;             break;
                        case 0x09: checkPins= 0x03; break;
                        default: checkPins= 0x00;     break;
                }

        }
        return checkPins;
}

/* FUNCTION(2) */
U8 IO_PinDir(U8 portBase, U8 pin, U8 dir)
{
        U8 checkPin= 0;
        if( checkPin= (TRUE_PORT_TRUE_PIN(portBase,pin) && TRUE_DIR(dir)) )
        {
                if(dir == OUTPUT)
                        CLR_BIT(TRIS(portBase),pin);
                else
                        SET_BIT(TRIS(portBase),pin);
        }
        return checkPin ;
}

/* FUNCTION(3) */
U8 IO_PortRangeDir(U8 portBase, U8 firstPin, U8 lastPin, U8 dir)
{
        U8 checkPins= 0, i ;
        if(TRUE_PORT_TRUE_PIN(portBase,firstPin)&& TRUE_PORT_TRUE_PIN(portBase,lastPin)&& TRUE_DIR(dir))
        {
                if(firstPin> lastPin)
                {
                        firstPin^= lastPin;
                        lastPin^= firstPin;
                        firstPin^= lastPin;
                }
                checkPins= (lastPin- firstPin) +1;
                if(dir == OUTPUT)
                        for(i= firstPin; i<= lastPin ; i++ )
                                CLR_BIT(TRIS(portBase),i);
                else
                        for(i= firstPin; i<= lastPin ; i++ )
                                SET_BIT(TRIS(portBase),i);
        }
        return checkPins;
}

/* FUNCTION(4) */
U8 IO_PortDirManage(U8 portBase, U8 binary_1sel_0neg, U8 binaryDir_1out_0in)
{
        U8 checkPins= 0, portPinsNum= 0x00, pin, pinShiftRead= 0x01;
        if(TRUE_PORT(portBase)&& binary_1sel_0neg> 0x00 )
        {
                switch(portBase)
                {
                        case 0x05: portPinsNum= 0x06; break;
                        case 0x06: case 0x07: case 0x08:
                        portPinsNum= 0x08;             break;
                        case 0x09: portPinsNum= 0x03; break;
                        default: portPinsNum= 0x00;     break;
                }
                for( pin= 0 ; pin< portPinsNum ; pin++, pinShiftRead<<= 1 )
                {
                        if( ((binary_1sel_0neg&pinShiftRead) >> pin) && ((binaryDir_1out_0in&pinShiftRead) >> pin) )
                        {
                                CLR_BIT(TRIS(portBase),pin) ;
                                checkPins++ ;
                        }
                        else if( ((binary_1sel_0neg&pinShiftRead) >> pin) && !((binaryDir_1out_0in&pinShiftRead) >> pin) )
                        {
                                SET_BIT(TRIS(portBase),pin) ;
                                checkPins++ ;
                        }
                }
        }
        return checkPins;
}


/*********************************************************************************************************/

/* FUNCTION(5) */
U8 IO_PortWrite(U8 portBase, U8 val )
{
        U8 checkPins= 0;
        if( TRUE_PORT(portBase) && val<= 0xff )
        {
                PORT(portBase)= val;
                checkPins= 0x08;
        }
        return checkPins;
}

/* FUNCTION(6) */
U8 IO_PinWrite(U8 portBase, U8 pin, U8 val)
{
        U8 checkPin= 0;
        if( checkPin= (TRUE_PORT_TRUE_PIN(portBase,pin) && (val==0||val==1)) )
        {
                if(val == 1)
                SET_BIT(PORT(portBase),pin);
                else
                CLR_BIT(PORT(portBase),pin);
        }
        return checkPin ;
}

/* FUNCTION(7) */
U8 IO_PortRangeWrite(U8 portBase, U8 firstPin, U8 lastPin, U8 val)
{
        U8 checkPins= 0, i, shiftVal= 0x01 ;
        if(TRUE_PORT_TRUE_PIN(portBase,firstPin)&& TRUE_PORT_TRUE_PIN(portBase,lastPin) )
        {
                if(firstPin> lastPin)
                {
                        firstPin^= lastPin;
                        lastPin^= firstPin;
                        firstPin^= lastPin;
                }
                checkPins= (lastPin- firstPin) +1;
                for(i= firstPin; i<= lastPin ; i++, shiftVal<<= 1 )
                {
                       if( shiftVal&val )
                           SET_BIT(PORT(portBase),i);
                       else
                           CLR_BIT(PORT(portBase),i);
                }
        }
        return checkPins;
}

/* FUNCTION(8) */
U8 IO_PortWriteManage(U8 portBase, U8 binary_1sel_0neg, U8 binary_val)
{
        U8 checkPins= 0, portPinsNum= 0x00, pin, pinShiftRead= 0x01;
        if(TRUE_PORT(portBase)&& binary_1sel_0neg> 0x00 )
        {
                switch(portBase)
                {
                        case 0x05: portPinsNum= 0x06; break;
                        case 0x06: case 0x07: case 0x08:
                        portPinsNum= 0x08;             break;
                        case 0x09: portPinsNum= 0x03; break;
                        default: portPinsNum= 0x00;     break;
                }
                for( pin= 0 ; pin< portPinsNum ; pin++, pinShiftRead<<= 1 )
                {
                        if( ((binary_1sel_0neg&pinShiftRead) >> pin) && ((binary_val&pinShiftRead) >> pin) )
                        {
                                SET_BIT(PORT(portBase),pin) ;
                                checkPins++ ;
                        }
                        else if( ((binary_1sel_0neg&pinShiftRead) >> pin) && !((binary_val&pinShiftRead) >> pin) )
                        {
                                CLR_BIT(PORT(portBase),pin) ;
                                checkPins++ ;
                        }
                }
        }
        return checkPins;
}


/********************************************************************************************************/

/* FUNCTION(9) */
U8 IO_PortRead(U8 portBase, U8 *portVal )
{
        U8 checkPins= 0;
        if( TRUE_PORT(portBase) )
        {
                checkPins= 0x08;
                *portVal= PORT(portBase)&0xff ;
        }
        return checkPins;
}

/* FUNCTION(10) */
U8 IO_PinRead(U8 portBase, U8 pin, U8 *pinReadVal)
{
        U8 checkPin= 0;
        if( checkPin= TRUE_PORT_TRUE_PIN(portBase,pin) )
                *pinReadVal= READ_BIT(PORT(portBase),pin);
        return checkPin ;
}

/* FUNCTION(11) */
U8 IO_PortRangeRead(U8 portBase, U8 firstPin, U8 lastPin, U8 *rangeReadVal)
{
        U8 checkPins= 0, i ;
        if(TRUE_PORT_TRUE_PIN(portBase,firstPin) && TRUE_PORT_TRUE_PIN(portBase,lastPin) )
        {
                if(firstPin> lastPin)
                {
                        firstPin^= lastPin;
                        lastPin^= firstPin;
                        firstPin^= lastPin;
                }
                checkPins= (lastPin- firstPin) +1;
                *rangeReadVal= 0x00 ;
                for(i= firstPin; i<= lastPin ; i++ )
                        *rangeReadVal|= PORT(portBase)&(1<<i) ;
                (*rangeReadVal)>>= firstPin;
        }
        return checkPins;
}

/* FUNCTION(12) */
U8 IO_PortReadManage(U8 portBase, U8 binary_1sel_0neg, U8 *binaryIndividuals_readVal)
{
        U8 checkPins= 0x00, portPinsNum= 0x00, pin, pinShiftRead= 0x01;
        if(TRUE_PORT(portBase)&& binary_1sel_0neg> 0x00 )
        {
                switch(portBase)
                {
                        case 0x05: portPinsNum= 0x06; break;
                        case 0x06: case 0x07: case 0x08:
                        portPinsNum= 0x08;             break;
                        case 0x09: portPinsNum= 0x03; break;
                        default: portPinsNum= 0x00;     break;
                }
                *binaryIndividuals_readVal= 0x00;
                for( pin= 0 ; pin< portPinsNum ; pin++, pinShiftRead<<= 1 )
                {
                        if( ((binary_1sel_0neg&pinShiftRead) >> pin) )
                        {
                                *binaryIndividuals_readVal|= PORT(portBase)&(1<<pin) ;
                                checkPins++ ;
                        }
                }
        }
        return checkPins;
}



/********************************************************************************************************/

/* FUNCTION(13) */
U8 IO_PortToggle(U8 portBase)
{
        U8 checkPins= 0;
        if( TRUE_PORT(portBase) )
        {
                checkPins= 0x08;
                PORT(portBase)^= 0xff ;
        }
        return checkPins;
}

/* FUNCTION(14) */
U8 IO_PinToggle(U8 portBase, U8 pin)
{
        U8 checkPin= 0;
        if( checkPin= TRUE_PORT_TRUE_PIN(portBase,pin) )
                TOGGLE_BIT(PORT(portBase),pin);
        return checkPin ;
}

/* FUNCTION(.51) */
U8 IO_PortRangeToggle(U8 portBase, U8 firstPin, U8 lastPin)
{
        U8 checkPins= 0, i ;
        if(TRUE_PORT_TRUE_PIN(portBase,firstPin) && TRUE_PORT_TRUE_PIN(portBase,lastPin) )
        {
                if(firstPin> lastPin)
                {
                        firstPin^= lastPin;
                        lastPin^= firstPin;
                        firstPin^= lastPin;
                }
                checkPins= (lastPin- firstPin) +1;
                for(i= firstPin; i<= lastPin ; i++ )
                        TOGGLE_BIT(PORT(portBase),i);
        }
        return checkPins;
}

/* FUNCTION(16) */
U8 IO_PortToggleManage(U8 portBase, U8 binary_1sel_0neg)
{
        U8 checkPins= 0, portPinsNum= 0, pin, pinShiftRead= 0x01;
        if(TRUE_PORT(portBase)&& binary_1sel_0neg> 0x00 )
        {
                switch(portBase)
                {
                        case 0x05: portPinsNum= 0x06; break;
                        case 0x06: case 0x07: case 0x08:
                        portPinsNum= 0x08;             break;
                        case 0x09: portPinsNum= 0x03; break;
                        default: portPinsNum= 0x00;     break;
                }
                for( pin= 0 ; pin< portPinsNum ; pin++, pinShiftRead<<= 1 )
                {
                        if( ((binary_1sel_0neg&pinShiftRead) >> pin) )
                        {
                                TOGGLE_BIT(PORT(portBase),pin) ;
                                checkPins++ ;
                        }
                }
        }
        return checkPins;
}

