/*
  * @file    System.c
  * @brief Hardware inits
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
#include "System.h"
#include "Clock.h"
#include "IIC.h"
#include "SPI.h"
#include "Timer.h"
#include "UART.h"
//#include "Interrupts.h"

void systemInit(void)
{
    clockInit();
    
    // Initialize the pins.  See Pins.h.
    LATA = LATB = 0;
    LATC = 0x01;
   
    // Open Drains
    ODCONA = 0x0;
    ODCONB = 0x0;
    ODCONC = 0x0;
    
    TRISA = 0x1F;
    TRISB = 0x84;
    TRISC = 0x82;

    // ANSELs
    ANSELA = 0x1F;
    ANSELB = 0x00;
    ANSELC = 0x00;

    // WPUx registers
    WPUA = 0x0;
    WPUB = 0x0;
    WPUC = 0x0;

    // Slew rate limit SLRCONx registers
    SLRCONA = 0x1F;
    SLRCONB = 0x84;
    SLRCONC = 0x82;

    // INLVLx registers
    INLVLA = 0x3F;
    INLVLB = 0xF0;
    INLVLC = 0xFF;

   // RxyI2C | RxyFEAT registers       
    RC3I2C = 0x0;   // These two set I2C slew rate, pull up, and threshold.
    RC4I2C = 0x0;
    
    // PPS registers, DS #341
    RC6PPS = 0x20;  // RC6->UART1:TX;
    RA6PPS = 0x26;  // RA6->UART3:TX;
    U1RXPPS = 0xC7;  // RC7->UART1:RX;
    U3RXPPS = 0x07;  // RA7->UART3:RX;
    
    RC3PPS = 0x37;  // IIC1 SCL
    RC4PPS = 0x38;  // IIC1 SDA
    I2C1SCLPPS = 0x23;
    I2C1SDAPPS = 0x24;
    
    RB1PPS = 0x32;  // RB1->SPI1:SDO
    SPI1SDIPPS = 0x12; //RB2->SPI1:SDI;
    SPI1SCKPPS = 0x13;  //RB3->SPI1:SCK;
    RB2PPS = 0x24;  //RB6->SPI1:SCK1;

   // IOCx registers 
    IOCAP = 0x0;
    IOCAN = 0x0;
    IOCAF = 0x0;
    IOCBP = 0x0;
    IOCBN = 0x0;
    IOCBF = 0x0;
    IOCCP = 0x0;
    IOCCN = 0x0;
    IOCCF = 0x0;
   
    iicInit();
	spi1Init();
    timer1Init();
    uart1Init();   
    
    PIE3bits.TMR1IE = 1;
    
    //RCONbits.IPEN = 1;
    //TMR0IP = 0;
   // interruptsInit();
}