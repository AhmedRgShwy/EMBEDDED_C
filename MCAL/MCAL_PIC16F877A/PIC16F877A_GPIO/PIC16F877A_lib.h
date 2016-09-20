

#ifndef PIC16F877A_LIB_H
#define PIC16F877A_LIB_H

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned long U32;

/*
                               *****************
******************************** GPIO, DIO, IO *****************************
                               *****************
*/
/*
** The corresponding data direction register is TRISx, ( set the direction of the port ).
** Setting a TRISx bit (= 1) will make the corresponding PORTx pin an input.
** Clearing a TRISx bit (= 0) will make the corresponding PORTx pin an output.
** Reading the PORTx register reads the status of the pins ( PORTx for read ), and also ( for write ).
** whereas writing to it will write to the port latch. All write operations are read-modify-write operations.
** Therefore, a write to a port implies that the port pins are read, the value is modified and then written to the port data latch.
*/
#define INPUT        1
#define OUTPUT        0
#define TRUE_DIR(dir)        (dir==INPUT||dir==OUTPUT)

/* Port A 
** PORTA is a 6-bit wide, bidirectional port.
*/
#define TRISA        *(volatile U8 *const)0x85
#define PORTA        *(volatile U8 *const)0x05

/* Port B 
** PORTB is an 8-bit wide, bidirectional port.
*/
#define TRISB        *(volatile U8 *const)0x86
#define PORTB        *(volatile U8 *const)0x06

/* Port C 
** PORTC is an 8-bit wide, bidirectional port.
*/
#define TRISC        *(volatile U8 *const)0x87
#define PORTC        *(volatile U8 *const)0x07

/* Port D 
** PORTD is an 8-bit wide, bidirectional port.
*/
#define TRISD        *(volatile U8 *const)0x88
#define PORTD        *(volatile U8 *const)0x08

/* Port E 
** PORTE has three pins.
*/
#define TRISE        *(volatile U8 *const)0x89
#define PORTE        *(volatile U8 *const)0x09

/*
** Second way for simplicity in GPIO Driver. 
*/
#define A                0x05
#define B                0x06
#define D                0x08
#define C                0x07
#define E                0x09
#define TRUE_PORT(port_base)                  (port_base==0x05||port_base==0x06||port_base==0x07||port_base==0x08||port_base==0x09)
#define TRUE_PORT_TRUE_PIN(port_base,pin)    (   ( (port_base==0x05)&&(pin>=0&&pin<=5) )||\
                                             ( ((port_base==0x06)||(port_base==0x07)||(port_base==0x08))&&(pin>=0&&pin<=7) )||\
                                             ( (port_base==0x09)&&(pin>=0&&pin<=2) )   )
                                        
#define TRIS(port_base)        *((volatile U8 *const)(port_base|0x80))
#define PORT(port_base)        *((volatile U8 *const)port_base )

#define SET_BIT(reg,pin)                reg|=(1<<pin)
#define CLR_BIT(reg,pin)                reg&=~(1<<pin)
#define READ_BIT(reg,pin)                ((reg&(1<<pin))>>pin)
#define TOGGLE_BIT(reg,pin)             reg^=(1<<pin)

/********** 7 **********/
#define PIN_RX                7
#define PIN_DT                7
#define PIN_PSP7                7
#define PIN_PGD                7
/********** 6 **********/
#define PIN_TX                6
#define PIN_CK                6
#define PIN_PSP6                6
#define PIN_PGC                6
/********** 5 **********/
#define PIN_PSP5                5
#define PIN_AN4                5
#define PIN_C2OUT                5
#define PIN_SS                5
#define PIN_SDO                5
/********** 4 **********/
#define PIN_PSP4                4
#define PIN_T0CK1                4
#define PIN_C1OUT                4
#define PIN_SDI                4
#define PIN_SDA                4
/********** 3 **********/
#define PIN_PGM                3
#define PIN_AN3                3
#define PIN_VREF_PLUS        3
#define PIN_SCK                3
#define PIN_SCL                3
#define PIN_PSP3                3
/********** 2 **********/
#define PIN_AN2                2
#define PIN_VREF_MINUS        2
#define PIN_CVREF                2
#define PIN_CS                2
#define PIN_AN7                2
#define PIN_CCP1                2
#define PIN_PSP2                2
/********** 1 **********/
#define PIN_AN1                1
#define PIN_WR                1
#define PIN_AN6                1
#define PIN_T1OS1                1
#define PIN_CCP2                1
#define PIN_PSP1                1
/********** 0 **********/
#define PIN_INT                0
#define PIN_AN0                0
#define PIN_AN5                0
#define PIN_RD                0
#define PIN_T1OSO                0
#define PIN_T1CK1                0
#define PIN_PSP0                0

/*
                               **********
******************************** TIMER0 *****************************
                               **********
*/
/*
** OPTION_REG REGISTER
*/

#define OPTION_REG        *(volatile U8 *const)0x81
#define RBPU         7
#define INTEDG         6
#define T0CS         5
#define T0SE         4
#define PSA         3
#define PS2         2
#define PS1         1
#define PS0        0

/*
** TMR0 Timer0 Module Register
*/
#define TMR0        *(volatile U8 *const)0x01

/*
** INTCON
*/
#define INTCON        *(volatile U8 *const)0x0B
#define GIE         7
#define PEIE         6
#define TMR0IE         5
#define INTE         4
#define RBIE         3
#define TMR0IF         2
#define INTF         1
#define RBIF        0

/*
                               **********
******************************** TIMER1 *****************************
                               **********
*/
/*
** T1CON: TIMER1 CONTROL REGISTER
*/
#define T1CON        *(volatile U8 *const)0x10
#define T1CKPS1                5
#define T1CKPS0                4
#define T1OSCEN                3
#define T1SYNC                2
#define TMR1CS                1
#define TMR1ON                0

/*
** PIR1
*/
#define PIR1        *(volatile U8 *const)0x0C
#define PSPIF 
#define ADIF 
#define RCIF 
#define TXIF 
#define SSPIF 
#define CCP1IF 
#define TMR2IF 
#define TMR1IF

/*
** PIE1
*/
#define PIE1        *(volatile U8 *const)0x8C
#define ADIE 
#define PSPIE 
#define RCIE 
#define TXIE 
#define SSPIE 
#define CCP1IE 
#define TMR2IE 
#define TMR1IE

/*
** TMR1L, TMR1H
*/
#define TMR1L        *(volatile U8 *const)0x0E
#define TMR1H        *(volatile U8 *const)0x0F

/*
                               **********
******************************** TIMER2 *****************************
                               **********
*/

/*
** T2CON: TIMER2 CONTROL REGISTER (ADDRESS 12h)
*/
#define T2CON        *(volatile U8 *const)0x12
#define TOUTPS3         6
#define TOUTPS2         5
#define TOUTPS1         4
#define TOUTPS0         3
#define TMR2ON                 2
#define T2CKPS1         1
#define T2CKPS0                0

/*
** PIR1
*/

/*
** PIE1
*/

/*
** TMR2: Timer2 Module’s Register
*/
#define TMR2        *(volatile U8 *const)0x11

/*
** PR2: Timer2 Period Register
*/
#define PR2        *(volatile U8 *const)0x92


/*
                               *************************
******************************** CAPTURE, COMPARE, PWM *****************************
                               *************************
*/
/*
** PIR2
*/
#define PIR2        *(volatile U8 *const)0x0D
#define CCP2IF        0

/*
** PIE2
*/
#define PIE2        *(volatile U8 *const)0x8D
#define CCP2IE        0

/*
** CCPR1L, CCPR1H: Capture/Compare/PWM Register
** Assuming the storing is leettle endian, u can use "CCPR1"
*/
#define CCPR1L        *(volatile U8 *const)0x15 
#define CCPR1H        *(volatile U8 *const)0x16 
#define CCPR1        *(volatile U16 *const)0x15

/*
** CCP1CON
*/
#define CCP1CON        *(volatile U8 *const)0x17 
#define CCP1X        5
#define CCP1Y        4
#define CCP1M3         3
#define CCP1M2         2
#define CCP1M1         1
#define CCP1M0        0

/*
** CCPR2L, CCPR2H: Capture/Compare/PWM Register
** Assuming the storing is leettle endian, u can use "CCPR2"
*/
#define CCPR2L        *(volatile U8 *const)0x1B 
#define CCPR2H        *(volatile U8 *const)0x1C
#define CCPR2        *(volatile U16 *const)0x1B

/*
** CCP2CON
*/
#define CCP2CON        *(volatile U8 *const)0x1D 
#define CCP2X        5
#define CCP2Y        4
#define CCP2M3         3
#define CCP2M2         2
#define CCP2M1         1
#define CCP2M0        0


/*
                               ********************************************************
******************************** MASTER SYNCHRONOUS SERIAL PORT (MSSP) MODULE SPI&I2C *****************************
                               ********************************************************
*/

/*
** SSPSTAT: MSSP STATUS REGISTER (ADDRESS 94h)
*/
#define SSPSTAT        *(volatile U8 *const)0x94
#define SMP         7
#define CKE         6
#define D/A         5
#define P         4
#define S         3
#define R/W         2
#define UA         1
#define BF        0


/*
** SSPCON1: MSSP CONTROL REGISTER1 (ADDRESS 14h)
*/
#define SSPCON        *(volatile U8 *const)0x14
#define SSPCON1        *(volatile U8 *const)0x14
#define WCOL         7
#define SSPOV         6
#define SSPEN         5
#define CKP         4
#define SSPM3         3
#define SSPM2         2
#define SSPM1         1
#define SSPM0        0

/*
** SSBUF: Synchronous Serial Port Receive Buffer/Transmit Register (ADDRESS 14h)
*/
#define SSBUF        *(volatile U8 *const)0x13


/*
** SSPCON2: MSSP CONTROL REGISTER2 (ADDRESS 91h)
*/
#define SSPCON2        *(volatile U8 *const)0x91
#define GCEN         7
#define ACKSTAT 6
#define ACKDT         5
#define ACKEN         4
#define RCEN         3
#define PEN         2
#define RSEN         1
#define SEN        0

/*
** SSPADD Synchronous Serial Port (I2C mode) Address Register
*/
#define SSPADD        *(volatile U8 *const)0x93



/*
                *******************************************************************************
***************** ADDRESSABLE UNIVERSAL SYNCHRONOUS ASYNCHRONOUS RECEIVER TRANSMITTER (USART) *****************************
                *******************************************************************************
*/
/*
** TXSTA: TRANSMIT STATUS AND CONTROL REGISTER (ADDRESS 98h)
*/
#define TXSTA        *(volatile U8 *const)0x98
#define CSRC         7
#define TX9         6
#define TXEN         5
#define SYNC         4
#define BRGH         2
#define TRMT         1
#define TX9D        0

/*
** RCSTA: RECEIVE STATUS AND CONTROL REGISTER (ADDRESS 18h)
*/
#define RCSTA        *(volatile U8 *const)0x18
#define SPEN         7
#define RX9         6
#define SREN         5
#define CREN         4
#define ADDEN         3
#define FERR         2
#define OERR         1
#define RX9D        0

/*
** SPBRG: Baud Rate Generator Register
*/
#define SPBRG        *(volatile U8 *const)0x99

/*
** TXREG: USART Transmit Register
*/
#define TXREG        *(volatile U8 *const)0x19


/*
** RCREG: USART Receive Register
*/
#define RCREG        *(volatile U8 *const)0x1A


/*
                               ********************************************
******************************** ANALOG-TO-DIGITAL CONVERTER (A/D) MODULE *****************************
                               ********************************************
*/

/*
** ADCON0: REGISTER (ADDRESS 1Fh)
*/
#define ADCON0        *(volatile U8 *const)0x1F
#define ADCS1        7
#define ADCS0         6
#define CHS2         5
#define CHS1         4
#define CHS0         3
#define GO/DONE        2
#define ADON        0

/*
** ADCON1: REGISTER (ADDRESS 9Fh)
*/
#define ADCON1        *(volatile U8 *const)0x9F
#define ADFM         7
#define ADCS2        6
#define PCFG3         3
#define PCFG2         2
#define PCFG1         1
#define PCFG0        0

/*
** ADRESH: A/D Result Register High Byte
*/
#define ADRESH        *(volatile U8 *const)0x1E

/*
** ADRESL: A/D Result Register Low Byte
*/
#define ADRESL        *(volatile U8 *const)0x9E



/*
                               *********************
******************************** COMPARATOR MODULE *****************************
                               *********************
*/

/*
** CMCON: COMPARATOR CONTROL REGISTER
*/
#define CMCON        *(volatile U8 *const)0x9C
#define C2OUT        7 
#define C1OUT         6
#define C2INV         5
#define C1INV         4
#define CIS         3
#define CM2         2        
#define CM1         1
#define CM0        0

/*
** CVRCON: 
*/
#define CVRCON        *(volatile U8 *const)0x9D
#define CVREN        7 
#define CVROE         6
#define CVRR        5
#define CVR3         3
#define CVR2         2
#define CVR1         1
#define CVR0        0


/*
                               *********************
******************************** CONFIGURATION WORD *****************************
                               *********************
*/
// Watchdog Timer (WDT)

/*
** CONFIG_WORD: 
*/
//#define CONFIG_WORD        *(volatile U16 *const)0x2007
#define CP        13
#define DEBUG         11
#define WRT1         10
#define WRT0        9
#define CPD        8
#define LVP        7
#define BOREN        6
#define PWRTEN         3
#define WDTEN         2
#define FOSC1        1 
#define FOSC0        0


/*
** STATUS: status register.
*/

#define STATUS        *(volatile U8 *const)0x03

#define IRP        7
#define RP1        6
#define RP0        5
#define TO        4
#define PD        3
#define Z        2
#define DC        1
#define C        0

/*
** FSR: Indirect Data Memory Address Pointer
*/
#define FSR        *(volatile U8 *const)0x04

/*
** PCLATH: Write Buffer for the upper 5 bits of the Program Counte
*/
#define PCLATH        *(volatile U8 *const)0x05

/*
** PCL: Program Counter (PC) Least Significant Byte 
*/
#define PCL        *(volatile U8 *const)0x82


/*
** PCON:  
*/
#define PCON        *(volatile U8 *const)0x8E
#define POR        1
#define BOR        0

/*
** INDF: Addressing this location uses contents of FSR to address data memory (not a physical register)
*/
#define INDF        *(volatile U8 *const)0x100


/*
                               **********
******************************** EEPROM *****************************
                               **********
*/
/*
** EEDATA: EEPROM Data Register Low Byte
*/
#define EEDATA        *(volatile U8 *const)0x10C
 
/*
** EEPROM:  Address Register Low Byte
*/
#define EEPROM        *(volatile U8 *const)0x10D
  
/*
** EEDATH: EEPROM Data Register High Byte
*/
#define EEDATH        *(volatile U8 *const)0x10E
        
/*
** EEADRH: EEPROM Address Register High Byte
*/
#define EEADRH        *(volatile U8 *const)0x10F
 
/*
** EECON1 REGISTER (ADDRESS 18Ch)
*/        
#define EECON1        *(volatile U8 *const)0x18
#define EEPGD        7
#define WRERR         3
#define WREN         2
#define WR         1
#define RD        0

/*
** EECON2 EEPROM Control Register2 (not a physical register)
*/
#define EECON2        *(volatile U8 *const)0x18D
 

#endif