/*
 * @file    IIC.h
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

#ifndef IIC_H
#define	IIC_H

#ifdef	__cplusplus
extern "C" {
#endif

#define IIC_ReadBit 0x01
    
#define IIC_BFR_LEN 15
extern uint8_t iicBfr[IIC_BFR_LEN];  

void iicInit(void);
void iicWriteTest(uint8_t iicAddr);
SYS_RtnCode iicByteWrite(uint8_t iicAddr, uint8_t iicReg, uint8_t datum);
SYS_RtnCode iicByteRead(uint8_t iicAddr, uint8_t iicReg, uint8_t* datum);
SYS_RtnCode iicArrayRead(uint8_t iicAddr, uint8_t iicRegStart, uint8_t len);

#ifdef	__cplusplus
}
#endif

#endif	/* IIC_H */

