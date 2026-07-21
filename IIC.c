/*
 * @file    IIC.c
 * @brief IIC
 * Project:  Firefly PIC18 Multiboard
 *   Supports Acorn API v1.1
 * Author:  Michael L Anderson
 * Company: Black Oak Engineering
 * Copyright 2026 - All Rights Reserved
 * Created: 19 Jun 26
 * Hardware: v1 PCBA, PIC18F26Q43T-I/SS, internal oscillator, SYSCLK = 16 MHz 
 * License: BOE Proprietary
 */

#include <xc.h>
#include <stdio.h>  
#include "Firefly.h"
#include "IIC.h"
//#include "RTS.h"

//#define IIC_Delay   2
//#define IIC_DELAY();   asm ("nop");
// #define IIC_DELAY();    __asm__ __volatile__("nop"); __asm__ __volatile__("nop"); __asm__ __volatile__("nop"); 
// #define IIC_DELAY();    for (int i = 0; i < 2; i++){}   // 2.1 us
 #define IIC_DELAY();    iicDummy+=3;  // 650 ns
        
uint8_t iicBfr[IIC_BFR_LEN];

static SYS_RtnCode _iicStart(void); // Assumes bus idle
static void _iicTransmit(uint8_t byOut);
static void _iicReceive(uint8_t* byIn);
static void _iicSendAck(void);
static void _iicSendNack(void);
static SYS_RtnCode _iicAwaitAck(void);
static void _iicStop(void);
static uint32_t  iicDummy;

void iicInit(void)
{}

    // Just write out a valid address, see if we get the Ack.
void iicWriteTest(uint8_t iicAddr)
{
    SYS_RtnCode rtn = RTN_Undefined;
    if (_iicStart() != RTN_Executed) 
    {
        printf("IIC bus not idle\r\n");
        errCon |= RTN_BusNotReady; 
        return; 
    }
    iicAddr <<= 1;         // Std I2C, 7-bit address followed by R/W bit. This is a W; LSB = 0.    
    _iicTransmit(iicAddr);  
    rtn = _iicAwaitAck();
    if (rtn == RTN_Executed) printf("Executed\r\n");      
    else if (rtn == RTN_IIC_NoAck) printf("No Ack\r\n");  
    else printf("Error = %d\r\n", rtn);                        
    _iicStop(); 
}

SYS_RtnCode iicByteWrite(uint8_t iicAddr, uint8_t iicReg, uint8_t datum) 
{
    SYS_RtnCode rtn = RTN_Undefined;

    if ((rtn = _iicStart()) != RTN_Executed) { _iicStop(); return rtn; }
    iicAddr <<= 1;          // Std I2C, 7-bit address followed by R/W bit. This is a W; LSB = 0.
    _iicTransmit(iicAddr);  
    if ((rtn = _iicAwaitAck()) != RTN_Executed) { _iicStop(); return rtn; }
    _iicTransmit(iicReg);
    if ((rtn = _iicAwaitAck()) != RTN_Executed) { _iicStop(); return rtn; }
    _iicTransmit(datum);
    if ((rtn = _iicAwaitAck()) != RTN_Executed) { _iicStop(); return rtn; }
    
    _iicStop();   
    return RTN_Executed;    
}

SYS_RtnCode iicByteRead(uint8_t iicAddr, uint8_t iicReg, uint8_t* datum)
{
    SYS_RtnCode rtn = RTN_Undefined;
    if ((rtn = _iicStart()) != RTN_Executed) { _iicStop(); return rtn; }       
    iicAddr <<= 1;          // Std I2C, 7-bit address followed by R/W bit. This is a W; LSB = 0.
    _iicTransmit(iicAddr);
    if ((rtn = _iicAwaitAck()) != RTN_Executed){ _iicStop(); return rtn; }
    _iicTransmit(iicReg);
    if ((rtn = _iicAwaitAck()) != RTN_Executed) { _iicStop(); return rtn; } 
    
    _iicStart();            // DEB Repeated Start
    
    _iicTransmit(iicAddr + IIC_ReadBit);  
    if ((rtn = _iicAwaitAck()) != RTN_Executed) { _iicStop(); return rtn; } 
    _iicReceive((uint8_t*) &datum);    
    _iicSendNack();
    _iicStop();
    return RTN_Executed;    
}

SYS_RtnCode iicArrayRead(uint8_t iicAddr, uint8_t iicReg, uint8_t len) 
{
    SYS_RtnCode rtn = RTN_Undefined;
    if (len > IIC_BFR_LEN) return RTN_IndexOutOfRange;
    if ((rtn = _iicStart()) != RTN_Executed) { _iicStop(); return rtn; }       
    iicAddr <<= 1;          // Std I2C, 7-bit address followed by R/W bit. This is a W; LSB = 0.
    _iicTransmit(iicAddr);
    if ((rtn = _iicAwaitAck()) != RTN_Executed) { _iicStop(); return rtn; }
    _iicTransmit(iicReg);
    if ((rtn = _iicAwaitAck()) != RTN_Executed) { _iicStop(); return rtn; }
    
            // Now need Repeated Start
    IIC3_SDA_Out = 1; IIC_DELAY();
    IIC3_SCL_Out = 1; IIC_DELAY(); 
    IIC3_SDA_Out = 0; IIC_DELAY(); 
    IIC3_SCL_Out = 0; IIC_DELAY(); 
    
    _iicTransmit(iicAddr + IIC_ReadBit);     
    if ((rtn = _iicAwaitAck()) != RTN_Executed) { _iicStop(); return rtn; }
   
    for (int i = 0; i < len; i++)
    {
        _iicReceive(&iicBfr[i]);
        if (i == (len - 1)) _iicSendNack();
        else _iicSendAck();
    }
       
    _iicStop();
    return RTN_Executed;    
}

  // IIC components ----------------------

static void _iicSendAck(void)
{
    IIC3_SDA_TRIS = 0;
    IIC3_SDA_Out = 0;  IIC_DELAY();
    IIC3_SCL_Out = 1;  IIC_DELAY();
    IIC3_SCL_Out = 0;  IIC_DELAY(); 
    IIC3_SDA_TRIS = 1;
}

static void _iicSendNack(void)
{
    IIC3_SDA_TRIS = 0;
    IIC3_SDA_Out = 1;  IIC_DELAY();
    IIC3_SCL_Out = 1;  IIC_DELAY();
    IIC3_SCL_Out = 0;  IIC_DELAY(); 
    IIC3_SDA_TRIS = 1;
}

static SYS_RtnCode _iicAwaitAck(void)
{
    SYS_RtnCode rtn = RTN_Undefined;
    uint8_t timeOut = 0;
    IIC3_SDA_Out = 1;                // Go H so Ack can pull L
    IIC3_SDA_TRIS = 1;           // Ready to read Ack
    IIC_DELAY();
    IIC3_SCL_Out = 1; 
    while (timeOut++ < 10)
    {
        if (IIC3_SDA_In == 0) break;
        IIC_DELAY();
    }
    if (timeOut >= 9)        
    { 
        _iicStop(); 
        rtn = RTN_IIC_NoAck; 
    }
    else rtn = RTN_Executed;
     
    IIC3_SCL_Out = 0;  
    IIC3_SDA_TRIS = 0;           // Back to drive
    IIC_DELAY();
    IIC3_SDA_Out = 0;
    return rtn; 
}

static void _iicTransmit(uint8_t byOut)
{    
    uint8_t mask = 0x80;
    IIC3_SDA_TRIS = 0;
    while (mask)
    {
        IIC3_SDA_Out = (byOut & mask) ? 1 : 0; IIC_DELAY();
        IIC3_SCL_Out = 1; IIC_DELAY();
        IIC3_SCL_Out = 0; IIC_DELAY();
        mask >>= 1;               
    }
}

static void _iicReceive(uint8_t* byIn)
{
    uint8_t mask = 0x80;
    *byIn = 0;
    IIC3_SDA_TRIS = 1;
    while (mask)
    {
        IIC3_SCL_Out = 1; IIC_DELAY();
        if (IIC3_SDA_In) *byIn |= mask; IIC_DELAY();   
        IIC3_SCL_Out = 0; IIC_DELAY();
        mask >>= 1;      
    }
    IIC3_SDA_TRIS = 0;
}

SYS_RtnCode _iicStart(void) // Requires bus idle
{
    IIC3_SDA_TRIS = IIC3_SCL_TRIS = 1;
    if ((IIC3_SDA_In == 0) || (IIC3_SCL_In == 0)) 
    { 
        _iicStop();         
        return RTN_BusNotReady;         
    }  
    IIC3_SDA_TRIS = IIC3_SCL_TRIS = 0;
    
    IIC3_SDA_Out = 0;        // Start
    IIC_DELAY();
    IIC3_SCL_Out = 0;
    return RTN_Executed;
}

void _iicStop(void)
{
    IIC3_SDA_TRIS = IIC3_SCL_TRIS = 0; 
    IIC3_SCL_Out = 1; IIC_DELAY();       // Stop
    IIC3_SDA_Out = 1;        
}
