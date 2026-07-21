/*
  * @file    Firefly.h
  * @brief Project header file
  * Project:  Firefly PIC18 Multiboard
  *   Supports Acorn API v1.1
  * Author:  Michael L Anderson
  * Company: Black Oak Engineering
  * Copyright 2026 - All Rights Reserved
  * Created: 19 Jun 26
  * Hardware: v1 PCBA, PIC18F16Q40T-I/SS, internal oscillator, SYSCLK = 16 MHz 
  * License: BOE Proprietary
  */


#ifndef FIREFLY_H
#define FIREFLY_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>   
#include "Pins.h"

extern char namePlain[];
extern char verFirmware[];
extern char verHardware[];
extern char verAcorn[];
extern char modelNumber[];
extern char pointOfContact[];
extern char serialNumber[];
extern uint8_t sensorID;   // If defined

extern uint16_t    commsFail;

extern uint8_t sysStat;
#define  SST_MeasRawMode    0x40    // Do not use cal zero & span
#define  SST_AcornEchoOn    0x20
#define  SST_SignOnMsg      0x02
#define  SST_ShowMags       0x01

extern uint16_t errCon;
#define ERC_SensorHWFail    0x80
#define ERC_EEPROMFail      0x40
#define ERC_SystemMalfunction   0x20    // E.g., arg is a nonexistent choice
#define ERC_SensorOverflow  0x04

 // Unified function return codes. 
typedef enum
{
    RTN_Executed = 1,
    RTN_Empty,
    RTN_Timeout,
    RTN_UnrecognizedAPICmd,     
    RTN_SyntaxError,
    RTN_ArgTooLong,           // EG, a serial number > max chars
    RTN_ParmOutOfRange,
    RTN_HardwareMalfunction,
    RTN_CannotWriteToReadOnly,
    RTN_MsmtStdDevExceeded,
    RTN_IndexOutOfRange,
    RTN_InSafetyShutdown,
    RTN_ControlNotResponding,
    RTN_UpperLimitReached,
    RTN_LowerLimitReached,
    RTN_BusyWithAnotherProcess,
    RTN_BusNotReady,
    RTN_IIC_NoAck,
    RTN_Undefined        
} SYS_RtnCode;


#endif