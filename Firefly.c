/*
 * @file    Firefly.c  
 * @brief main() 
 * Project:  Firefly
 *   Supports Acorn API v1.1
 * Author:  Michael L Anderson
 * Company: Black Oak Engineering
 * Copyright 2026 - All Rights Reserved
 * Created: 17 Jul 26
 * Hardware: 1v2 PCBA, PIC18F26Q43T-I/SS, internal oscillator, SYSCLK = 16 MHz 
 * License: BOE Proprietary
 */

#include "Firefly.h"
#include "System.h"
#include "Timer.h"
#include "RTS.h"
#include "UART.h"
//#include "Interrupts.h"

char namePlain[] = "Firefly PIC18 Multiboard";
char verFirmware[] = "0.1";
char verHardware[] = "1.2";
char verAcorn[] = "1.3";
char modelNumber[] = "#BE-FIRF";
char pointOfContact[] = "blackoakeng.com";
char serialNumber[] = "260717AA";    // Build YYMMDDnn

uint8_t sensorID;   
uint16_t commsFail;
uint8_t sysStat;
uint16_t errCon;

void main(void) 
{
    uint8_t dummy;
    systemInit();
    timer1Start();       
    rtsInit();    
    //measInit();
    uart1Enable();
  
    INTCON0bits.GIE = 1;    // Global interrupt enable
    sysStat = SST_AcornEchoOn + SST_ShowMags;
//    acornInitialMessage();
//    acornPrompt();
    while(1) 
    {
        dummy++;

    }
    return;
}

void __interrupt(irq(TMR1), base(8)) TMR1_ISR(void)
{
    PIR3bits.TMR1IF = 0;
    rts.free_ms++;
    if (rts.free_ms > 1000) 
    {
        LED_Out ^= 1;
        rts.free_ms = 0;
    }
}
