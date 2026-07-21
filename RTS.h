/*
 * @file    RTS.h
 * @brief Real Time Scheduler
 * Project:  Firefly PIC18 Multiboard
 *   Supports Acorn API v1.1
 * Author:  Michael L Anderson
 * Company: Black Oak Engineering
 * Copyright 2026 - All Rights Reserved
 * Created: 19 Jun 26
 * Hardware: v1 PCBA, PIC18F26Q43T-I/SS, internal oscillator, SYSCLK = 16 MHz 
 * License: BOE Proprietary
 */

#ifndef RTS_H
#define	RTS_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#define PeriodicOptsNum 6
#define TimeoutOptsNum 5
#define CountdownDisabled   0x0
#define PeriodDisabled      0x0

//extern char periodicOptStrs[PeriodicOptsNum][8];
//extern char timeoutOptStrs[TimeoutOptsNum][8];
//
//typedef enum Process_Periods { Proc_none, Proc_1min, Proc_5min, Proc_10min, Proc_30min, Proc_60min } procPers;
//typedef enum Time_Outs { Timeout_NeverOn, Timeout_5sec, Timeout_10sec, Timeout_30sec, Timeout_60sec, Timeout_StayOn } timeOuts;
   
struct rtsStruct
{
    uint16_t    ms; 
    uint16_t    free_ms;
    uint8_t     sec;
    uint8_t     min;
    uint8_t     hr;   
    uint16_t    serialRepCtdn_ms;   // Serial reporting
    uint16_t    serialRepPeriod_ms; // serep period, 0 means no serep
    bool        measSemaphor;
}; 

extern struct rtsStruct rts;

void rtsScheduler(void);
void rtsInit(void);
void msDelay(uint16_t ms);
void rtsClock(void);
void delay(uint16_t d);

#ifdef	__cplusplus
}
#endif

#endif	/* RTS_H */

