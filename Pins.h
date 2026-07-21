/*
 * @file    Pins.h
 * @brief Pin names
 * Project:  Firefly
 *   Supports Acorn API v1.1
 * Author:  Michael L Anderson
 * Company: Black Oak Engineering
 * Copyright 2026 - All Rights Reserved
 * Created: 19 Jun 26
 * Hardware: 1v2 PCBA, PIC18F26Q43T-I/SS, internal oscillator, SYSCLK = 16 MHz 
 * License: BOE Proprietary
 */

#ifndef PINS_H
#define	PINS_H

#define MCLR_n_In   PORTEbits.RE3       // Pin #1 
#define MCLR_n_TRIS	TRISEbits.TRISE3

#define AN0_Out     LATAbits.LATA0      // #2 Analog by default
#define AN0_In      PORTAbits.RA0
#define AN0_TRIS	TRISAbits.TRISA0    // A: 0000 0001

#define AN1_Out     LATAbits.LATA1      // #3 Analog by default
#define AN1_In      PORTAbits.RA1
#define AN1_TRIS	TRISAbits.TRISA1    // A: 0000 0011

#define AN2_Out     LATAbits.LATA2      // #4 Analog by default
#define AN2_In      PORTAbits.RA2
#define AN2_TRIS	TRISAbits.TRISA2    // A: 0000 0111

#define AN3_Out     LATAbits.LATA3      // #5 Analog by default
#define AN3_In      PORTAbits.RA3
#define AN3_TRIS	TRISAbits.TRISA3    // A: 0000 1111

#define BattHalfV_In    PORTAbits.RA4   // #6 Analog, fixed on Firefly.
#define BattHalfV_TRIS  TRISAbits.TRISA4  // A: 0001 1111

#define BattCheck_Out   LATAbits.LATA5   // #7 Fixed on Firefly.  Init 0.
#define BattCheck_TRIS  TRISAbits.TRISA5

#define UART3_RX_In     PORTAbits.RA7       // #9 Remap.
#define UART3_RX_TRIS   TRISAbits.TRISA7    // UART3 has external breakout.  A: 1001 1111

#define UART3_TX_Out    LATAbits.LATA7      // #10 Remap.
#define UART3_TX_TRIS   TRISAbits.TRISA7    // UART3 has external breakout.

#define Ext_CS_Out      LATCbits.LATC0      // #11 Init 1
#define Ext_CS_TRIS     TRISCbits.TRISC0

#define SOSCI_In        PORTCbits.RC1       // #12 Fixed on Firefly.  
#define SOSCI_TRIS      TRISCbits.TRISC1    // C: 0000 0010

#define SOSCO_Out       LATCbits.RC2        // #13 Fixed on Firefly.  
#define SOSCO_TRIS      TRISCbits.TRISC2

#define IIC3_SCL_Out    LATCbits.LATC3      // #14 Remap
#define IIC3_SCL_In     PORTCbits.RC3
#define IIC3_SCL_TRIS   TRISCbits.TRISC3	 

#define IIC3_SDA_Out    LATCbits.LATC4      // #15 Remap
#define IIC3_SDA_In     PORTCbits.RC4
#define IIC3_SDA_TRIS	TRISCbits.TRISC4	 

#define Swi3V3_En_Out   LATCbits.LATC5      // #16 fixed on Firefly
#define Swi3V3_En_TRIS	TRISCbits.TRISC5	

#define UART1_TX_Out    LATCbits.RC6        // #17 Remap.
#define UART1_TX_TRIS   TRISCbits.TRISC6    // UART1 is internal use.

#define UART1_RX_In     PORTCbits.RC7       // #18 Remap.
#define UART1_RX_TRIS   TRISCbits.TRISC7    // UART1 is internal use.  C: 1000 0010

#define INT_Out         LATBbits.RB0        // #21 
#define INT_In          PORTBbits.RB0      
#define INT_TRIS        TRISBbits.TRISB0   

#define SPI1_MOSI_Out   LATBbits.RB1        // #22 Remap, Micro Out - Serial In 
#define SPI1_MOSI_TRIS  TRISBbits.TRISB1     

#define SPI1_MISO_In    PORTBbits.RB2       // #23 Remap, Micro In - Serial Out
#define SPI1_MISO_TRIS  TRISBbits.TRISB2    // B: 0000 0100 

#define SPI1_SCK_Out    LATBbits.RB3        // #24 Remap
#define SPI1_SCK_TRIS   TRISBbits.TRISB3     

#define PWM_Out         LATBbits.LATB4      // #25 
#define PWM_In          PORTBbits.RB4       
#define PWM_TRIS        TRISBbits.TRISB4    

#define RST_Out         LATBbits.LATB5      // #26 
#define RST_In          PORTBbits.RB5       
#define RST_TRIS        TRISBbits.TRISB5       

#define PGC_Out         LATBbits.LATB6      // #27 Connected to LED
#define LED_Out         LATBbits.LATB6      // alias
#define PGC_In          PORTBbits.RB6       // Used in ICSP
#define PGC_TRIS        TRISBbits.TRISB6      

#define PGD_Out         LATBbits.LATB7      // #28 
#define PGD_In          PORTBbits.RB7       // Used in ICSP
#define PGD_TRIS        TRISBbits.TRISB7    // B: 1000 0100

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

