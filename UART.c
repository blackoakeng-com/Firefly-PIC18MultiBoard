/*
 * @file    UART.c
 * @brief UART serial comms
 * Project:  Firefly PIC18 Multiboard
 *   Supports Acorn API v1.1
 * Author:  Michael L Anderson
 * Company: Black Oak Engineering
 * Copyright 2026 - All Rights Reserved
 * Created: 19 Jun 26
 * Hardware: v1 PCBA, PIC18F26Q43T-I/SS, internal oscillator, SYSCLK = 16 MHz 
 * License: BOE Proprietary
 */

#include "Firefly.h"
#include "UART.h"

void uart1Init(void)
{
    // Set the UART1 module to the options selected in the user interface.

    //RXCHK disabled; 
    U1RXCHK = 0x0;
    //TXCHK disabled; 
    U1TXCHK = 0x0;
    //P1L 0x0; 
    U1P1L = 0x0;
    //P1H 0x0; 
    U1P1H = 0x0;
    //P2L 0x0; 
    U1P2L = 0x0;
    //P2H 0x0; 
    U1P2H = 0x0;
    //P3L 0x0; 
    U1P3L = 0x0;
    //P3H 0x0; 
    U1P3H = 0x0;
    //MODE Asynchronous 8-bit mode; RXEN enabled; TXEN enabled; ABDEN disabled; BRGS high speed; 
    U1CON0 = 0xB0;
    //SENDB disabled; BRKOVR disabled; RXBIMD Set RXBKIF on rising RX input; WUE disabled; ON enabled; 
    U1CON1 = 0x80;
    //FLO off; TXPOL not inverted; C0EN Add all TX and RX characters; STP Transmit 1Stop bit, receiver verifies first Stop bit; RXPOL not inverted; RUNOVF RX input shifter stops all activity; 
    U1CON2 = 0x8;
    //BRGL 138; 
    U1BRGL = 0x8A;
    //BRGH 0; 
    U1BRGH = 0x0;
    //TXBE empty; STPMD in middle of first Stop bit; TXWRE No error; 
    U1FIFO = 0x2E;
    //ABDIE disabled; ABDIF Auto-baud not enabled or not complete; WUIF WUE not enabled by software; 
    U1UIR = 0x0;
    //TXCIF equal; RXFOIF not overflowed; RXBKIF No Break detected; FERIF no error; CERIF No Checksum error; ABDOVF Not overflowed; PERIF no parity error; TXMTIF empty; 
    U1ERRIR = 0x80;
    //TXCIE disabled; RXFOIE disabled; RXBKIE disabled; FERIE disabled; CERIE disabled; ABDOVE disabled; PERIE disabled; TXMTIE disabled; 
    U1ERRIE = 0x0;
}

void uart1Enable(void)
{
    U1CON1bits.ON = 1; 
}

void uart1Disable(void)
{
    U1CON1bits.ON = 0; 
}

void uart1TransmitEnable(void)
{
    U1CON0bits.TXEN = 1;
}

void uart1TransmitDisable(void)
{
    U1CON0bits.TXEN = 0;
}

void uart1ReceiveEnable(void)
{
    U1CON0bits.RXEN = 1;
}

void uart1ReceiveDisable(void)
{
    U1CON0bits.RXEN = 0;
}

void uart1SendBreakControlEnable(void)
{
    U1CON1bits.SENDB = 1;
}

void uart1SendBreakControlDisable(void)
{
    U1CON1bits.SENDB = 0;
}

void uart1AutoBaudSet(bool enable)
{
    if(enable)
    {
        U1CON0bits.ABDEN = 1; 
    }
    else
    {
      U1CON0bits.ABDEN = 0;  
    }
}


bool uart1AutoBaudQuery(void)
{
    return (bool)U1UIRbits.ABDIF; 
}

void uart1AutoBaudDetectCompleteReset(void)
{
    U1UIRbits.ABDIF = 0; 
}

bool uart1IsAutoBaudDetectOverflow(void)
{
    return (bool)U1ERRIRbits.ABDOVF; 
}

void uart1AutoBaudDetectOverflowReset(void)
{
    U1ERRIRbits.ABDOVF = 0; 
}

bool uart1IsRxReady(void)
{
    return (bool)(!U1FIFObits.RXBE);
}

bool uart1IsTxReady(void)
{
    return (bool)(U1FIFObits.TXBE && U1CON0bits.TXEN);
}

bool uart1IsTxDone(void)
{
    return U1ERRIRbits.TXMTIF;
}

//size_t UART1_ErrorGet(void)
//{
//    uart1RxLastError.status = 0;
//    
//    if(true == U1ERRIRbits.FERIF)
//    {
//        uart1RxLastError.ferr = 1;
//        if(NULL != UART1_FramingErrorHandler)
//        {
//            UART1_FramingErrorHandler();
//        }  
//    }
//    if(true == U1ERRIRbits.RXFOIF)
//    {
//        uart1RxLastError.oerr = 1;
//        if(NULL != UART1_OverrunErrorHandler)
//        {
//            UART1_OverrunErrorHandler();
//        }   
//    }
//    if(true == U1ERRIRbits.PERIF)
//    {
//        uart1RxLastError.perr = 1;
//        if(NULL != UART1_ParityErrorHandler)
//        {
//            UART1_ParityErrorHandler();
//        }   
//    }
//
//    return uart1RxLastError.status;
//}

uint8_t uart1Read(void)
{
    return U1RXB;
}


void uart1Write(uint8_t txData)
{
    U1TXB = txData; 
}

int getch(void)   
{
    if (U1FIFObits.RXBE) { U1FIFObits.RXBE = 0; return 0; }
    else         // return U1RXB;
    {
        while(!(uart1IsRxReady()))
        {

        }
        return uart1Read();
    }
}

void putch(char txData)
{
    while(!(uart1IsTxReady()))
    {

    }
    return uart1Write(txData);   
}